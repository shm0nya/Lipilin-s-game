#ifndef MODULE1_H
#define MODULE1_H

using namespace std;

int NOD(int a, int b);

vector<int> pblok_key (int pblok_lenght);
vector<vector<int>> sblok_like_vigener_key(int count);

vector<QRgb> use_pblok(vector<QRgb> &original, vector<int> &key);

vector<char> sblok_like_cesar(vector<char>* data, int key);
vector<QRgb> sblok_like_vigener(vector<QRgb> &data, vector<vector<int>> &key);
#endif
