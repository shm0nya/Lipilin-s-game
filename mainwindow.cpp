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

    ui->edit_ip_root->setText(root_address);
    ui->lbl_now_use_ip_root->setText(root_address);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::rootwindow()
{
    flag_is_it_root = true;

    root_wnd = new root_window;
    make_wnd = new make_img_window;

    connect(root_wnd, SIGNAL(show_make_img_with_my_img(QImage, int, int, QString)), this, SLOT(show_make_wnd_to_root(QImage, int, int, QString)));
    connect(root_wnd, SIGNAL(get_rune(int)), this, SLOT(set_rune(int)));
    connect(make_wnd, SIGNAL(rejected()), this, SLOT(if_close_wnd_fo_root()));
    connect(make_wnd, SIGNAL(root_make_new_img(QImage, int, int, QString, QString)), this, SLOT(new_rune_created_root(QImage, int, int, QString, QString)));
    connect(root_wnd, SIGNAL(start()), this, SLOT(NET_send_info_for_start()));

    root_wnd->set_runes_bd_size(make_wnd->get_rune_bd_size());
    root_wnd->set_colors_bd_size(make_wnd->get_colors_bd_size());

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
    intercept_wnd = new interception;

    connect(send_messege_wnd, SIGNAL(change_wnd_to_homewnd()), this, SLOT(sendmess_wnd__home_wnd()));
    connect(home_wnd, SIGNAL(change_wnd_to_swnd()),this ,SLOT(home_wnd__sendmess_wnd()));

    connect(home_wnd, SIGNAL(do_it(int, int)), this, SLOT(create_pb(int, int)));
    connect(home_wnd, SIGNAL(i_opend(QImage, int, int,QString)), this, SLOT(then_opend_img(QImage, int, int, QString)));
    connect(send_messege_wnd, SIGNAL(show_ch_buttons_sign()), this, SLOT(show_ch_wnd()));
    connect(choose_button_wnd, SIGNAL(i_choose_img(QImage, int, int, QString)),this ,SLOT(then_choosen_img(QImage, int, int, QString)));
    connect(choose_button_wnd, SIGNAL(rejected()), this, SLOT(if_close_wnd()));

    connect(send_messege_wnd, SIGNAL(show_make_img_wnd()),this, SLOT(show_make_wnd()));
    connect(make_wnd, SIGNAL(rejected()), this, SLOT(if_close_wnd()));
    connect(make_wnd, SIGNAL(i_make_img(QImage, QString)), this, SLOT(then_made_img(QImage, QString)));

    connect(send_messege_wnd, SIGNAL(player_send_messege(QImage,QImage,QString,int,QString,int,int,int, QString)),
            this, SLOT(test_player_image(QImage,QImage,QString,int,QString,int,int,int, QString)));

    connect(home_wnd, SIGNAL(show_intercept_wnd_please()), this, SLOT(show_intercept_window()));
    connect(intercept_wnd, SIGNAL(homecomig()), this, SLOT(back__homecoming()));
    connect(home_wnd, SIGNAL(i_want_intercept(QString)), this, SLOT(NET_send_players_inercept_login(QString)));

    connect(intercept_wnd, SIGNAL(go_to_crypto(QImage,QString,int,QString,int,int,int,QString)),
            this, SLOT(send_messege_wnd_on_intercept_value(QImage,QString,int,QString,int,int,int,QString)));

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

    pb->rune_code = runes_code[i][j];

    connect(pb, &QPushButton::clicked, [this, pb](){
        if (pb->reverse_img.isNull())
            QMessageBox::information(this,"Oops", "Я же говорил, что ничего не будет");
        else
            emit choose_button_wnd->i_choose_img(pb->reverse_img, pb->i, pb->j, pb->rune_code);
    });

    choose_button_wnd->set_button(pb, i, j);
}

void MainWindow::then_choosen_img(QImage img, int i, int j, QString code)
{
    send_messege_wnd->user_choose_img(img, code);
    send_messege_wnd->set_position_of_img(i, j);

    send_messege_wnd->setEnabled(true);
    send_messege_wnd->show();
}

void MainWindow::then_opend_img(QImage img, int i, int j, QString code)
{
    choose_button_wnd->open_button(img, i, j, code);
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

void MainWindow::new_rune_created_root(QImage img ,int i, int j, QString str, QString img_code)
{
    QPB_modify *pb = new QPB_modify;

    pb->i = i;
    pb->j = j;
    pb->str = str;
    pb->rune_code = img_code;

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

void MainWindow::then_made_img(QImage img, QString code)
{
    send_messege_wnd->user_choose_img(img, code);

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

    case 'g':
        home_wnd->create_img_buttons(source_img, img_count_n, img_count_m, runes_code);
        break;

    case 'i':
        if (who == '0')
            NET_players_intercept_for_root(data, sender);
        else
            NET_players_intercept_for_player(data);

        break;

    case 'a':
        NET_list_of_user_in_game(data);
        break;

    case 'I':
        NET_add_intercepted_messege(data, buffer);
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

    /* Отправка ответа. Идет в начале, т.к. NET_a_new_player_come отсылает созданному пользователю информацию
     * Он должен быть создан перед тем, как ему отправится информация
     */
    QByteArray Data;
    Data.append("1r");
    Data.append(verdict);
    socket->writeDatagram(Data, sender, 65201);

    /* В случае, если уникальный, занесение в БД и оповещение других пользователей */
    if (verdict == "true")
    {
        NET_a_new_player_come(login, sender.toString());
        user_list[login] = sender.toString();
    }

    if (flag_is_it_root)
    {
        root_wnd->add_new_player(login);
        if (root_wnd->get_flag_game_on())
            NET_send_info_for_player(sender.toString(), messeges, img_code);
    }
}

void MainWindow::NET_registration_for_player(QString verdict)
{
    if (verdict == "true")
        playerwindow();
    else
        QMessageBox::information(this, "Oops", "Такой логин уже занят, попробуй другой");
}

void MainWindow::NET_a_new_player_come(QString new_player_login, QString sender)
{
    QMap<QString, QString>::iterator it;
    QString users = "1a";

    for (it = user_list.begin(); it!=user_list.end(); it++)
    {
        users = users + it.key() + ' ';

        QHostAddress temp_addres(it.value());
        QByteArray Data;
        Data.append("1n");
        Data.append(new_player_login);
        socket->writeDatagram(Data, temp_addres, 65201);
    }

    QByteArray Data;
    Data.append(users);
    socket->writeDatagram(Data, QHostAddress(sender), 65201);
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
    messeges = "";
    img_code = "";

    /* В сообщение добавляем n, m*/

    messeges = messeges + QString::number(n) + ' ';
    messeges = messeges + QString::number(m) + ' ';

    /* В начале получаем сообщение со строчками следующего вида:
     * "первое_слово второе_слово третье_слово ..."
     */

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            QString temp = root_wnd->get_messege_at_position(i, j);
            messeges = messeges + temp + ' ';
        }

    /* Форсмируется строка закодированных изображений */
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            img_code = img_code + root_wnd->get_rune_code_at_position(i, j) + ' ';

    if (messeges.size() + img_code.size() > 65000)
    {
        QMessageBox::information(this, "error" ,"Слишком большие кодовые слова");
        return;
    }

    /* Шлем данные */
    for (it = user_list.begin(); it!=user_list.end(); it++)
    {
        NET_send_info_for_player(it.value(), messeges, img_code);
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

    /* Вытаскиваем слова */
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

    /* Генерируем изображения */
    for (int i = 0; i < img_count_n; i++)
    {
        vector<QImage> temp_vec;
        vector<QString> temp_code_vec;
        for (int j = 0; j < img_count_m; j++)
        {
            temp_str = cut_string_befor_simbol(messeges, ' ');
            temp_code_vec.push_back(temp_str);
            QImage temp_img;
            int ic = cut_string_befor_simbol(temp_str, '_').toInt();
            int jc = temp_str.toInt();
            temp_img = make_wnd->paint_picture_at_code(ic, jc);
            temp_vec.push_back(temp_img);
        }
        source_img.push_back(temp_vec);
        runes_code.push_back(temp_code_vec);
    }
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

void MainWindow::test_player_image(QImage img, QImage enc_img, QString p_key, int p_key_size, QString s_key, int s_key_size, int i, int j, QString algoritm)
{
    if ((i<=0) || (j<=0) || (i > img_count_n) || (j > img_count_m))
    {
        QMessageBox::information(this, "error", "Неправильыне координаты");
        return;
    }

    // В зависимости игра оффлайн или онлайн
    if (root_address == "127.0.0.1")
        send_messege_wnd->players_img_verdict(img == home_wnd->get_cut_img(i-1, j-1));
    else
        send_messege_wnd->players_img_verdict(img == source_img[i-1][j-1]);

    for (int k = 0; k < int(me_overhere_addres_list.size()); k++)
        NET_send_intercepted_messege_for_player(me_overhere_addres_list[k],
                                                enc_img, p_key, p_key_size,
                                                s_key, s_key_size, i, j, algoritm);
}

void MainWindow::show_intercept_window()
{
    home_wnd->close();
    intercept_wnd->show();
}

void MainWindow::back__homecoming()
{
    intercept_wnd->close();
    home_wnd->show();
}

void MainWindow::NET_send_players_inercept_login(QString login)
{
    if (intercept_wnd->get_login_of_intercept() != "")
        NET_no_overhere_for_root(login);

    intercept_wnd->set_login_of_intercept(login);

    QByteArray Data;
    Data.append("0iyes ");
    Data.append(login);
    socket->writeDatagram(Data, QHostAddress(root_address), 65201);
}

void MainWindow::NET_players_intercept_for_root(QString data, QHostAddress sender)
{
    QByteArray Data;
    Data.append("1i");

    QString action = cut_string_befor_simbol(data, ' ');
    Data.append(action);
    Data.append(' ');

    QHostAddress addres (user_list[data]);

    Data.append(sender.toString());
    socket->writeDatagram(Data, addres, 65201);
}

void MainWindow::NET_players_intercept_for_player(QString data)
{
    QString action = cut_string_befor_simbol(data, ' '); // Поиск да или нет
    if (action == "yes")
        me_overhere_addres_list.push_back(data);
    else
    {
        int i = me_overhere_addres_list.indexOf(data);
        me_overhere_addres_list.remove(i);
    }
}

void MainWindow::NET_send_intercepted_messege_for_player (QString addres, QImage img,                  
                                             QString p_key, int p_key_size,   
                                             QString s_key, int s_key_size, 
                                             int i, int j, QString algoritm)
{
    QByteArray Data;
    Data.append("1I");
    QString messege = "";

    messege = messege + p_key + ' ' + QString::number(p_key_size) + ' '
                      + s_key + ' ' + QString::number(s_key_size) + ' '
                      + QString::number(i) + ' ' + QString::number(j) + ' ' + algoritm + ' ';

    Data.append(messege);

    QByteArray ba;
    QBuffer buffer(&ba);
    img.save(&buffer,"PNG");

    Data = Data + ba;

    socket->writeDatagram(Data, QHostAddress(addres), 65201);
}

void MainWindow::NET_no_overhere_for_root (QString login)
{
    QByteArray Data;
    Data.append("0ino ");
    Data.append(login);
    socket->writeDatagram(Data, QHostAddress(root_address), 65201);
}

void MainWindow::NET_list_of_user_in_game(QString data)
{
    while (data!="")
    {
        QString user = cut_string_befor_simbol(data, ' ');
        NET_add_new_player(user);
    }
}

void MainWindow::NET_send_info_for_player(QString address, QString &messeges, QString &codes)
{
    QHostAddress temp_addres(address);

    QString datagramm = messeges + codes;

    QByteArray first_data;
    first_data.append("1S");
    first_data.append(datagramm);
    socket->writeDatagram(first_data, temp_addres, 65201);

    // В случае, если игра началась, а пользователь опоздал - сразу шлется старт
    if (root_wnd->get_flag_game_on())
    {
        QByteArray Data;
        Data.append("1g");
        socket->writeDatagram(Data, temp_addres, 65201);
    }

}

void MainWindow::NET_add_intercepted_messege(QString data, QByteArray buffer)
{
    // Костыльненько, но должно работать
    QString p_key           = cut_string_befor_simbol(data, ' ');
    QString p_key_size_str  = cut_string_befor_simbol(data, ' ');
    QString s_key           = cut_string_befor_simbol(data, ' ');
    QString s_key_size_st   = cut_string_befor_simbol(data, ' ');
    QString i_str           = cut_string_befor_simbol(data, ' ');
    QString j_str           = cut_string_befor_simbol(data, ' ');
    QString algoritm        = cut_string_befor_simbol(data, ' ');

    int size_data = p_key.size() + p_key_size_str.size() +
                    s_key.size() + s_key_size_st.size() +
                    i_str.size() + j_str.size() +
                    algoritm.size () + 7 + 2; // 7 пробелов 2 - служеюаня информация

    int p_key_size = p_key_size_str.toInt();
    int s_key_size = s_key_size_st.toInt();
    int i = i_str.toInt();
    int j = j_str.toInt();

    buffer.remove(0, size_data);
    QImage image;
    image.loadFromData(buffer);

    intercept_wnd->add_new_messege(image ,p_key,p_key_size,s_key,s_key_size,i, j, algoritm);
    home_wnd->set_visibale_new_messege(true);
}

void MainWindow::send_messege_wnd_on_intercept_value(QImage img,
                                         QString p_key, int p_key_size,
                                         QString s_key, int s_key_size,
                                         int i, int j,
                                         QString algoritm)
{
    send_messege_wnd->set_intercept_info(img, p_key, p_key_size, s_key,s_key_size, i, j, algoritm);
    intercept_wnd->close();
    send_messege_wnd->show();
}


















