#include <iostream>

void computeBees(int N, unsigned int& M, unsigned int& F)
{  
   unsigned int Fp;
   unsigned int Mp;
   
   M = 0;
   F = 1;
   
   for (int i = 0;i < N;i++)
   {
      Fp = F;
      Mp = M;
      
      F = 1 + Mp;
      M = Fp + Mp;
   }
}


int main(int argc, char** argv)
{
   int N = 0;
   unsigned int M, F;
   int flag = 0;
   
   while(true)
   {
      std::cin >> N;      
      if (N < 0) break;       
      
      computeBees(N, M, F);            
      std::cout << M << " " << (M+F) << "\n";           
   }  
}