QT += core gui widget network

TARGET = Client

CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    Client.cpp \
    Utils.cpp \
    Arguments.cpp

HEADERS += \
    Utils.h \
    Arguments.h
