#ifndef MODULE1_H
#define MODULE1_H

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
struct RSA {
	/*
	RSA. Необходимы p,q,fi,e,d
	Хранит всё. Избыточно, но все пригодится
	vector<int> d создан для того, чтобы пользователь сам мог выбрать пару ключей e, d
	Вдруг не понравятся?..
	*/
	int p;
	int q; 
	int n;  // n = p*q 
	int fi; // fi = (p-1)(q-1)
	int e;  // 1 < e < fi
	int d;  // d*e = 1(mod fi) 
};

int NOD(int a, int b);
string int_into_string(int value);

vector<int> pblok_key (int pblok_lenght);
vector<int> sblok_like_vigener_key(int count);
RSA RSA_key(int p, int q);

vector<char> get_data(string addres);

pixel get_one_pixel(string addres, int byte_seek);
vector<pixel> get_all_pixels(string addres);
vector<pixel> get_some_pixel(string addres, int seek, int count);

vector<pixel> use_pblok(vector<pixel> original, vector<int> key);

vector<char> sblok_like_cesar(vector<char>* data, int key);
vector<char> sblok_like_vigener(vector<char>* data, vector<int>* k);
#endif