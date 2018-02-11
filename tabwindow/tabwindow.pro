#-------------------------------------------------
#
# Project created by QtCreator 2013-10-29T16:21:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tabwindow
TEMPLATE = app


SOURCES += main.cpp \
    layout/tab.cpp \
    layout/tabcontent.cpp \
    layout/layoutmanager.cpp \
    layout/tabtoolbuttonbox.cpp \
    layout/template.cpp \
    layout/tabbuttonbarbutton.cpp \
    layout/tabbuttonbarlist.cpp \
    layout/layoutwindow.cpp \
    layout/drag.cpp \
    layout/deal.cpp

HEADERS  += \
    layout/tab.h \
    layout/tabcontent.h \
    layout/tabtoolbuttonbox.h \
    layout/layoutmanager.h \
    layout/template.h \
    layout/tabbuttonbarbutton.h \
    layout/tabbuttonbarlist.h \
    layout/layoutwindow.h \
    layout/drag.h \
    layout/deal.h

FORMS    += \
    layout/template.ui \
    layout/tab.ui \
    layout/deal.ui

RESOURCES += \
    resouce/resource.qrc
