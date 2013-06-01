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
    ItemEvent.h \
    ScriptEvent.h \
    DataEvent.h

SOURCES += \
