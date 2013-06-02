QT += \
    core \
    gui \
    widgets \
    sql

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
    combinelist.cpp \
    Render.cpp

HEADERS += \
    Types.h \
    bitmap.h \
    Images.h \
    mainwindow.h \
    newdialog.h \
    listpass.h \
    combinelist.h \
    Render.h

LIBS += -L../Libs\
    -lUtils

FORMS += \
    Images.ui \
    mainwindow.ui \
    newdialog.ui \
    listpass.ui \
    combinelist.ui
