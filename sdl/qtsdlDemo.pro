#-------------------------------------------------
#
# Project created by QtCreator 2017-06-06T10:16:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qtsdlDemo
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


SOURCES += main.cpp\
        mainwindow.cpp \
    sdlwidget.cpp

HEADERS  += mainwindow.h \
    sdlwidget.h

FORMS    += mainwindow.ui

unix{
LIBS += -L/usr/lib/x86_64-linux-gnu -lSDL2 -lSDL2_image
}

    INCLUDEPATH += . C:/SDL2/SDL2-2.0.5/include C:/SDL2/SDL2_image-2.0.1/include
    LIBS += -LC:/SDL2/SDL2-2.0.5/lib/x86 -lSDL2
    LIBS += -LC:/SDL2/SDL2-2.0.5/lib/x86 -lSDL2test

    LIBS += -LC:/SDL2/SDL2_image-2.0.1/lib/x86 -lSDL2_image
