#include<iostream>
#include <fstream>
#include <vector>
#include <stack>

std::vector<std::vector<int> > adj;

int **MatrizAdj, num_vert;
void Matriz(std::string file){
   std::fstream myfile(file, std::ios_base::in);
   int num_lig;
   myfile >> num_vert >> num_lig;
   int rows = num_vert, cols = num_vert;
   MatrizAdj = new int*[rows];
   for (int i = 0; i < rows; ++i)
      MatrizAdj[i] = new int[cols];
   for(int i = 0;i<num_vert;++i){
      for(int j = 0;j<num_vert;++j){
         MatrizAdj[i][j]=0;
      }
   }
   std::string str;
   while (getline(myfile, str))
  {
     int a,b;
     myfile >> a >> b;
     MatrizAdj[a-1][b-1] = 1;
  }
}


int min(int a, int b) {
   return (a<b)?a:b;
}

int x = 0;
void Componente(int a, int count[], int low_link[], std::stack<int>&pilha, bool pilhaItem[]) {
   std::vector <int> v1;
   static int time = 0;
   count[a] = low_link[a] = ++time;    
   pilha.push(a);
   pilhaItem[a] = true;    
   for(int b = 0; b<num_vert; b++) {
      if(MatrizAdj[a][b]) {
         if(count[b] == -1) {   
            Componente(b, count, low_link, pilha, pilhaItem);
            low_link[a] = min(low_link[a], low_link[b]);
         } else if(pilhaItem[b])    
            low_link[a] = min(low_link[a], count[b]);
      }
   }
   int x=0,Elemento = 0;
   if(low_link[a] == count[a]) {
      while(pilha.top() != a) {
         Elemento = pilha.top();
         v1.push_back(Elemento);
         pilhaItem[Elemento] = false;    
         pilha.pop();
      }
      Elemento = pilha.top();
      v1.push_back(Elemento);
      ++x;
      pilhaItem[Elemento] = false;
      pilha.pop();
   }
   adj.push_back(v1);
}

void CFC() {
   int count[num_vert], low_link[num_vert];
   bool pilhaItem[num_vert];
   std::stack<int> pilha;
   for(int i = 0; i<num_vert; i++) {    
      count[i] = low_link[i] = -1;
      pilhaItem[i] = false;
   }
   for(int i = 0; i<num_vert; i++)   
      if(count[i] == -1)
         Componente(i, count, low_link, pilha, pilhaItem);
}

int main(int argc, char** argv){
   (void)argc; 
   Matriz(argv[1]);
   CFC();

   std::vector<int> adjNEW[num_vert];
   std::vector<int> OutDeg(num_vert);
   std::vector<int> InDeg(num_vert);
   std::vector<int> Proc[num_vert];

   //Conjunto 1
   for(int i=0;i<num_vert;++i){
      for (int n : adj[i]) {
         for(int y=0;y<num_vert;++y){
            if(MatrizAdj[n][y]==1){
               Proc[i].push_back(y);
            }
         }
      }
   }
   //-----------

   //Conjunto 2
   for(int i=0;i<num_vert;++i){
      for(int b=0;b<num_vert;++b){
         for (int y : Proc[i]) {
            for (int a : adj[b]){
               if(y==a && i!=b){
                  adjNEW[i].push_back(b);
                  OutDeg.at(i) = 1 + OutDeg[i];
                  InDeg.at(b) = 1 + InDeg[b];
               }
            }
         }
      }
   }
   //-----------

   int size =0;
   for(int i=0;i<num_vert;++i){
         if(adj[i].size() > 0)
            size++; 
   }


   int OutMax=0,InMax=0;
   for (int i = 0; i < num_vert; i++){
   if (OutDeg.at(i) > 0){
     OutMax++;}
   }
   OutMax = size - OutMax;

   for (int i = 0; i < num_vert; i++){
   if (InDeg.at(i) > 0)
     InMax++;
   }
   InMax = size - InMax;

   if(InMax>OutMax){
      std::cout << InMax << std::endl;
   }else{
      std::cout << OutMax << std::endl;
   }

}