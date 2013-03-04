QT += core network

TARGET = Client

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    Client.cpp \
    Utils.cpp \
    Arguments.cpp

HEADERS += \
    Utils.h \
    Arguments.h
