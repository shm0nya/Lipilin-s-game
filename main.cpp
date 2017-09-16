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
	test.add("900");
	cout  << test.get_value();

	return 0;
}