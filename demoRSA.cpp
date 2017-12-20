#include <iostream> 
#include <cmath>
#include <vector>

#define RAND_MAX 90000

#include <cstdlib>
#include <ctime>

using namespace std;

long long int prostoe_chislo(long long int max);
long long int take_d(long long int e, long long int phi);
bool prostoe(long long int n);

int main()
{
	srand(time(0));
	int p = prostoe_chislo(200);
	int q = prostoe_chislo(200);
	cout << p << " " << q << endl;
	long long int n = p*q;
	long long int phi = (p - 1)*(q - 1);
	long long int e = prostoe_chislo(phi);
	cout << e << " " << n << endl;
	long long int d = take_d(e, phi);
	cout << d << " " << n << endl;
	return 0;
}

long long int prostoe_chislo(long long int max)
{
	long long int a = 0;
	
	while (1)
	{
		a = rand() % max;

		if (prostoe(a))
		{
			break;
		}
	}
	return a;
}

long long int take_d(long long int e, long long int phi)
{
	long long int d = 3;
	while (1)
	{
		if ((e*d) % (phi) == 1)
		{
			break;
		}
		d++;
	}
	return d;
}

bool prostoe(long long int n)
{
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}
