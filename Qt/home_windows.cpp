#include "home_windows.h"
#include "ui_home_windows.h"

#include <QBuffer>
#include <QFile>

Home_windows::Home_windows(QString str_login, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_windows)
{
    login_name = str_login;
    ui->setupUi(this);

    ui->label_level->setText(level);
    ui->label_login->setText(login_name);
    ui->listWidget->addItem(login_name);

    ui->pushButton->setStyleSheet( " background-color: green; " ); // ЗЁЛЕНАЯ КНОПКА

    soket = new QUdpSocket(this);
    soket->bind(QHostAddress::AnyIPv4, 65201); // начинаем слушать 65201 порт
    connect(soket, SIGNAL(readyRead()), this, SLOT(ready())); // ловим udp дейтаграммы
    UserList = config(); // получаем IP адреса
    StatusOnline(); // становимся онлайн (рассылка UDP пакетов)
}

Home_windows::~Home_windows()
{
    delete ui;
}

/*
void Home_windows::Test()
{


    QFile file("D:\\1.bmp");
    file.open(QIODevice::ReadOnly);

    QByteArray Data = file.readAll();
    file.close();




    QByteArray Data;
    Data.append("level:5");

    soket->writeDatagram(Data,QHostAddress("192.168.1.102"), 65201);
}
*/
void Home_windows::ready()
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
        ui->label_level->setText(datagramma);
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
            ui->listWidget->addItem(datagramma);
        }
        else
        {
            for (int i = 0; i < ui->listWidget ->count(); i++)
            {
                if (UserList[sender.toString()] == ui->listWidget->item(i)->text())
                {
                    delete ui->listWidget->takeItem(i);
                    break;
                }
            }

            UserList[sender.toString()] = datagramma;
            ui->listWidget->addItem(datagramma);
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
        //ui->label_2->setPixmap(QPixmap::fromImage(image));
        //ui->label_2->setScaledContents(true);
    }
}

QMap<QString,QString> Home_windows::config()
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

void Home_windows::StatusOnline()
{
    for(auto e : UserList.keys())
    {
        QByteArray Data;
        Data.append("1online:");
        Data.append(login_name);
        soket->writeDatagram(Data,QHostAddress(e), 65201);
    }
}
