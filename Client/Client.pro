QT += \
    core \
    gui \
    widgets \
    network \
    sql

TARGET = Client

TEMPLATE = app

CONFIG += c++11

SOURCES += \
    Client.cpp \
    Interface.cpp \
    Login.cpp \
    Buffer.cpp \
    Info.cpp \
    Pack.cpp \
    Produce.cpp \
    Share.cpp

HEADERS += \
    Types.h \
    Interface.h \
    Login.h \
    Buffer.h \
    Info.h \
    Pack.h \
    Produce.h \
    Share.h

LIBS += -L../Libs\
    -lTypes \
    -lUtils

TRANSLATIONS = \
    zh_CN.ts
