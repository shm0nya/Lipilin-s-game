#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#include "fun.h"
#include "config.h"


int main()
{
	extern int pblok_lenght;
	extern int sblok_lenght;
	ifstream in("in.bmp");
	ofstream out("out_S_like-vigener-32.bmp");

	char temp;
	vector<char> data;

	for (int i = 0; i < 54; i++)
	{
		in.get(temp);
		out << temp;
	}

	while (!in.eof())
	{
		in.get(temp);
		data.push_back(temp);
	}

	vector<char> uns;
	vector<int> key = sblok_like_vigener_key(sblok_lenght);
	uns = sblok_like_vigener(&data, &key);
	//uns = sblok_like_cesar(&data, 100);
	for (int i = 0; i < uns.size(); i++)
		out << uns[i];

	return 0;
}
