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
    UpdateEvent.h \
    UserEvent.h \
    PlayerEvent.h \
    Bit.h

SOURCES += \
