QT += core network

TARGET = Server

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    Server.cpp \
    Utils.cpp \
    Arguments.cpp

HEADERS += \
    Utils.h \
    Arguments.h
