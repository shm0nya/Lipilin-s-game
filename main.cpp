#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

#include "fun.h"
#include "config.h"


int main()
{
	extern int pblok_lenght;
	extern int sblok_lenght;
	ifstream in("in.bmp");
	ofstream out("out.bmp");

	RSA test;
	test = RSA_key(3, 11);

	int m = 3;
	double c = pow(m, test.e);
	cout << c;
	double m2 = pow(c, test.d);
	cout << m2;

	return 0;
}
