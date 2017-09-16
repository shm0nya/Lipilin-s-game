#-------------------------------------------------
#
# Project created by QtCreator 2016-04-23T16:36:13
#
#-------------------------------------------------

QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    home_windows.cpp

HEADERS  += mainwindow.h \
    home_windows.h

FORMS    += mainwindow.ui \
    home_windows.ui
	
CONFIG += c++11

