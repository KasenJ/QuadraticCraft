QT += core network

TARGET = Utils

TEMPLATE =lib

CONFIG += staticlib
CONFIG += c++11

DESTDIR = ../

HEADERS += \
    Socket.h \
    Types.h \
    Utils.h

SOURCES += \
    Socket.cpp \
    Utils.cpp
