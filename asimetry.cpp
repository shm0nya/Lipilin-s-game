#include "asimetry.h"
#include "ui_asimetry.h"

#include <cmath>
#include <vector>

#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

long long int prostoe_chislo(long long int max);
long long int take_d(long long int e, long long int phi);
bool prostoe(long long int n);
vector <int> crypt(string s1, int e, int n);
string decrypt(vector <int> crypted, int d, int n);

asimetry::asimetry(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::asimetry)
{
    ui->setupUi(this);
    init_bd();
    ui->progress_bar_exchange->setVisible(false);
}

asimetry::~asimetry()
{
    delete ui;
}

void asimetry::init_bd()
{
    /* База данных ключей для RSA
     * Столбцы:
     * | p | q | n | f_n | e | d |
     */

    int count = 1;      // Количество ключей
    keys_bd.resize(count);   // Выделение памяти под них

    /* Инициализация */
    keys_bd[0] = {"7", "13", "91", "72", "5", "91"};
}

void asimetry::on_button_generate_clicked()
{

    srand(time(0));
    int p = prostoe_chislo(100);
    int q = prostoe_chislo(100);

    long long int n = p*q;
    long long int phi = (p - 1)*(q - 1);
   long long int e = prostoe_chislo(phi);

    long long int d = take_d(e, phi);

    QString s = QString::number(p);
    ui->lbl_p_value->setText(s);
    s = QString::number(q);
    ui->lbl_q_value->setText(s);
    s = QString::number(n);
    ui->lbl_n_value->setText(s);
    s = QString::number(phi);
    ui->lbl_f_n_value->setText(s);
    s = QString::number(e);
    ui->lbl_e_value->setText(s);
    s = QString::number(d);
    ui->lbl_d_value->setText(s);

    flag_key_generated = true;
}

void asimetry::on_button_exchange_clicked()
{
    if (!flag_key_generated)
    {
        QMessageBox::information(this, "error", "Ключи не сгенерированы");
        return;
    }

    ui->progress_bar_exchange->setVisible(true);

    for (int i = 0; i < 100; i++)
    {
        QEventLoop loop;
        QTimer::singleShot(mc, &loop, SLOT(quit()));
        loop.exec();
        loop.exit();
        ui->progress_bar_exchange->setValue(i+1);
    }

    ui->progress_bar_exchange->setVisible(false);
    ui->lbl_status_value->setText("Ключи получены");

    emit this->keys_was_generated();
}

void asimetry::on_button_back_clicked()
{
    emit this->from_rsa_to_home_wnd();
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
    for (int i = 0; i < s1.size(); i++)
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
    for (int i = 0; i < crypted.size(); i++)
    {
        int m = 1;
        int j = 0;
        while (j < d)
        {
            m = m * crypted[i];
            m = m % n;
            j++;
        }
        unsigned int temp = m;
        char ch = m;
        s1 = s1 + ch;
    }
    //cout << "TEST: " << s1;
    return s1;
}
