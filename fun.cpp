#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>

using namespace std;

#include "fun.h"
#include "config.h"

vector<int> pblok_key(int pblok_lenght)
{
	/*
	Функция, которая генерирует ключ перестановки
	Ключ возвращается ввиде массива (vector), где
	каждому i-ому символу соответствует его новое место
	*/
	vector<int> key;
	for (int i = 0; i < pblok_lenght; i++)
		key.push_back(i);

	int temp;
	for (int i = 0; i < pblok_lenght; i++)
	{
		temp = rand() % pblok_lenght;
		swap(key[i], key[temp]);
	}

	return key;
}
vector<int> sblok_like_vigener_key(int count)
{
	/*
	Генерирует случайные числа по модулю 256, которые будут являться элементами ключа
	key[i] = x, где x -> [0..255]
	Принимает размер ключа, возвращает массив с случайными числами
	*/
	vector<int> key;
	int temp;
	for (int i = 0; i < count; i++)
	{
		temp = rand() % 256;
		key.push_back(temp);
	}

	return key;
}

vector<char> get_data(string addres)
{
	/*
	char имеет размер 1 байт по стандарту. Побайтово
	(по одному char) считываем файл метотдом get,
	возвращает массив (vector) байт

	принимает string - адрес файла. По дефолту ищет в папке проект (in.bmp)
	*/

	ifstream in(addres);
	char temp;
	vector<char> data;
	while (!in.eof())
	{
		in.get(temp);
		data.push_back(temp);
	}

	return data;
}

pixel get_one_pixel(string addres, int byte_seek)
{
	/*
	Позволяет получить один пиксель из изображения c
	определенным смещением. Смещение в байтах (1 пиксель 3 байта)
	*/
	ifstream in(addres);
	in.seekg(byte_seek);
	pixel temp;
	in.get(temp.red);
	in.get(temp.green);
	in.get(temp.blue);
	return temp;
}

vector<pixel> get_all_pixels(string addres)
{
	/*
	Возвращает массив (vector) пикселей. При этом пропускает bmp заголовок
	bmp заголовок хранится в первых 54 байтах. В моем изображении из paint
	тоже так было 
	http://vbzero.narod.ru/chapter3/article_2.htm
	*/
	ifstream in(addres);
	int seek = 54;
	pixel temp;
	vector<pixel> data;
	while (!in.eof())
	{
		in.get(temp.red);
		in.get(temp.green);
		in.get(temp.blue);
		data.push_back(temp);
	}

	return data;
}

vector<pixel> get_some_pixel(string addres, int seek, int count)
{
	/*
	Считывает определенное количество пикселей из файла из определенного места файла.
	Возвращает массив (vector) из этих пикселей
	*/
	vector<pixel> data;
	ifstream in(addres);
	in.seekg(seek);

	pixel temp;
	for (int i = 0; i < count; i++)
	{
		in.get(temp.red);
		in.get(temp.green);
		in.get(temp.blue);
		data.push_back(temp);
	}

	return data;
}

vector<pixel> use_pblok(vector<pixel>* original_ad, vector<int>* key_ad)
{
	/*
	Применяет pblok к массиву с пикселями. Возвращает уже перемешанный
	*/
	vector<pixel> p_pixel;
	vector<pixel> original = *original_ad;
	vector<int> key = *key_ad;
	pixel temp;
	for (int i = 0; i < key.size(); i++)
	{
		temp = original[key[i]];
		p_pixel.push_back(temp);
	}
	return p_pixel;
}

vector<char> sblok_like_cesar(vector<char>* data, int key)
{
	/*
	Простой шифр Цезаря. Каждый байт складывается с ключом по модулю 256
	*/
	vector<char> new_data = *data;
	for (int i = 0; i < new_data.size(); i++)
		new_data[i] = (new_data[i] + key) % 256;

	return new_data;
}

vector<char> sblok_like_vigener(vector<char>* data, vector<int>* k)
{
	/*
	Шифр Виженера. Каждый байт складывается с числом, являющимся элементом ключа по модулю 256.
	Если длина ключа больше, чем количество байт, то, когда ключ "заканчивается",
	сложение продолжается с 0-ого элемента ключа
	*/
	vector<char> new_data = *data;
	vector<int> key = *k;
	for (int i = 0; i < new_data.size(); i++)
		new_data[i] = (new_data[i] + key[i%key.size()]) % 256;

	return new_data;
}