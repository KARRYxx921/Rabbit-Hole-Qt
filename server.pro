#-------------------------------------------------
#
# Project created by QtCreator 2018-08-28T09:08:25
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
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
    server.cpp \
    tcpclientsocket.cpp \
    interface.cpp \
    main.cpp \
    interface_menu.cpp \
    aaaaaaa/tablewidget.cpp

HEADERS  += \
    server.h \
    tcpclientsocket.h \
    interface.h \
    interface_menu.h \
    aaaaaaa/tablewidget.h

FORMS    += \
    interface.ui \
    interface_menu.ui

RESOURCES += \
    imag2.qrc
