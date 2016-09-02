#-------------------------------------------------
#
# Project created by QtCreator 2016-08-29T16:10:17
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Cpluspluswork
TEMPLATE = app


SOURCES += main.cpp\
        trainmanager.cpp \
    mainwindow.cpp\
	Handle.cpp \
    User.cpp \
    Manager.cpp

HEADERS  += trainmanager.h \
    login.h \
    Handle.h \
    User.h \
    Manager.h

FORMS    += trainmanager.ui \
    mainwindow.ui
