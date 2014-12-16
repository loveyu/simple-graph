#-------------------------------------------------
#
# Project created by QtCreator 2014-12-09T08:24:16
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Graph
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    painterwidget.cpp \
    ccohen_sutherland.cpp \
    graphmove.cpp \
    graphrevolve.cpp \
    graphscaled.cpp \
    graphtool.cpp \
    imageaction.cpp \
    fillshape.cpp \
    myopengl.cpp \
    tddraw.cpp \
    colorlabel.cpp

HEADERS  += mainwindow.h \
    painterwidget.h \
    ActionType.h \
    GraphVector.h \
    ccohen_sutherland.h \
    graphmove.h \
    graphrevolve.h \
    graphscaled.h \
    graphtool.h \
    imageaction.h \
    fillshape.h \
    myopengl.h \
    tddraw.h \
    colorlabel.h

FORMS    += mainwindow.ui

CONFIG += c++11

RESOURCES += \
    icon.qrc
RC_FILE += icon.rc

OTHER_FILES += \
    icon.rc

TRANSLATIONS = zh_CN.ts
