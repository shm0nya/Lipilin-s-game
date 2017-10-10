#ifndef MODULE1_H
#define MODULE1_H

using namespace std;

int NOD(int a, int b);

vector<int> pblok_key (int pblok_lenght);
vector<QRgb> pblok_use(vector<QRgb> &original, vector<int> &key);
vector<int> pblok_key_revers(vector<int> &pblok_key);


vector<vector<int>> sblok_like_vigener_key(int count);
vector<QRgb> sblok_like_vigener_use(vector<QRgb> &data, vector<vector<int>> &key);
vector<QRgb> sblok_like_vigener_reverse(vector<QRgb> &data, vector<vector<int>> &key);
#endif
