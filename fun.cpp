#include <vector>
#include <string>
#include <map>

#include<QRgb>
#include <QColor>

#include "fun.h"

using namespace std;

vector<int> pblok_key(int pblok_lenght, int start)
{
    /*
     * Принимает на вход: int длина П-блока, стартовое значение ГСЧ
     *
     * Функция, которая генерирует ключ перестановки
     * Ключ возвращается ввиде массива (vector), где
     * каждому i-ому символу соответствует его новое место
    */
    srand(start);

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

vector <vector<int>> sblok_like_vigener_key(int count, int start)
{
    /*
     * Принимает на вход: int длина S-блока, стартовое значение ГСЧ
     *
     * Генерирует случайные числа по модулю 256, которые будут являться элементами ключа
     * key[i] = x, где x -> [0..255]
     * Принимает размер ключа, возвращает массив с случайными числами
    */
    srand(start);

    vector <vector<int>> key;
    for (int i = 0; i < 3; i++)
    {
        int temp;
        vector<int> temp_key;
        for (int j = 0; j < count; j++)
        {
            temp = rand() % 256;
            temp_key.push_back(temp);
        }
          key.push_back(temp_key);
    }

    return key;
}

vector<QRgb> pblok_use(vector<QRgb> &original, vector<int> &key)
{
    /*
    Применяет pblok к массиву с пикселями. Возвращает уже перемешанный
    */
    vector<QRgb> p_pixel;
    QRgb temp;
    int key_size = key.size();
    for (int i = 0; i < key_size; i++)
    {
        temp = original[key[i]];
        p_pixel.push_back(temp);
    }
    return p_pixel;
}

vector<QRgb> sblok_like_vigener_use(vector<QRgb> &data, vector<vector<int>> &key)
{
    /*
     * Принимает массив QRgb пикселей и vector< vector <key>> Ключ
     * Шифр Виженера. Каждый цвет пикселя складывается с соответствующим ключом в массиве ключей key
     * Возвращает массив QRgb
     *
     *
    */

    int data_size = data.size();

    for (int i = 0; i < data_size; i++)
    {
        // Способ работы с пикселем - QColor
        // Каждую составляющую складывает с ключом
        QColor temp = QColor(data[i]);
        int red = (temp.red() + key[0][i%key[0].size()]) % 256; // Первый ключ соответствует red
        temp.setRed(red);
        int green = (temp.green() + key[1][i%key[1].size()]) % 256; // Второй green
        temp.setGreen(green);
        int blue = (temp.blue() + key[2][i%key[2].size()]) % 256; // Третий blue
        temp.setBlue(blue);
        data[i] = temp.rgb();
    }

    return data;
}

vector<int> pblok_key_revers(vector<int> &pblok_key)
{
    /*
    Получает на вход p-блок, выводит обратный к нему пблок
    Для каждого возможного элемента в p-блок ищет "обратный к нему"
    Распиши пример на бумажке
    */
    vector<int> revers;
    int i = 0;

    int pblok_key_size = pblok_key.size();

    while (i != pblok_key_size)
    {
        for (int j = 0; j < pblok_key_size; j++)
            if (pblok_key[j] == i)
            {
                revers.push_back(j);
                break;
            }
        i++;
    }
    return revers;
}

vector<QRgb> sblok_like_vigener_reverse(vector<QRgb> &data, vector<vector<int>> &key)
{
    /*
     * Принимает массив QRgb пикселей и vector< vector <key>> Ключ
     * Возвращает массив QRgb
     * a + b (mod n) = c
     * c - b (mod n) = a
     * В данном случае ищем a, т.к. на входе подается уже зашифрованное изображение
     * Поскольку у нас не конечное поле, то могут быть отрицательные значения, преобразуем к
     * c - b + n (mod n) = a
    */

    int data_size = data.size();

    for (int i = 0; i < data_size; i++)
    {
        // Способ работы с пикселем - QColor
        // Каждую составляющую складывает с ключом
        QColor temp = QColor(data[i]);
        int red = (temp.red() - key[0][i%key[0].size()] + 256) % 256; // Первый ключ соответствует red
        temp.setRed(red);
        int green = (temp.green() - key[1][i%key[1].size()] + 256) % 256; // Второй green
        temp.setGreen(green);
        int blue = (temp.blue() - key[2][i%key[2].size()] + 256) % 256; // Третий blue
        temp.setBlue(blue);
        data[i] = temp.rgb();
    }

    return data;
}

long long int prostoe_chislo(long long int max)
{
    long long int a = 0;

    while (1)
    {
        a = rand() % max;

        if (prostoe(a))
        {
            break;
        }
    }
    return a;
}

long long int take_d(long long int e, long long int phi)
{
    long long int d = 3;
    while (1)
    {
        if ((e*d) % (phi) == 1)
        {
            break;
        }
        d++;
    }
    return d;
}

bool prostoe(long long int n)
{
    if (n < 3)
        return false;
    for (int i = 2; i <= sqrt(n); i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

vector <int> crypt(string s1, int e, int n)
{
    vector <int> result;
    for (int i = 0; i < (int)s1.size(); i++)
    {
        int c = 1;
        int j = 0;
        unsigned int ASCIIcode = (unsigned int)s1[i];
        while (j < e)
        {
            c = c*ASCIIcode;
            c = c%n;
            j++;
        }
        result.push_back(c);
        //cout << c << " ";
    }
    //cout << endl;
    return result;
}

string decrypt(vector <int> crypted, int d, int n)
{
    string s1="";
    for (int i = 0; i < (int)crypted.size(); i++)
    {
        int m = 1;
        int j = 0;
        while (j < d)
        {
            m = m * crypted[i];
            m = m % n;
            j++;
        }
        //unsigned int temp = m;
        char ch = m;
        s1 = s1 + ch;
    }
    //cout << "TEST: " << s1;
    return s1;
}
