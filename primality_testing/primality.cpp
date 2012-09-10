#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

long long powerMod(long long base, long long exp, long long mod)
{
	long long ret = 1;
	long long cpy = exp;
	int bits = 0;	

	while(cpy > 0)
	{
		bits++;
		cpy = cpy >> 1;
	}

	int bitsConst = bits;

	while(bits > 0)
	{

		ret = ret * ret % mod; 
	
		if( (exp >> (bits - 1)) & 1 == 1)
		{
			ret = base * ret % mod;
		}

		bits--;
	}

	return ret;
}

bool fermat(long long prime, int retryCount = 20)
{
	int a = 0;
	for(int i=0;i<retryCount;i++)
	{
		//a = (rand() % (prime - 1)) + 1;
		a = rand() % prime;

		if(a < 1)
		{
			i--;
			continue;
		}

		if(powerMod(a, prime - 1, prime) != 1)
		{
			return false;
		}
	}

	return true;
}

int inline largeFactorTwo(long long n)
{
	while(n % 2 == 0) n = n >> 1;
	return n;
}

bool millerRabin(long long prime, int retryCount = 20)
{
	int s = largeFactorTwo(prime - 1);
	int d = prime / pow(2, s);
	int a, x;

	while(retryCount-- > 0)
	{
		a = rand() % prime;

		if(a < 1) 
		{
			retryCount++;
			continue;
		}	

		x = powerMod(a, d, prime);

		int exp = d;

		while(exp != prime - 1 && x != 1 && x != prime - 1)
		{
			x = x * x % prime;
			exp = exp * 2;
		}
	
		if(x != prime - 1 && exp % 2 == 0)
			return false;
	}

	return true;	
}

int main(int argc, char **argv)
{
	srand(time(0));
	long long prime = 0;
	cout << "Enter Prime: ";
	cin >> prime;

	if(millerRabin(prime))
		cout << "Miller-Rabin Prime!" << endl;
	else
		cout << "Miller-Rabin Composite" << endl;

	if(fermat(prime))
		cout << "Fermat Prime!" << endl;
	else
		cout << "Fermat Composite" << endl;
	

	cin.get();
	return 0;
}