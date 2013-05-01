QT += core network

TARGET = Types

TEMPLATE =lib

CONFIG += staticlib
CONFIG += c++11

DESTDIR = ../

HEADERS += \
    Event.h \
    UpdateEvent.h \
    UserEvent.h \
    PlayerEvent.h \
    Bit.h \
    ItemEvent.h

SOURCES += \
