#ifndef MODULE1_H
#define MODULE1_H

vector<int> pblok_key (int pblok_lenght);
vector<int> sblok_like_vigener_key(int count);

vector<char> get_data(string addres);

struct pixel
{
	/*
	ѕиксель состоит из трех байт: RGB
	“ри байта его описывают
	*/
	char red;
	char green;
	char blue;
};

pixel get_one_pixel(string addres, int byte_seek);
vector<pixel> get_all_pixels(string addres);
vector<pixel> get_some_pixel(string addres, int seek, int count);

vector<pixel> use_pblok(vector<pixel> original, vector<int> key);

vector<char> sblok_like_cesar(vector<char>* data, int key);
vector<char> sblok_like_vigener(vector<char>* data, vector<int>* k);
#endif