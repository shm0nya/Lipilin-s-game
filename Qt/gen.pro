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
    home_windows.cpp \
    fun.cpp \
    send_messege.cpp

HEADERS  += mainwindow.h \
    home_windows.h \
    fun.h \
    send_messege.h

FORMS    += mainwindow.ui \
    home_windows.ui \
    send_messege.ui
	
CONFIG += c++11

QMAKE_CXXFLAGS_DEBUG += -gdwarf-3

RESOURCES += \
    resourses.qrc


