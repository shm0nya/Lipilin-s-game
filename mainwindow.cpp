#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->Login_button->setEnabled(false);
    QRegExp is_login_variable("[a-zA-Z0-9]{1,20}");
    ui->login_edit->setValidator(new QRegExpValidator(is_login_variable, this));
    connect(ui->login_edit,SIGNAL(textChanged(QString)),this,SLOT(ok_enabled()));

    socket = new QUdpSocket(this);
    socket->bind(QHostAddress::AnyIPv4, 65201); // начинаем слушать 65201 порт
    connect(socket, SIGNAL(readyRead()), this, SLOT(NET_datagramm_analysis())); // ловим udp дейтаграммы и анализируем

    user_list["rr"] = "192.168.1.1"; // Для проверки работы "уникальности имени" Не работает, если тестировать одновременно с void MainWindow::NET_a_new_player_come(QString new_player_login)
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rootwindow()
{
    root_wnd = new root_window;
    make_wnd = new make_img_window;

    connect(root_wnd, SIGNAL(show_make_img_with_my_img(QImage, int, int, QString)), this, SLOT(show_make_wnd_to_root(QImage, int, int, QString)));
    connect(root_wnd, SIGNAL(get_rune(int)), this, SLOT(set_rune(int)));
    connect(make_wnd, SIGNAL(rejected()), this, SLOT(if_close_wnd_fo_root()));
    connect(make_wnd, SIGNAL(root_make_new_img(QImage, int, int, QString)), this, SLOT(new_rune_created_root(QImage, int, int, QString)));
    connect(root_wnd, SIGNAL(start()), this, SLOT(NET_send_info_for_start()));

    root_wnd->show();
    this->close();
}

void MainWindow::playerwindow()
{
    QString name_login = ui->login_edit->text();

    home_wnd = new home_window(name_login);
    send_messege_wnd = new send_messege;
    choose_button_wnd = new choose_button;
    make_wnd = new make_img_window;

    connect(send_messege_wnd, SIGNAL(change_wnd_to_homewnd()), this, SLOT(sendmess_wnd__home_wnd()));
    connect(home_wnd, SIGNAL(change_wnd_to_swnd()),this ,SLOT(home_wnd__sendmess_wnd()));

    connect(home_wnd, SIGNAL(do_it(int, int)), this, SLOT(create_pb(int, int)));
    connect(home_wnd, SIGNAL(i_opend(QImage, int, int)), this, SLOT(then_opend_img(QImage, int, int)));
    connect(send_messege_wnd, SIGNAL(show_ch_buttons_sign()), this, SLOT(show_ch_wnd()));
    connect(choose_button_wnd, SIGNAL(i_choose_img(QImage, int, int)),this ,SLOT(then_choosen_img(QImage, int, int)));
    connect(choose_button_wnd, SIGNAL(rejected()), this, SLOT(if_close_wnd()));

    connect(send_messege_wnd, SIGNAL(show_make_img_wnd()),this, SLOT(show_make_wnd()));
    connect(make_wnd, SIGNAL(rejected()), this, SLOT(if_close_wnd()));
    connect(make_wnd, SIGNAL(i_make_img(QImage)), this, SLOT(then_made_img(QImage)));

    home_wnd->show();
    this->close();
}

void MainWindow::ok_enabled()
{
    ui->Login_button->setEnabled(ui->login_edit->hasAcceptableInput());
}

void MainWindow::on_Login_button_clicked()
{   
    if(ui->login_edit->text() == "root")
        rootwindow();
    else
    {
        QByteArray data;
        data.append("0r");
        data.append(ui->login_edit->text());
        socket->writeDatagram(data, QHostAddress(root_address), 65201);
    }
}

void MainWindow::home_wnd__sendmess_wnd()
{
    home_wnd->close();
    send_messege_wnd->show();
}

void MainWindow::sendmess_wnd__home_wnd()
{
    send_messege_wnd->close();
    home_wnd->show();
}

void MainWindow::show_ch_wnd()
{
    send_messege_wnd->setEnabled(false);
    choose_button_wnd->show();
}

void MainWindow::create_pb(int i, int j)
{
    QPB_modify *pb = new QPB_modify;
    QSize button_size(50,50);
    pb->setMaximumSize(button_size);
    pb->setMinimumSize(button_size);

    pb->setIcon(QIcon(":/images/question.png"));
    QSize icon_size(40,40);
    pb->setIconSize(icon_size);

    connect(pb, &QPushButton::clicked, [this, pb](){
        if (pb->reverse_img.isNull())
            QMessageBox::information(this,"Oops", "Я же говорил, что ничего не будет");
        else
            emit choose_button_wnd->i_choose_img(pb->reverse_img, pb->i, pb->j);
    });

    choose_button_wnd->set_button(pb, i, j);
}

void MainWindow::then_choosen_img(QImage img, int i, int j)
{
    send_messege_wnd->user_choose_img(img);
    send_messege_wnd->set_position_of_img(i, j);

    send_messege_wnd->setEnabled(true);
    send_messege_wnd->show();
}

void MainWindow::then_opend_img(QImage img, int i, int j)
{
    choose_button_wnd->open_button(img, i, j);
}

void MainWindow::if_close_wnd()
{
    send_messege_wnd->setEnabled(true);
    send_messege_wnd->show();
}

void MainWindow::show_make_wnd()
{
    send_messege_wnd->setEnabled(false);
    make_wnd->show();
}

void MainWindow::set_rune(int i)
{
    root_wnd->set_temp_rune(make_wnd->paint_picture(make_wnd->get_rune(i),
                                                   make_wnd->get_color(i)));
}

void MainWindow::show_make_wnd_to_root(QImage img, int i, int j, QString str)
{
    root_wnd->setEnabled(false);
    make_wnd->set_rune(img, i, j, str);
    make_wnd->show();
}

void MainWindow::if_close_wnd_fo_root()
{
    root_wnd->setEnabled(true);
}

void MainWindow::new_rune_created_root(QImage img ,int i, int j, QString str)
{
    QPB_modify *pb = new QPB_modify;

    pb->i = i;
    pb->j = j;
    pb->str = str;

    pb->reverse_img = img;
    QSize button_size(50,50);
    pb->setMaximumSize(button_size);
    pb->setMinimumSize(button_size);

    pb->setIcon(QIcon(QPixmap::fromImage(img)));
    QSize icon_size(pb->size());
    pb->setIconSize(icon_size);

    connect(pb, &QPushButton::clicked, [this, pb](){
        emit root_wnd->show_make_img_with_my_img(pb->reverse_img, pb->i, pb->j, pb->str);
    });

    root_wnd->set_rune_at_GL(pb, i, j);
}

void MainWindow::then_made_img(QImage img)
{
    send_messege_wnd->user_choose_img(img);

    send_messege_wnd->setEnabled(true);
    send_messege_wnd->show();
}

void MainWindow::NET_datagramm_analysis()
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
    case 'r':
        if (who == '0') // Отправитель player
            NET_registration_for_root(data ,sender);
        else
            NET_registration_for_player(data);
        break;

    case 'n':
        NET_add_new_player(data);
        break;

    case 'S':
        NET_start_messeges_phase_1(data);
        break;

    case 's':
        NET_start_messeges_phase_2(data);
        break;

    case 'g':
        home_wnd->create_img_buttons(source_img, img_count_n, img_count_m);
        break;
    }
}

void MainWindow::NET_registration_for_root(QString login, QHostAddress sender)
{
    /* Проверка на уникальность адреса */
    QMap<QString, QString>::iterator it;
    QString verdict = "true";

    for (it = user_list.begin(); it!=user_list.end(); it++)
    {
        if (it.key() == login)
        {
            verdict = "false";
            break;
        }
    }

    /* В случае, если уникальный, занесение в БД и оповещение других пользователей */
    if (verdict == "true")
    {
        NET_a_new_player_come(login);
        user_list[login] = sender.toString();
    }

    /* Отправка ответа */
    QByteArray Data;
    Data.append("1r");
    Data.append(verdict);
    socket->writeDatagram(Data, sender, 65201);
}

void MainWindow::NET_registration_for_player(QString verdict)
{
    if (verdict == "true")
        playerwindow();
    else
        QMessageBox::information(this, "Oops", "Такой логин уже занят, попробуй другой");
}

void MainWindow::NET_a_new_player_come(QString new_player_login)
{
    QMap<QString, QString>::iterator it;

    for (it = user_list.begin(); it!=user_list.end(); it++)
    {
        QHostAddress temp_addres(it.value());

        QByteArray Data;
        Data.append("1n");
        Data.append(new_player_login);
        socket->writeDatagram(Data, temp_addres, 65201);
    }
}

void MainWindow::NET_add_new_player (QString login)
{
    home_wnd->add_new_player(login);
}

void MainWindow::NET_send_info_for_start()
{
    QMap<QString, QString>::iterator it;
    int n = root_wnd->get_n();
    int m = root_wnd->get_m();
    QString messege = "";
    vector<QByteArray> datagramms;

    /* В сообщение добавляем n, m*/

    messege = messege + QString::number(n) + ' ';
    messege = messege + QString::number(m) + ' ';

    /* В начале получаем сообщение со строчками следующего вида:
     * "первое_слово второе_слово третье_слово ..."
     */

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            QString temp = root_wnd->get_messege_at_position(i, j);
            messege = messege + temp + ' ';
        }

    if (messege.size() > 65000)
    {
        QMessageBox::information(this, "error" ,"Слишком большие кодовые слова");
        return;
    }

    /* Формируем дейтаграммы */
    QByteArray first_data;
    first_data.append("1S");
    first_data.append(messege);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            QImage temp_img = root_wnd->get_rune_at_position(i, j);
            QByteArray Data;

            QString temp = "1s " + QString::number(i) + ' ' + QString::number(j) + ' ';
            Data.append(temp);

            Data.append((char *)temp_img.bits(),temp_img.byteCount()); // Хз как работает. На чистой магии. Лишь бы скомпилировалось

            datagramms.push_back(Data);
        }

    /* Послыаем пользователям информацию */

    for (it = user_list.begin(); it!=user_list.end(); it++)
    {
        QHostAddress temp_addres(it.value());

        socket->writeDatagram(first_data, temp_addres, 65201);
        sleep(1000);

        for (int i = 0; i < datagramms.size(); i++)
        {
            socket->writeDatagram(datagramms[i], temp_addres, 65201);
            sleep(1000);
        }
    }

    /* Посылаем сигнал старта игры */
    for (it = user_list.begin(); it!=user_list.end(); it++)
    {
        QHostAddress temp_addres(it.value());

        QByteArray Data;
        Data.append("1g");
        socket->writeDatagram(Data, temp_addres, 65201);
    }

}

void MainWindow::NET_start_messeges_phase_1(QString messeges)
{
    QString temp_str;

    /* Вытаскиваем n */
    temp_str = cut_string_befor_simbol(messeges, ' ');
    img_count_n = temp_str.toInt();

    /* Вытаскиваем m */
    temp_str = cut_string_befor_simbol(messeges, ' ');
    img_count_m = temp_str.toInt();

    /* Подготовка хранилища векторов */
    for (int i =0; i<img_count_n; i++)
    {
        vector<QImage> tt_vec(img_count_m);
        source_img.push_back(tt_vec);

    }

    /* Вытаскиваем всё остальное */
    for (int i = 0; i < img_count_n; i++)
    {
        vector<QString> temp_vec;
        for (int j = 0; j < img_count_m; j++)
        {
            temp_str = cut_string_befor_simbol(messeges, ' ');
            temp_vec.push_back(temp_str);
        }
        code_messege.push_back(temp_vec);
    }
}

void MainWindow::NET_start_messeges_phase_2(QString data)
{
    QString temp_str;
    int i;
    int j;

    temp_str = cut_string_befor_simbol(data, ' ');
    i = temp_str.toInt();

    temp_str = cut_string_befor_simbol(data, ' ');
    j = temp_str.toInt();

    QByteArray ba;
    ba.append(temp_str);

    QImage image((uchar *)ba.data(),100,100,QImage::Format_RGB32);
    source_img[i][j] = image;
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
    temp_str = simbols_in_str_at_positions(str, 0, temp);
    str.remove(0, temp+1); // Компенсация пробела

    return temp_str;
}

void MainWindow::on_edit_ip_root_editingFinished()
{
    root_address = ui->edit_ip_root->text();
    ui->lbl_now_use_ip_root->setText(ui->edit_ip_root->text());
}

QString simbols_in_str_at_positions(QString data, int position, int count)
{
    QString unswer = "";
    for (int i = position; i < position + count; i++)
    {
        unswer = unswer + data[i];
    }

    return unswer;
}

void sleep(int t)
{
    QTime time;
    time.start();
    for(;time.elapsed() < t;)
    {
        1+1;
    }
}
