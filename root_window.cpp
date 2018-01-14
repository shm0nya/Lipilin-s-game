#include "root_window.h"
#include "ui_root_window.h"

root_window::root_window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::root_window)
{
    ui->setupUi(this);

    QRegExp is_int("[0-9]{0,3}");
    ui->edit_n->setValidator(new QRegExpValidator(is_int, this));
    ui->edit_m->setValidator(new QRegExpValidator(is_int, this));

    p_colors = pblok_key(colors_size, 100500);

    QRegExp reg("[А-Я]{0,70}");
    ui->edit_text->setValidator(new QRegExpValidator(reg, this));

    // Инициализация соответствия букв и рун (слева буквы, справа руны)

    letters["А"]=1;
    letters["Б"]=2;
    letters["В"]=18;
    letters["Г"]=9;
    letters["Д"]=5;
    letters["Е"]=6;
    letters["Ж"]=7;
    letters["З"]=3;
    letters["И"]=8;
    letters["Й"]=8;
    letters["К"]=9;
    letters["Л"]=10;
    letters["М"]=11;
    letters["Н"]=12;
    letters["О"]=13;
    letters["П"]=14;
    letters["Р"]=15;
    letters["С"]=3;
    letters["Т"]=16;
    letters["У"]=17;
    letters["Ф"]=18;
    letters["Х"]=7;
    letters["Ц"]=4;
    letters["Ч"]=4;
    letters["Ш"]=14;
    letters["Щ"]=16;
    letters["Ъ"]=15;
    letters["Ы"]=5;
    letters["Ь"]=2;
    letters["Э"]=6;
    letters["Ю"]=17;
    letters["Я"]=1;

    //create_images();
}

root_window::~root_window()
{
    delete ui;
}

void root_window::on_button_apply_clicked()
{
    if ((ui->edit_m->text() == "") || (ui->edit_n->text() == ""))
    {
        QMessageBox::information(this, "Error", "Вы не указали один из параметров n, m");
        return;
    }

    n = ui->edit_n->text().toInt();
    m = ui->edit_m->text().toInt();
    flag_default = false;

    if (ui->lbl_count_of_char_value->text().toInt()!= n*m)
    {
        QMessageBox::information(this, "error", "Количество букв в тексте и рун не совпадает");
        return;
    }

    // Удаление элементов, при задании новых n, m
    QLayoutItem *ch;
    while ((ch = ui->componate_alphabet_buttons->takeAt(0))!= 0)
    {
            ui->componate_alphabet_buttons->removeItem(ch);
            ch->widget()->deleteLater();
            delete ch;
    }

    create_images();
}

void root_window::create_images()
{
    pb_runes.clear();

    for (int i = 0; i < n; i++)
    {
        std::vector<QPB_modify*> temp_vec;
        for (int j = 0; j < m; j++)
        {
            // задается руна, соответствующая букве, с определенным цветом
            int let = letters[messege[j + i*n]];
            int col = p_colors[(j + i*n)%colors_size];
            emit this->get_rune(let, col);

            QPB_modify *pb = new QPB_modify;
            pb->i = i;
            pb->j = j;
            if (flag_default == true)
                pb->str = messege[j + i*n];

            pb->reverse_img = temp_rune;
            pb->rune_code = QString::number((j + i*n)%runes_size) + '_' + QString::number((j + i*n)%colors_size);

            QSize button_size(50,50);
            pb->setMaximumSize(button_size);
            pb->setMinimumSize(button_size);

            pb->setIcon(QIcon(QPixmap::fromImage(temp_rune)));
            QSize icon_size(pb->size());
            pb->setIconSize(icon_size);

            connect(pb, &QPushButton::clicked, [this, pb](){
                // Предыдущая реализация
                //emit this->show_make_img_with_my_img(pb->reverse_img, pb->i, pb->j, pb->str);
                QMessageBox::information(this, "", pb->str);
            });
            ui->componate_alphabet_buttons->addWidget(pb, i, j);
            temp_vec.push_back(pb);
        }
        pb_runes.push_back(temp_vec);
    }
}

void root_window::on_button_default_clicked()
{
    n = 5;
    m = 6;
    flag_default = true;
    messege = default_text;
    QString str = "";
    int messege_size = messege.size();
    for (int i = 0; i < messege_size; i++)
        str = str + messege[i] + ' ';

    create_images();

    ui->edit_m->setText("6");
    ui->edit_n->setText("5");
}

void root_window::on_button_start_clicked()
{
    flag_gamego_on = true;
    emit this->start();
    QMessageBox::information(this,"Старт", "Игра началась.");
}

void root_window::set_rune_at_GL(QPB_modify *pb, int i, int j)
{
    ui->componate_alphabet_buttons->addWidget(pb, i, j);
    pb_runes[i][j] = pb;
}

QString root_window::get_rune_code_at_position(int i, int j)
{
   QString code;
   code = pb_runes[i][j]->rune_code;
   return code;
}

QString root_window::get_messege_at_position(int i, int j)
{
    int messege_size = messege.size();
    if (messege_size > i*m +j)
        return messege[i*m + j];
    else
        return "";
}

void root_window::add_new_player(QString login)
{
    ui->user_list->addItem(login);
}

void root_window::on_edit_text_editingFinished()
{
    messege.clear();

    QString text = ui->edit_text->text();
    QString new_text = "";
    int count = 0;
    int i = 0;

    while (i!=text.size())
    {
        if (text[i]!=' ')
        {
            count++;
            QString str = "";
            str = str + text[i];
            messege.push_back(str);
            new_text = new_text + str + ' ';
        }
        i++;
    }

    ui->lbl_now_using_text->setText(new_text);
    ui->lbl_count_of_char_value->setText(QString::number(count));
}

void root_window::on_button_level_up_clicked()
{
    //повышение уровня
    //после рассылки игрокам уровня вывести его значение в level (lable)
}
