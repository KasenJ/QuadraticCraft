QT += \
    sql \
    core \
    gui \
    widgets

TARGET = Editor

TEMPLATE = app

CONFIG += c++11

SOURCES += \ 
    Editor.cpp \
    bitmap.cpp \
    Images.cpp \
    mainwindow.cpp \
    newdialog.cpp \
    listpass.cpp \
    combinelist.cpp

HEADERS += \
    Types.h \
    bitmap.h \
    Images.h \
    mainwindow.h \
    newdialog.h \
    listpass.h \
    combinelist.h

LIBS += -L../Libs\
    -lUtils

FORMS += \
    Images.ui \
    mainwindow.ui \
    newdialog.ui \
    listpass.ui \
    combinelist.ui
