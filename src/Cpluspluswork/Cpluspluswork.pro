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
    mainwindow.cpp\
	Handle.cpp \
    User.cpp \
    Manager.cpp \
    Forms/profileform.cpp \
    Forms/form.cpp \
    Forms/trainform.cpp \
    Forms/trainstationform.cpp \
    BasicData/basicdata.cpp\
	book.cpp \
    search.cpp \
    account.cpp \
    profile.cpp \
    seat.cpp \
    userview.cpp

HEADERS  += Handle.h \
    User.h \
    Manager.h \
    mainwindow.h \
    BasicDataField.h \
    Forms/profileform.h \
    Forms/form.h \
    Forms/trainform.h \
    Forms/trainstationform.h \
    BasicData/basicdata.h\
	book.h \
    search.h \
    account.h \
    profile.h \
    seat.h \
    userview.h

FORMS    +=mainwindow.ui \
    Forms/form.ui\
    ManagerView.ui \
    search.ui \
    account.ui \
    profile.ui \
    seat.ui \
    userview.ui

RESOURCES +=work.qrc
