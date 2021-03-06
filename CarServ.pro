#-------------------------------------------------
#
# Project created by QtCreator 2018-05-06T16:25:45
#
#-------------------------------------------------

QT       += core gui sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = CarServ
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    newclient.cpp \
    newauto.cpp \
    newrepair.cpp \
    searchform.cpp \
    repairwigdetitem.cpp \
    addrepair.cpp \
    carsdatabase.cpp \
    showallcars.cpp \
    removechangeauto.cpp \
    removeclient.cpp \
    printformat.cpp

HEADERS += \
        mainwindow.h \
    newclient.h \
    newauto.h \
    newrepair.h \
    searchform.h \
    repairwigdetitem.h \
    addrepair.h \
    carsdatabase.h \
    showallcars.h \
    removechangeauto.h \
    removeclient.h \
    printformat.h

FORMS += \
        mainwindow.ui \
    newclient.ui \
    newrepair.ui \
    searchform.ui \
    addrepair.ui \
    repairwigdetitem.ui \
    newauto.ui \
    showallcars.ui \
    removechangeauto.ui \
    removeclient.ui \
    printformat.ui

RESOURCES += \
    Images/images.qrc

DISTFILES += \
    DataBase/All_Models.sqlite \
    DataBase/Automobiles.sqlite \
    DataBase/Clients.sqlite \
    DataBase/Marki.sqlite \
    Images/CarFormBackground.jpeg
