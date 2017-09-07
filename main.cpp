#include <iostream>

#include "fun.h"
#include "config.h"

using namespace std;

int main()
{
	test();
	extern int sblok_lenght; /* use extern, if variable in anothe module
							    sblok_lenght on config.cpp
							 */ 
	cout << "sblok lenght = "<<sblok_lenght;
	return 0;
}
