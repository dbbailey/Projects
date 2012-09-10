#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

long long powerMod(long long base, long long exp, long long mod)
{
	long long ret = 1;
	int bits = log(exp) / log(2) + 1;
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

bool millerRabin(long long w, int retryCount = 20)
{
	if((w & 1) == 0) return false;
	
	int cpy = w - 1, a = 0;
	while(!(cpy & 1))
	{
		cpy >>= 1;
		a++;
	}

	int m = (w - 1) / pow(2, a);

	for(int iter=0;iter<retryCount;iter++)
	{
		int a = rand() % (w - 4) + 2;

		int z = powerMod(a, m, w);
		if(z == 1 || z == w - 1) 
			continue;

		bool cont = false;
		for(int j=1;j<a;j++)
		{
			z = (z * z) % w;
			if(z == w - 1)
			{
				cont = true;
				break;
			}

			if(z == 1) return false;
		}

		if(cont) continue;

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
