#include <iostream>
#include <cstdlib>
#include <cmath>
#include <string>

#define uint32 unsigned int

uint32 base26Val(std::string val)
{
   int n = val.length();
   uint32 retVal = 0;
   
   for (int i=0;i<val.length();i++)   
      retVal += std::pow(26, n-i-1)*(val[i]-'A');   
      
   return retVal;
}

bool testPlate(std::string plate)
{
   uint32 txtVal = base26Val(plate.substr(0,3));
   uint32 numVal = std::stoi(plate.substr(4,4), nullptr);

   int diff = txtVal-numVal;

   if (std::abs(diff) <= 100)
      return true;
   else
      return false;
}

int main(int argc, char** argv)
{
   int numPlates;
   std::string plate;
   std::cin >> numPlates;
   
   for (int i=0;i<numPlates;i++)
   {
      std::cin >> plate;
      
      if (testPlate(plate))
         std::cout << "nice" << "\n";
      else
         std::cout << "not nice" << "\n";
   }
}