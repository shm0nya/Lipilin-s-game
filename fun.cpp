#include <vector>
#include <string>
#include <map>

#include<QRgb>
#include <QColor>

using namespace std;

#include "fun.h"

int NOD(int a, int b)
{
    /*
    Ищет остатки от деления. см Алгоритм Евклида
    https://habrahabr.ru/sandbox/60131/
    */
    while (a && b)
        if (a >= b)
            a %= b;
        else
            b %= a;
    return a | b;
}

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
    for (int i = 0; i < key.size(); i++)
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
    */
    for (int i = 0; i < data.size(); i++)
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
    while (i != pblok_key.size())
    {
        for (int j = 0; j < pblok_key.size(); j++)
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
    for (int i = 0; i < data.size(); i++)
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

int count_simbols_befor(QString data, char befor)
{
    bool do_it = true;
    int i = 0;

    while (do_it)
    {
        if (QCharRef(data[i]).toLatin1() != befor)
            i++;
        else
            do_it = !do_it;
    }

    return i;
}

QString cut_string_befor_simbol(QString &str, char befor)
{
    int temp;
    QString temp_str;

    temp_str = "";
    temp = count_simbols_befor(str, befor);
    temp_str.replace(0, temp, str);
    str.remove(0, temp+1); // Компенсация пробела

    return temp_str;
}
