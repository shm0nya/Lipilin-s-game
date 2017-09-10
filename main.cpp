#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

#include "fun.h"
#include "config.h"


int main()
{
	/*
	ofstream out("out2.bmp");
	vector<char> data = get_data("in.bmp");
	for (int i = 0; i < data.size(); i++)
		out << data[i];
	*/

	/*
	ofstream out("test.pixel");
	pixel pi = get_one_pixel("in.bmp", 0);
	out<<pi.red<<pi.green<<pi.blue;
	*/
	vector<int> key = pblok_key(8);
	ifstream in("in.bmp");
	ofstream out("out.bmp");
	char t;
	for (int i = 0; i < 54; i++)
	{
		in.get(t);
		out << t;
	}

	vector<pixel> temp, next;
	int seek = 54;
	while (seek!=100*100*3 + 54)
	{
		temp = get_some_pixel("in.bmp", seek, 8);
		next = use_pblok(temp, key);
		for (int i = 0; i < next.size(); i++)
		{
			out << next[i].red;
			out << next[i].green;
			out << next[i].blue;
		}
		seek = seek + 8*3;
	}


	return 0;
}
