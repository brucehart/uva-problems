#include <math.h>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#define MAX_DIGITS 	1000

int multiply(int a, std::vector<int> &resultDigits, int &effDigits)
{
	int carry = 0;

	for(int i=0;i<effDigits;i++)
	{
		int p = resultDigits[i]*a + carry;

		carry = p/10;
		resultDigits[i] = p%10;
	}

	while (carry)
	{
		resultDigits[effDigits] = carry%10;
		carry = carry/10;
		effDigits++;
	}
}

std::vector<int> factorial(int n)
{
	std::vector<int> resultDigits(1000,0);
	int effDigits = 1;

	resultDigits[0] = 1;

	for (int j=2;j<=n;j++)
	{
		multiply(j, resultDigits, effDigits);
	}

	return resultDigits;
}

std::vector<int> computeStats(std::vector<int> largeNum)
{
	std::vector<int> retVal(10,0);

	int i = largeNum.size()-1;

	while (i > 0 && largeNum[i] == 0)
		i--;

	while (i >= 0)	
	{
		retVal[largeNum[i]] += 1;
		i--;
	}

	return retVal;
}


int main(int argc, char** argv)
{
	int n;

	while(std::cin >> n)
	{
		if (n <= 0) break;

		std::vector<int> stats = computeStats(factorial(n));

		std::cout << n << "! --";

		for (int i=0;i<10;i++)
		{
			if (i%5 == 0)
				std::cout << "\n ";

			std::cout << "(" << i << ") " << stats[i] << " ";
		}

		std::cout << "\n";
	}
	
}