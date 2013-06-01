QT += \
    sql \
    core \
    gui \
    widgets

TARGET = Editor

CONFIG += console

TEMPLATE = app

CONFIG += c++11

SOURCES += \ 
    Editor.cpp

HEADERS += \
    Types.h

LIBS += -L../Libs\
    -lUtils
