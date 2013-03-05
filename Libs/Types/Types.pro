QT += core

TARGET = Types

TEMPLATE =lib

CONFIG += staticlib

DESTDIR = ../

HEADERS += \
    MoveEvent.h \
    Event.h \
    GetEvent.h \
    UpdateEvent.h

SOURCES += \
    MoveEvent.cpp \
    GetEvent.cpp \
    UpdateEvent.cpp
