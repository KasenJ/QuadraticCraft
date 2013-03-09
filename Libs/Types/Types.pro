QT += core network

TARGET = Types

TEMPLATE =lib

CONFIG += staticlib
CONFIG += c++11

DESTDIR = ../

HEADERS += \
    Event.h \
    DropEvent.h \
    GetEvent.h \
    MoveEvent.h \
    Socket.h \
    Square.h \
    UpdateEvent.h \
    UserEvent.h

SOURCES += \
    Socket.cpp \
    Square.cpp
