#include <iostream> 
#include <cmath>
#include <vector>

#define RAND_MAX 90000

#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

long long int prostoe_chislo(long long int max);
long long int take_d(long long int e, long long int phi);
bool prostoe(long long int n);
vector <int> crypt(string s1, int e, int n);
string decrypt(vector <int> crypted, int d, int n);

int main()
{
	srand(time(0));
	int p = prostoe_chislo(100);
	int q = prostoe_chislo(100);
	cout << p << " " << q << endl;
	long long int n = p*q;
	long long int phi = (p - 1)*(q - 1);
	long long int e = prostoe_chislo(phi);
	cout << e << " " << n << endl;
	long long int d = take_d(e, phi);
	cout << d << " " << n << endl;
	string s1 = "lol";
	vector <int> test = crypt(s1, e, n);
	string s2 = decrypt(test, d, n);
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
	if (n < 3)
		return false;
	for (int i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
			return false;
	}
	return true;
}

vector <int> crypt(string s1, int e, int n)
{
	vector <int> result;
	for (int i = 0; i < s1.size(); i++)
	{
		int c = 1;
		int j = 0;
		unsigned int ASCIIcode = (unsigned int)s1[i];
		while (j < e)
		{
			c = c*ASCIIcode;
			c = c%n;
			j++;
		}
		result.push_back(c);
		//cout << c << " ";
	}
	//cout << endl;
	return result;
}
string decrypt(vector <int> crypted, int d, int n)
{
	string s1="";
	for (int i = 0; i < crypted.size(); i++)
	{
		int m = 1;
		int j = 0;
		while (j < d)
		{
			m = m * crypted[i];
			m = m % n;
			j++;
		}
		unsigned int temp = m;
		char ch = m;
		s1 = s1 + ch;
	}
	//cout << "TEST: " << s1;
	return s1;
}