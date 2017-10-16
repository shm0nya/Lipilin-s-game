#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    /*
     * Проверка на правильность ввода логина:
     *      Устанавливает кнопку "Ок" в состояние [enabled]
     *      Регулярное выражение, которое разрешает все комбинации из цифр, букв латинского алфавит
     *      становится Валидатором line edit.
     *      В случае, если пользователь попытается ввести значение, не соответствующее регулярному,
     *      валидатор не даст это сделать
     *
     * connect:
     *      ловят input от пользователя, после чего разрешают зарегистрироватсья
    */

    ui->Login_button->setEnabled(false);
    QRegExp is_login_variable("[a-zA-Z0-9]{1,20}");
    ui->login_edit->setValidator(new QRegExpValidator(is_login_variable, this)); // Необходимо указывать родителся, чтобы автоматически удаляться при закрытии данного окна

    connect(ui->login_edit,SIGNAL(textChanged(QString)),this,SLOT(ok_enabled()));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::ok_enabled()
{
    /*
     * У класса line edit есть метод, который в зависимости от валидатора
     * возвращает True или False
    */
    ui->Login_button->setEnabled(ui->login_edit->hasAcceptableInput());
}

void MainWindow::on_Login_button_clicked()
{
    /*
     * В начале создается окно mainwindow
     * Пользователю предлагается ввести login. (QLineEdit = input_login)
     * После чего открывается окно Home_windows, в него передается значение login
     * Окно main закрывается
    */
    QString name_login = ui->login_edit->text();
    sWindow = new Home_windows(name_login);
    sWindow->show();
    this->close();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Return)
    {
        /*
         * В начале создается окно mainwindow
         * Пользователю предлагается ввести login. (QLineEdit = input_login)
         * После чего открывается окно Home_windows, в него передается значение login
         * Окно main закрывается
        */
        QString name_login = ui->login_edit->text();
        sWindow = new Home_windows(name_login);
        sWindow->show();
        this->close();
    }
}
