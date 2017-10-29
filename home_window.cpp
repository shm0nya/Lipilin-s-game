#include "home_window.h"
#include "ui_home_window.h"

#include <QMessageBox>

home_window::home_window(QString str_login, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::home_window)
{
    ui->setupUi(this);
    connect(ui->button_send_messege,SIGNAL(clicked()),this, SIGNAL(change_wnd_to_swnd()));

    login_name = str_login;
    ui->lbl_login_value->setText(login_name);
    ui->lbl_level_value->setText("FiRsT Leeeeevel!!!!!!");
    ui->list_users->addItem(login_name);

    soket = new QUdpSocket(this);
    soket->bind(QHostAddress::AnyIPv4, 65201); // начинаем слушать 65201 порт
    connect(soket, SIGNAL(readyRead()), this, SLOT(ready())); // ловим udp дейтаграммы
    UserList = config(); // получаем IP адреса
    StatusOnline(); // становимся онлайн (рассылка UDP пакетов)
}

home_window::~home_window()
{
    delete ui;
}

/*________________Работа с сетью________________*/

void home_window::ready()
{
    QByteArray buffer; //Дейтаграмма
    buffer.resize(soket->pendingDatagramSize());

    QHostAddress sender; // IP отправителя
    quint16 senderPort; // Port

    soket->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);

    QString datagramma (buffer);

    //анализируем дейтаграмму
    if (datagramma.left(6) == "level:")
    {
        QString temp = "";
        datagramma.replace(0, 6, temp);
        level = datagramma;
        ui->lbl_level_value->setText(datagramma);
    }
    else if ((datagramma.left(8) == "1online:") || (datagramma.left(7) == "online:"))
    {
        QString temp = "";
        bool first = false;
        if (datagramma.left(8) == "1online:")
        {
            datagramma.replace(0, 8, temp);
            first = true;
        }
        else if (datagramma.left(7) == "online:")
             datagramma.replace(0, 7, temp);

        if (UserList[sender.toString()] == "")
        {
            UserList[sender.toString()] = datagramma;
            ui->list_users->addItem(datagramma);
        }
        else
        {
            for (int i = 0; i < ui->list_users ->count(); i++)
            {
                if (UserList[sender.toString()] == ui->list_users->item(i)->text())
                {
                    delete ui->list_users->takeItem(i);
                    break;
                }
            }

            UserList[sender.toString()] = datagramma;
            ui->list_users->addItem(datagramma);
        }

        if (first)
        {
            QByteArray Data;
            Data.append("online:");
            Data.append(login_name);
            soket->writeDatagram(Data,QHostAddress(sender), 65201);
        }
    }
    else
    {
        QImage image;
        image.loadFromData(buffer, "BMP");
    }
}

QMap<QString,QString> home_window::config()
{
    QMap<QString,QString> list;
    QFile file("config.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
            return list;

    QTextStream in(&file);
    while (!in.atEnd())
    {
        QString IPaddress = in.readLine();
        list[IPaddress] = "";
    }
    file.close();
    return list;
}

void home_window::StatusOnline()
{
    for(auto e : UserList.keys())
    {
        QByteArray Data;
        Data.append("1online:");
        Data.append(login_name);
        soket->writeDatagram(Data,QHostAddress(e), 65201);
    }
}

vector <vector<QImage>> cut_image(QImage &image, int n, int m)
{
    vector<vector<QImage>> cut;
    for (int i = 0; i<m; i++)
    {
        vector<QImage> str_image;
        for (int j = 0; j<n; j++)
        {
            QImage temp(100,100,image.format());
            for (int wid = j*100; wid<j*100+100; wid++)
            {
                for (int hei = i*100; hei<i*100+100; hei++)
                {
                    QRgb t = image.pixel(wid,hei);
                    temp.setPixel(wid%100, hei%100, t);
                }
            }
            str_image.push_back(temp);
        }
        cut.push_back(str_image);
    }
  return cut;
}

void home_window::create_img_buttons(vector<vector<QImage>> &cut, int n, int m)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            QPB_modify *pb = new QPB_modify;
            pb->reverse_img = cut[i][j];
            pb->i = i;
            pb->j = j;
            pb->was_opening = false;

            QSize button_size(50,50);
            pb->setMaximumSize(button_size);
            pb->setMinimumSize(button_size);

            pb->setIcon(QIcon(":/images/question.png"));
            QSize icon_size(40,40);
            pb->setIconSize(icon_size);

            connect(pb, &QPushButton::clicked, [this, pb](){
                QPushButton *pb2 = new QPushButton;
                pb2->setIcon(QPixmap::fromImage(pb->reverse_img));
                pb2->setIconSize(pb->size());
                pb2->setMaximumSize(pb->size());
                emit i_opend(pb->reverse_img, pb->i, pb->j);
                ui->componate_custom_buttons_img->addWidget(pb2, pb->i, pb->j);
            });

            emit do_it(pb->i, pb->j);
            ui->componate_custom_buttons_img->addWidget(pb,i,j);
        }
}


void home_window::on_pushButton_clicked()
{
    original_img.load(":/images/work image.png");
    vector<vector<QImage>> cut = cut_image(original_img,5,5);
    create_img_buttons(cut, 5,5);
}
