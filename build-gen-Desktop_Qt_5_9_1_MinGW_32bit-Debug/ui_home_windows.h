/********************************************************************************
** Form generated from reading UI file 'home_windows.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HOME_WINDOWS_H
#define UI_HOME_WINDOWS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Home_windows
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QListWidget *listWidget;
    QWidget *widget;
    QVBoxLayout *left_layout;
    QVBoxLayout *summary_show_componation;
    QHBoxLayout *login_componation;
    QHBoxLayout *login_show;
    QLabel *login_show_lbl;
    QLabel *label_login;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *level_componation;
    QHBoxLayout *level_show;
    QLabel *level_show_lbl;
    QLabel *label_level;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *friend_show_componation;
    QLabel *friend_sho_who_it_lbl;
    QLabel *friend_show_who_it_value;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *opponent_show_componation;
    QLabel *opponent_show_is_lbl;
    QLabel *opponent_show_is_value;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *summary_edit_componation;
    QHBoxLayout *friend_edit_componation;
    QVBoxLayout *friend_edit_show;
    QLabel *friend_show_lbl;
    QHBoxLayout *friend_show_line_edit;
    QLineEdit *friend_edit;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *opponent_edit_componation;
    QVBoxLayout *opponent_edit_show;
    QLabel *opponent_edit_show_text;
    QHBoxLayout *opponent_show_line_edit;
    QLineEdit *opponent_edit;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_6;
    QWidget *tab_2;
    QWidget *widget1;
    QWidget *widget_2;
    QPushButton *Button_Sblok_use;
    QPushButton *Button_Pblok_use;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QPushButton *pushButton_8;
    QWidget *layoutWidget_2;
    QHBoxLayout *S_key_componate;
    QVBoxLayout *S_key_info_componate;
    QHBoxLayout *S_key_value_componate;
    QLabel *S_key_value_show_lbl;
    QSpacerItem *horizontalSpacer_11;
    QLineEdit *S_key_line_edit;
    QHBoxLayout *S_key_size_componate;
    QLabel *S_key_size_show_lbl;
    QSlider *S_key_size_slider;
    QSpinBox *S_key_size_spinBox;
    QPushButton *S_key_generate_button;
    QWidget *widget2;
    QHBoxLayout *P_key_componate;
    QVBoxLayout *P_key_info_componate;
    QHBoxLayout *P_key_value_componate;
    QLabel *P_key_value_show_lbl;
    QSpacerItem *horizontalSpacer_10;
    QLineEdit *P_key_line_edit;
    QHBoxLayout *P_key_size_componate;
    QLabel *P_key_size_show_lbl;
    QSlider *P_key_size_slider;
    QSpinBox *P_key_size_spinBox;
    QPushButton *P_key_generate_button;
    QWidget *widget3;
    QVBoxLayout *show_now_use;
    QLabel *show_now_use_header;
    QGridLayout *show_now_use_grid;
    QLabel *show_now_use_value;
    QLabel *show_now_use_P_value;
    QLabel *show_now_use_S_value;
    QLabel *show_now_use_P_size;
    QLabel *show_now_use_S_size;
    QLabel *show_now_use_size;
    QLabel *show_now_use_key;
    QLabel *show_now_use_P;
    QLabel *show_now_use_S;
    QWidget *tab_3;
    QLabel *label_12;
    QLabel *label_13;
    QTableView *tableView_2;
    QPushButton *pushButton_7;

    void setupUi(QWidget *Home_windows)
    {
        if (Home_windows->objectName().isEmpty())
            Home_windows->setObjectName(QStringLiteral("Home_windows"));
        Home_windows->resize(967, 563);
        tabWidget = new QTabWidget(Home_windows);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 961, 591));
        tabWidget->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"font: 75 10pt \"Verdana\";"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        listWidget = new QListWidget(tab);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(590, 10, 361, 511));
        widget = new QWidget(tab);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 10, 531, 511));
        left_layout = new QVBoxLayout(widget);
        left_layout->setObjectName(QStringLiteral("left_layout"));
        left_layout->setContentsMargins(0, 0, 0, 0);
        summary_show_componation = new QVBoxLayout();
        summary_show_componation->setObjectName(QStringLiteral("summary_show_componation"));
        login_componation = new QHBoxLayout();
        login_componation->setObjectName(QStringLiteral("login_componation"));
        login_show = new QHBoxLayout();
        login_show->setObjectName(QStringLiteral("login_show"));
        login_show_lbl = new QLabel(widget);
        login_show_lbl->setObjectName(QStringLiteral("login_show_lbl"));

        login_show->addWidget(login_show_lbl);

        label_login = new QLabel(widget);
        label_login->setObjectName(QStringLiteral("label_login"));

        login_show->addWidget(label_login);


        login_componation->addLayout(login_show);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        login_componation->addItem(horizontalSpacer_4);


        summary_show_componation->addLayout(login_componation);

        level_componation = new QHBoxLayout();
        level_componation->setObjectName(QStringLiteral("level_componation"));
        level_show = new QHBoxLayout();
        level_show->setObjectName(QStringLiteral("level_show"));
        level_show_lbl = new QLabel(widget);
        level_show_lbl->setObjectName(QStringLiteral("level_show_lbl"));

        level_show->addWidget(level_show_lbl);

        label_level = new QLabel(widget);
        label_level->setObjectName(QStringLiteral("label_level"));

        level_show->addWidget(label_level);


        level_componation->addLayout(level_show);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        level_componation->addItem(horizontalSpacer_3);


        summary_show_componation->addLayout(level_componation);

        friend_show_componation = new QHBoxLayout();
        friend_show_componation->setObjectName(QStringLiteral("friend_show_componation"));
        friend_sho_who_it_lbl = new QLabel(widget);
        friend_sho_who_it_lbl->setObjectName(QStringLiteral("friend_sho_who_it_lbl"));

        friend_show_componation->addWidget(friend_sho_who_it_lbl);

        friend_show_who_it_value = new QLabel(widget);
        friend_show_who_it_value->setObjectName(QStringLiteral("friend_show_who_it_value"));

        friend_show_componation->addWidget(friend_show_who_it_value);

        horizontalSpacer_7 = new QSpacerItem(188, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        friend_show_componation->addItem(horizontalSpacer_7);


        summary_show_componation->addLayout(friend_show_componation);

        opponent_show_componation = new QHBoxLayout();
        opponent_show_componation->setObjectName(QStringLiteral("opponent_show_componation"));
        opponent_show_is_lbl = new QLabel(widget);
        opponent_show_is_lbl->setObjectName(QStringLiteral("opponent_show_is_lbl"));

        opponent_show_componation->addWidget(opponent_show_is_lbl);

        opponent_show_is_value = new QLabel(widget);
        opponent_show_is_value->setObjectName(QStringLiteral("opponent_show_is_value"));

        opponent_show_componation->addWidget(opponent_show_is_value);

        horizontalSpacer_8 = new QSpacerItem(248, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        opponent_show_componation->addItem(horizontalSpacer_8);


        summary_show_componation->addLayout(opponent_show_componation);


        left_layout->addLayout(summary_show_componation);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        left_layout->addItem(verticalSpacer);

        summary_edit_componation = new QVBoxLayout();
        summary_edit_componation->setObjectName(QStringLiteral("summary_edit_componation"));
        friend_edit_componation = new QHBoxLayout();
        friend_edit_componation->setObjectName(QStringLiteral("friend_edit_componation"));
        friend_edit_show = new QVBoxLayout();
        friend_edit_show->setObjectName(QStringLiteral("friend_edit_show"));
        friend_show_lbl = new QLabel(widget);
        friend_show_lbl->setObjectName(QStringLiteral("friend_show_lbl"));

        friend_edit_show->addWidget(friend_show_lbl);

        friend_show_line_edit = new QHBoxLayout();
        friend_show_line_edit->setObjectName(QStringLiteral("friend_show_line_edit"));
        friend_edit = new QLineEdit(widget);
        friend_edit->setObjectName(QStringLiteral("friend_edit"));

        friend_show_line_edit->addWidget(friend_edit);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        friend_show_line_edit->addItem(horizontalSpacer);


        friend_edit_show->addLayout(friend_show_line_edit);


        friend_edit_componation->addLayout(friend_edit_show);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        friend_edit_componation->addItem(horizontalSpacer_5);


        summary_edit_componation->addLayout(friend_edit_componation);

        opponent_edit_componation = new QHBoxLayout();
        opponent_edit_componation->setObjectName(QStringLiteral("opponent_edit_componation"));
        opponent_edit_show = new QVBoxLayout();
        opponent_edit_show->setObjectName(QStringLiteral("opponent_edit_show"));
        opponent_edit_show_text = new QLabel(widget);
        opponent_edit_show_text->setObjectName(QStringLiteral("opponent_edit_show_text"));

        opponent_edit_show->addWidget(opponent_edit_show_text);

        opponent_show_line_edit = new QHBoxLayout();
        opponent_show_line_edit->setObjectName(QStringLiteral("opponent_show_line_edit"));
        opponent_edit = new QLineEdit(widget);
        opponent_edit->setObjectName(QStringLiteral("opponent_edit"));

        opponent_show_line_edit->addWidget(opponent_edit);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        opponent_show_line_edit->addItem(horizontalSpacer_2);


        opponent_edit_show->addLayout(opponent_show_line_edit);


        opponent_edit_componation->addLayout(opponent_edit_show);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        opponent_edit_componation->addItem(horizontalSpacer_6);


        summary_edit_componation->addLayout(opponent_edit_componation);


        left_layout->addLayout(summary_edit_componation);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        widget1 = new QWidget(tab_2);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(10, 130, 331, 291));
        widget_2 = new QWidget(tab_2);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(590, 140, 331, 291));
        Button_Sblok_use = new QPushButton(tab_2);
        Button_Sblok_use->setObjectName(QStringLiteral("Button_Sblok_use"));
        Button_Sblok_use->setGeometry(QRect(390, 180, 141, 23));
        Button_Pblok_use = new QPushButton(tab_2);
        Button_Pblok_use->setObjectName(QStringLiteral("Button_Pblok_use"));
        Button_Pblok_use->setGeometry(QRect(390, 220, 141, 23));
        pushButton_4 = new QPushButton(tab_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(40, 470, 75, 23));
        pushButton_5 = new QPushButton(tab_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(844, 480, 81, 23));
        pushButton_6 = new QPushButton(tab_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(844, 440, 81, 23));
        pushButton_8 = new QPushButton(tab_2);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));
        pushButton_8->setGeometry(QRect(670, 470, 81, 23));
        layoutWidget_2 = new QWidget(tab_2);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(340, 10, 331, 71));
        S_key_componate = new QHBoxLayout(layoutWidget_2);
        S_key_componate->setObjectName(QStringLiteral("S_key_componate"));
        S_key_componate->setContentsMargins(0, 0, 0, 0);
        S_key_info_componate = new QVBoxLayout();
        S_key_info_componate->setObjectName(QStringLiteral("S_key_info_componate"));
        S_key_value_componate = new QHBoxLayout();
        S_key_value_componate->setObjectName(QStringLiteral("S_key_value_componate"));
        S_key_value_show_lbl = new QLabel(layoutWidget_2);
        S_key_value_show_lbl->setObjectName(QStringLiteral("S_key_value_show_lbl"));

        S_key_value_componate->addWidget(S_key_value_show_lbl);

        horizontalSpacer_11 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        S_key_value_componate->addItem(horizontalSpacer_11);

        S_key_line_edit = new QLineEdit(layoutWidget_2);
        S_key_line_edit->setObjectName(QStringLiteral("S_key_line_edit"));

        S_key_value_componate->addWidget(S_key_line_edit);


        S_key_info_componate->addLayout(S_key_value_componate);

        S_key_size_componate = new QHBoxLayout();
        S_key_size_componate->setObjectName(QStringLiteral("S_key_size_componate"));
        S_key_size_show_lbl = new QLabel(layoutWidget_2);
        S_key_size_show_lbl->setObjectName(QStringLiteral("S_key_size_show_lbl"));

        S_key_size_componate->addWidget(S_key_size_show_lbl);

        S_key_size_slider = new QSlider(layoutWidget_2);
        S_key_size_slider->setObjectName(QStringLiteral("S_key_size_slider"));
        S_key_size_slider->setOrientation(Qt::Horizontal);

        S_key_size_componate->addWidget(S_key_size_slider);

        S_key_size_spinBox = new QSpinBox(layoutWidget_2);
        S_key_size_spinBox->setObjectName(QStringLiteral("S_key_size_spinBox"));
        S_key_size_spinBox->setMaximum(100);
        S_key_size_spinBox->setSingleStep(2);

        S_key_size_componate->addWidget(S_key_size_spinBox);


        S_key_info_componate->addLayout(S_key_size_componate);


        S_key_componate->addLayout(S_key_info_componate);

        S_key_generate_button = new QPushButton(layoutWidget_2);
        S_key_generate_button->setObjectName(QStringLiteral("S_key_generate_button"));

        S_key_componate->addWidget(S_key_generate_button);

        widget2 = new QWidget(tab_2);
        widget2->setObjectName(QStringLiteral("widget2"));
        widget2->setGeometry(QRect(10, 10, 321, 68));
        P_key_componate = new QHBoxLayout(widget2);
        P_key_componate->setObjectName(QStringLiteral("P_key_componate"));
        P_key_componate->setContentsMargins(0, 0, 0, 0);
        P_key_info_componate = new QVBoxLayout();
        P_key_info_componate->setObjectName(QStringLiteral("P_key_info_componate"));
        P_key_value_componate = new QHBoxLayout();
        P_key_value_componate->setObjectName(QStringLiteral("P_key_value_componate"));
        P_key_value_show_lbl = new QLabel(widget2);
        P_key_value_show_lbl->setObjectName(QStringLiteral("P_key_value_show_lbl"));

        P_key_value_componate->addWidget(P_key_value_show_lbl);

        horizontalSpacer_10 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        P_key_value_componate->addItem(horizontalSpacer_10);

        P_key_line_edit = new QLineEdit(widget2);
        P_key_line_edit->setObjectName(QStringLiteral("P_key_line_edit"));

        P_key_value_componate->addWidget(P_key_line_edit);


        P_key_info_componate->addLayout(P_key_value_componate);

        P_key_size_componate = new QHBoxLayout();
        P_key_size_componate->setObjectName(QStringLiteral("P_key_size_componate"));
        P_key_size_show_lbl = new QLabel(widget2);
        P_key_size_show_lbl->setObjectName(QStringLiteral("P_key_size_show_lbl"));

        P_key_size_componate->addWidget(P_key_size_show_lbl);

        P_key_size_slider = new QSlider(widget2);
        P_key_size_slider->setObjectName(QStringLiteral("P_key_size_slider"));
        P_key_size_slider->setOrientation(Qt::Horizontal);

        P_key_size_componate->addWidget(P_key_size_slider);

        P_key_size_spinBox = new QSpinBox(widget2);
        P_key_size_spinBox->setObjectName(QStringLiteral("P_key_size_spinBox"));
        P_key_size_spinBox->setMaximum(100);
        P_key_size_spinBox->setSingleStep(2);

        P_key_size_componate->addWidget(P_key_size_spinBox);


        P_key_info_componate->addLayout(P_key_size_componate);


        P_key_componate->addLayout(P_key_info_componate);

        P_key_generate_button = new QPushButton(widget2);
        P_key_generate_button->setObjectName(QStringLiteral("P_key_generate_button"));

        P_key_componate->addWidget(P_key_generate_button);

        widget3 = new QWidget(tab_2);
        widget3->setObjectName(QStringLiteral("widget3"));
        widget3->setGeometry(QRect(700, 10, 245, 86));
        show_now_use = new QVBoxLayout(widget3);
        show_now_use->setObjectName(QStringLiteral("show_now_use"));
        show_now_use->setContentsMargins(0, 0, 0, 0);
        show_now_use_header = new QLabel(widget3);
        show_now_use_header->setObjectName(QStringLiteral("show_now_use_header"));

        show_now_use->addWidget(show_now_use_header);

        show_now_use_grid = new QGridLayout();
        show_now_use_grid->setObjectName(QStringLiteral("show_now_use_grid"));
        show_now_use_value = new QLabel(widget3);
        show_now_use_value->setObjectName(QStringLiteral("show_now_use_value"));

        show_now_use_grid->addWidget(show_now_use_value, 0, 1, 1, 1);

        show_now_use_P_value = new QLabel(widget3);
        show_now_use_P_value->setObjectName(QStringLiteral("show_now_use_P_value"));

        show_now_use_grid->addWidget(show_now_use_P_value, 1, 1, 1, 1);

        show_now_use_S_value = new QLabel(widget3);
        show_now_use_S_value->setObjectName(QStringLiteral("show_now_use_S_value"));

        show_now_use_grid->addWidget(show_now_use_S_value, 2, 1, 1, 1);

        show_now_use_P_size = new QLabel(widget3);
        show_now_use_P_size->setObjectName(QStringLiteral("show_now_use_P_size"));

        show_now_use_grid->addWidget(show_now_use_P_size, 1, 2, 1, 1);

        show_now_use_S_size = new QLabel(widget3);
        show_now_use_S_size->setObjectName(QStringLiteral("show_now_use_S_size"));

        show_now_use_grid->addWidget(show_now_use_S_size, 2, 2, 1, 1);

        show_now_use_size = new QLabel(widget3);
        show_now_use_size->setObjectName(QStringLiteral("show_now_use_size"));

        show_now_use_grid->addWidget(show_now_use_size, 0, 2, 1, 1);

        show_now_use_key = new QLabel(widget3);
        show_now_use_key->setObjectName(QStringLiteral("show_now_use_key"));

        show_now_use_grid->addWidget(show_now_use_key, 0, 0, 1, 1);

        show_now_use_P = new QLabel(widget3);
        show_now_use_P->setObjectName(QStringLiteral("show_now_use_P"));

        show_now_use_grid->addWidget(show_now_use_P, 1, 0, 1, 1);

        show_now_use_S = new QLabel(widget3);
        show_now_use_S->setObjectName(QStringLiteral("show_now_use_S"));

        show_now_use_grid->addWidget(show_now_use_S, 2, 0, 1, 1);


        show_now_use->addLayout(show_now_use_grid);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        label_12 = new QLabel(tab_3);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(0, 10, 101, 16));
        label_13 = new QLabel(tab_3);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(0, 30, 81, 16));
        tableView_2 = new QTableView(tab_3);
        tableView_2->setObjectName(QStringLiteral("tableView_2"));
        tableView_2->setGeometry(QRect(0, 50, 641, 491));
        pushButton_7 = new QPushButton(tab_3);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));
        pushButton_7->setGeometry(QRect(780, 490, 75, 23));
        tabWidget->addTab(tab_3, QString());

        retranslateUi(Home_windows);
        QObject::connect(P_key_size_spinBox, SIGNAL(valueChanged(int)), P_key_size_slider, SLOT(setValue(int)));
        QObject::connect(S_key_size_spinBox, SIGNAL(valueChanged(int)), S_key_size_slider, SLOT(setValue(int)));

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Home_windows);
    } // setupUi

    void retranslateUi(QWidget *Home_windows)
    {
        Home_windows->setWindowTitle(QApplication::translate("Home_windows", "Form", Q_NULLPTR));
        login_show_lbl->setText(QApplication::translate("Home_windows", "\320\222\320\260\321\210 \320\273\320\276\320\263\320\270\320\275:", Q_NULLPTR));
        label_login->setText(QApplication::translate("Home_windows", "login", Q_NULLPTR));
        level_show_lbl->setText(QApplication::translate("Home_windows", "\320\243\321\200\320\276\320\262\320\265\320\275\321\214:", Q_NULLPTR));
        label_level->setText(QApplication::translate("Home_windows", "lvl", Q_NULLPTR));
        friend_sho_who_it_lbl->setText(QApplication::translate("Home_windows", "\320\222\321\213 \320\276\320\261\321\211\320\260e\321\202\320\265\321\201\321\214 \321\201:", Q_NULLPTR));
        friend_show_who_it_value->setText(QString());
        opponent_show_is_lbl->setText(QApplication::translate("Home_windows", "\320\222\321\213 \320\277\320\265\321\200\320\265\321\205\320\262\320\260\321\202\321\213\320\262\320\260\320\265\321\202\320\265 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\320\265 \321\203:", Q_NULLPTR));
        opponent_show_is_value->setText(QString());
        friend_show_lbl->setText(QApplication::translate("Home_windows", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\273\320\276\320\263\320\270\320\275 \321\202\320\276\320\263\320\276 \321\207\320\265\320\273\320\276\320\262\320\265\320\272\320\260, \321\201 \320\272\320\265\320\274 \321\205\320\276\321\202\320\270\321\202\320\265 \320\262\320\265\321\201\321\202\320\270 \320\277\320\265\321\200\320\265\320\277\320\270\321\201\320\272\321\203:", Q_NULLPTR));
        opponent_edit_show_text->setText(QApplication::translate("Home_windows", "\320\222\320\262\320\265\320\264\320\270\321\202\320\265 \320\273\320\276\320\263\320\270\320\275 \321\202\320\276\320\263\320\276 \321\207\320\265\320\273\320\276\320\262\320\265\320\272\320\260, \321\207\321\214\320\270 \321\201\320\276\320\276\320\261\321\211\320\265\320\275\320\270\321\217 \321\205\320\276\321\202\320\270\321\202\320\265 \320\277\320\265\321\200\320\265\321\205\320\262\320\260\321\202\321\213\320\262\320\260\321\202\321\214:", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Home_windows", "Tab 1", Q_NULLPTR));
        Button_Sblok_use->setText(QApplication::translate("Home_windows", "\320\227\320\260\320\274\320\265\320\275\320\260 (S)", Q_NULLPTR));
        Button_Pblok_use->setText(QApplication::translate("Home_windows", "\320\237\320\265\321\200\320\265\321\201\321\202\320\260\320\275\320\276\320\262\320\272\320\260 (P)", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("Home_windows", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("Home_windows", "\320\236\321\202\320\277\321\200\320\260\320\262\320\270\321\202\321\214", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("Home_windows", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", Q_NULLPTR));
        pushButton_8->setText(QApplication::translate("Home_windows", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", Q_NULLPTR));
        S_key_value_show_lbl->setText(QApplication::translate("Home_windows", "\320\232\320\273\321\216\321\207 S:", Q_NULLPTR));
        S_key_line_edit->setText(QString());
        S_key_size_show_lbl->setText(QApplication::translate("Home_windows", "\320\224\320\273\320\270\320\275\320\260:", Q_NULLPTR));
        S_key_generate_button->setText(QApplication::translate("Home_windows", "\320\227\320\260\320\264\320\260\321\202\321\214", Q_NULLPTR));
        P_key_value_show_lbl->setText(QApplication::translate("Home_windows", "\320\232\320\273\321\216\321\207 P:", Q_NULLPTR));
        P_key_size_show_lbl->setText(QApplication::translate("Home_windows", "\320\224\320\273\320\270\320\275\320\260:", Q_NULLPTR));
        P_key_generate_button->setText(QApplication::translate("Home_windows", "\320\227\320\260\320\264\320\260\321\202\321\214", Q_NULLPTR));
        show_now_use_header->setText(QApplication::translate("Home_windows", "\320\241\320\265\320\271\321\207\320\260\321\201 \320\270\321\201\320\277\320\276\320\273\321\214\320\267\321\203\321\216\321\202\321\201\321\217 \320\272\320\273\321\216\321\207\320\270:", Q_NULLPTR));
        show_now_use_value->setText(QApplication::translate("Home_windows", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270e                ", Q_NULLPTR));
        show_now_use_P_value->setText(QString());
        show_now_use_S_value->setText(QString());
        show_now_use_P_size->setText(QString());
        show_now_use_S_size->setText(QString());
        show_now_use_size->setText(QApplication::translate("Home_windows", "\320\224\320\273\320\270\320\275\320\260", Q_NULLPTR));
        show_now_use_key->setText(QApplication::translate("Home_windows", "\320\232\320\273\321\216\321\207", Q_NULLPTR));
        show_now_use_P->setText(QApplication::translate("Home_windows", "P", Q_NULLPTR));
        show_now_use_S->setText(QApplication::translate("Home_windows", "S", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Home_windows", "Tab 2", Q_NULLPTR));
        label_12->setText(QApplication::translate("Home_windows", "\320\222\320\260\321\210 \320\273\320\276\320\263\320\270\320\275:", Q_NULLPTR));
        label_13->setText(QApplication::translate("Home_windows", "\320\243\321\200\320\276\320\262\320\265\320\275\321\214:", Q_NULLPTR));
        pushButton_7->setText(QApplication::translate("Home_windows", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("Home_windows", "\320\241\321\202\321\200\320\260\320\275\320\270\321\206\320\260", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Home_windows: public Ui_Home_windows {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HOME_WINDOWS_H
