#ifndef MODULE1_H
#define MODULE1_H

using namespace std;

int NOD(int a, int b);

vector<int> pblok_key (int pblok_lenght, int start);                // Генерация ключа P
vector<QRgb> pblok_use(vector<QRgb> &original, vector<int> &key);   // Шифврование Р
vector<int> pblok_key_revers(vector<int> &pblok_key);               /* Генерация ключа для расшифровывания Р;
                                                                     * Для расшифровывания применяется pblok_use с реверсным ключом
                                                                     */


/* Используется в качестве замены (S) несколько кривой Виженер
 * Будет использоваться, пока кто-нибудь не перепишет его
 */
vector<vector<int>> sblok_like_vigener_key(int count, int start);                      // Ключ S
vector<QRgb> sblok_like_vigener_use(vector<QRgb> &data, vector<vector<int>> &key);     // Шифрование S
vector<QRgb> sblok_like_vigener_reverse(vector<QRgb> &data, vector<vector<int>> &key); // Расшифровывание S
#endif
