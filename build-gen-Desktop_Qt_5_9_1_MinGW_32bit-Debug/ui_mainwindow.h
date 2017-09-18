/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *widget;
    QVBoxLayout *summary_componate;
    QHBoxLayout *componate_text_first_lbl;
    QSpacerItem *horizontalSpacer;
    QLabel *label_text_to_get_login1;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *componate_second_lbl;
    QSpacerItem *horizontalSpacer_10;
    QLabel *label_text_to_get_login2;
    QSpacerItem *horizontalSpacer_9;
    QHBoxLayout *componate_third_lbl;
    QSpacerItem *horizontalSpacer_7;
    QLabel *label_text_toget_login_3;
    QSpacerItem *horizontalSpacer_8;
    QHBoxLayout *Componate_Line_edit;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *login_edit;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *componate_login_button;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *Login_button;
    QSpacerItem *horizontalSpacer_6;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(765, 434);
        MainWindow->setContextMenuPolicy(Qt::CustomContextMenu);
        MainWindow->setAutoFillBackground(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(94, 145, 573, 152));
        summary_componate = new QVBoxLayout(widget);
        summary_componate->setSpacing(6);
        summary_componate->setContentsMargins(11, 11, 11, 11);
        summary_componate->setObjectName(QStringLiteral("summary_componate"));
        summary_componate->setContentsMargins(0, 0, 0, 0);
        componate_text_first_lbl = new QHBoxLayout();
        componate_text_first_lbl->setSpacing(6);
        componate_text_first_lbl->setObjectName(QStringLiteral("componate_text_first_lbl"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        componate_text_first_lbl->addItem(horizontalSpacer);

        label_text_to_get_login1 = new QLabel(widget);
        label_text_to_get_login1->setObjectName(QStringLiteral("label_text_to_get_login1"));
        QFont font;
        font.setPointSize(14);
        label_text_to_get_login1->setFont(font);

        componate_text_first_lbl->addWidget(label_text_to_get_login1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        componate_text_first_lbl->addItem(horizontalSpacer_2);


        summary_componate->addLayout(componate_text_first_lbl);

        componate_second_lbl = new QHBoxLayout();
        componate_second_lbl->setSpacing(6);
        componate_second_lbl->setObjectName(QStringLiteral("componate_second_lbl"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        componate_second_lbl->addItem(horizontalSpacer_10);

        label_text_to_get_login2 = new QLabel(widget);
        label_text_to_get_login2->setObjectName(QStringLiteral("label_text_to_get_login2"));
        label_text_to_get_login2->setFont(font);

        componate_second_lbl->addWidget(label_text_to_get_login2);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        componate_second_lbl->addItem(horizontalSpacer_9);


        summary_componate->addLayout(componate_second_lbl);

        componate_third_lbl = new QHBoxLayout();
        componate_third_lbl->setSpacing(6);
        componate_third_lbl->setObjectName(QStringLiteral("componate_third_lbl"));
        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        componate_third_lbl->addItem(horizontalSpacer_7);

        label_text_toget_login_3 = new QLabel(widget);
        label_text_toget_login_3->setObjectName(QStringLiteral("label_text_toget_login_3"));
        label_text_toget_login_3->setFont(font);

        componate_third_lbl->addWidget(label_text_toget_login_3);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        componate_third_lbl->addItem(horizontalSpacer_8);


        summary_componate->addLayout(componate_third_lbl);

        Componate_Line_edit = new QHBoxLayout();
        Componate_Line_edit->setSpacing(6);
        Componate_Line_edit->setObjectName(QStringLiteral("Componate_Line_edit"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Componate_Line_edit->addItem(horizontalSpacer_3);

        login_edit = new QLineEdit(widget);
        login_edit->setObjectName(QStringLiteral("login_edit"));
        QFont font1;
        font1.setPointSize(11);
        login_edit->setFont(font1);

        Componate_Line_edit->addWidget(login_edit);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        Componate_Line_edit->addItem(horizontalSpacer_4);


        summary_componate->addLayout(Componate_Line_edit);

        componate_login_button = new QHBoxLayout();
        componate_login_button->setSpacing(6);
        componate_login_button->setObjectName(QStringLiteral("componate_login_button"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        componate_login_button->addItem(horizontalSpacer_5);

        Login_button = new QPushButton(widget);
        Login_button->setObjectName(QStringLiteral("Login_button"));

        componate_login_button->addWidget(Login_button);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        componate_login_button->addItem(horizontalSpacer_6);


        summary_componate->addLayout(componate_login_button);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_text_to_get_login1->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\270\320\264\321\203\320\274\320\260\320\271\321\202\320\265 \321\201\320\265\320\261\320\265 \320\273\320\276\320\263\320\270\320\275 \320\270 \320\262\320\262\320\265\320\264\320\270\321\202\320\265 \320\265\320\263\320\276. ", Q_NULLPTR));
        label_text_to_get_login2->setText(QApplication::translate("MainWindow", "\320\233\320\276\320\263\320\270\320\275 \320\274\320\276\320\266\320\265\321\202 \321\201\320\276\321\201\321\202\320\276\321\217\321\202\321\214 \321\202\320\276\320\273\321\214\320\272\320\276 \320\273\320\260\321\202\320\270\320\275\321\201\320\272\320\270\321\205 \320\261\321\203\320\272\320\262 \320\270 \321\206\320\270\321\204\321\200.", Q_NULLPTR));
        label_text_toget_login_3->setText(QApplication::translate("MainWindow", "\320\234\320\260\320\272\321\201\320\270\320\274\321\203\320\274 20 \320\267\320\275\320\260\320\272\320\276\320\262", Q_NULLPTR));
        login_edit->setText(QString());
        Login_button->setText(QApplication::translate("MainWindow", "\320\236\320\232", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
