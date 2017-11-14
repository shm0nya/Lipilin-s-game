#include "home_window.h"
#include "ui_home_window.h"

home_window::home_window(QString login, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::home_window)
{
    ui->setupUi(this);
    connect(ui->button_send_messege,SIGNAL(clicked()),this, SIGNAL(change_wnd_to_swnd()));

    login_name = login;
    ui->lbl_login_value->setText(login_name);
    ui->lbl_level_value->setText("FiRsT Leeeeevel!!!!!!");
    ui->list_users->addItem(login_name);

    socket = new QUdpSocket;
    socket->bind(QHostAddress::AnyIPv4, 65201); // начинаем слушать 65201 порт
    connect(socket, SIGNAL(readyRead()), this, SLOT(NET_datagramm_analysis())); // ловим udp дейтаграммы и анализируем
}

home_window::~home_window()
{
    delete ui;
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

void home_window::add_new_player(QString new_player_login)
{
    ui->list_users->addItem(new_player_login);
}

void home_window::NET_datagramm_analysis()
{
    QByteArray buffer; //Дейтаграмма
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender; // IP отправителя
    quint16 senderPort; // Port

    socket->readDatagram(buffer.data(), buffer.size(),&sender, &senderPort);
    QString data(buffer);

    char who = QCharRef(data[0]).toLatin1();
    char action = QCharRef(data[1]).toLatin1();
    data.remove(0, 2); // Удаляются первые 2 символа т.к. они уже записаны в who, data

    //анализируем дейтаграмму
    switch (action) {
     case 'S':
        NET_start_messeges_phase_1(data);
        break;

    case 's':
        NET_start_messeges_phase_2(data);
        break;

    case 'g':
        game_must_go_on();
        break;
    }
}

void home_window::NET_start_messeges_phase_1(QString messeges)
{
    QString temp_str;

    /* Вытаскиваем n */
    temp_str = cut_string_befor_simbol(messeges, ' ');
    n = temp_str.toInt();

    /* Вытаскиваем m */
    temp_str = cut_string_befor_simbol(messeges, ' ');
    m = temp_str.toInt();

    /* Подготовка хранилища векторов */
    source_img.resize(n);
    for (int i =0; i<n; i++)
        source_img.resize(m);

    /* Вытаскиваем всё остальное */
    for (int i = 0; i < n; i++)
    {
        vector<QString> temp_vec;
        for (int j = 0; j < m; j++)
        {
            temp_str = cut_string_befor_simbol(messeges, ' ');
            temp_vec.push_back(temp_str);
        }
        code_messege.push_back(temp_vec);
    }

}

void home_window::NET_start_messeges_phase_2(QString data)
{
    QString temp_str;
    int i;
    int j;

    temp_str = cut_string_befor_simbol(data, ' ');
    i = temp_str.toInt();

    temp_str = cut_string_befor_simbol(data, ' ');
    j = temp_str.toInt();

    QImage img;
    QByteArray data_for_img; // Костыльно, но это С++, где всё привязно к типам данных. А вот в python... (дальше срач)
    data_for_img.append(data);
    img.loadFromData(data_for_img);
    source_img[i][j] = img;
}

void home_window::game_must_go_on()
{
    create_img_buttons(source_img, n, m);
}
