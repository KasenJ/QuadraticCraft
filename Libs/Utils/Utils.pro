QT += core network

TARGET = Utils

TEMPLATE =lib

CONFIG += staticlib
CONFIG += c++11

DESTDIR = ../

HEADERS += \
    Socket.h \
    Square.h \
    Types.h

SOURCES += \
    Socket.cpp \
    Square.cpp
