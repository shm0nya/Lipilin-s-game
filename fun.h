#ifndef MODULE1_H
#define MODULE1_H

#include<QRgb>
#include <QColor>
#include <QImage>

#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <cstdlib>
#include <ctime>

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

/* assimetry from Stas */
long long int prostoe_chislo(long long int max);
long long int take_d(long long int e, long long int phi);
long long int take_e(long long int phi);
int gcd(int a,int b);
bool prostoe(long long int n);
vector <int> crypt(vector<int> s1, int e, int n);
vector<int> decrypt (vector <int> crypted, int d, int n);

vector <int> image_to_vector(QImage img);
QImage set_vector_at_image(QImage img, vector<int> data);

vector<int> crypt_rsa2(vector<int> data, int e, int n);
vector<int> decrypt_rsa2(vector<int> data, int e, int n);

QImage encrypt_image_p(QImage encrypted_image, std::vector<int> pb_key); /* Принимает QImage - изображение, которое надо шифровать,
                                                                          *           pb_key - ключ блока перестановки
                                                                          * Возвращает зашифрованный QImage
                                                                          * Алгоритм:
                                                                          *            Каждый пиксель задается своими координтами: высота и ширина.
                                                                          *            Используется цикл со счетчиком count от нуля до Высота*Ширина изображения.
                                                                          *            QImage.pixel(wid,hei)=Qmage.pixel(целая часть от деления count на ширину,
                                                                          *                                      остаток от деления count на ширину)
                                                                          *
                                                                          *            Считывается блок пикселей размером с длину блока, заданную пользователем,
                                                                          *            перемешивается, после чего записывается обратно в изображение.
                                                                          */

QImage encrypt_image_s(QImage encrypted_image, std::vector<vector<int>> sb_key);
                                                                            /* Принимает QImage - изображение, которое надо шифровать,
                                                                             *           pb_key - ключ блока перестановки
                                                                             * Возвращает зашифрованный QImage
                                                                             * Алгоритм аналогичен "encrypt_image_p"
*/
QImage decrypt_image_s(QImage encrypted_image, std::vector<vector<int>> sb_key); /* Делает то же, что и encrypt, только использует sblok_like_vigener_revers*/
#endif
