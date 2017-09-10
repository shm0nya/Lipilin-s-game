#include "home_windows.h"
#include "ui_home_windows.h"

#include <QBuffer>
#include <QFile>

Home_windows::Home_windows(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home_windows)
{
    ui->setupUi(this);

    //connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(Test()));
    ui->label_level->setText(level);

    soket = new QUdpSocket(this);
    soket->bind(QHostAddress::AnyIPv4, 65201); // начинаем слушать 65201 порт
    connect(soket, SIGNAL(readyRead()), this, SLOT(ready())); // ловим udp дейтаграммы
}

Home_windows::~Home_windows()
{
    delete ui;
}

void Home_windows::setLogin(const QString& str_login)
{
    login_name = str_login;
    ui->label_login->setText(str_login);
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
        ui->label_level->setText(datagramma);
    }
    else
    {
        QImage image;
        image.loadFromData(buffer, "BMP");
        ui->label_2->setPixmap(QPixmap::fromImage(image));
        ui->label_2->setScaledContents(true);
    }
}
