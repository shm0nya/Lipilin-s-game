#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

#include "fun.h"
#include "config.h"
#include "algebra_string.h"

int main()
{
	extern int pblok_lenght;
	extern int sblok_lenght;
	ifstream in("in.bmp");
	ofstream out("out.bmp");

	string_int test("313");
	int c = test.value_into_int();
	cout << c;
	string str = int_into_string(0);
	cout << ' ' << str;
	return 0;
}