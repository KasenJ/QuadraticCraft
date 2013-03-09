QT += \
    core \
    gui \
    widgets \
    network

TARGET = Client

TEMPLATE = app

CONFIG += c++11

SOURCES += \
    Client.cpp \
    Interface.cpp \
    Login.cpp

HEADERS += \
    Types.h \
    Interface.h \
    Login.h

LIBS += -L../Libs\
    -lTypes

RESOURCES += \
    Resource.qrc

TRANSLATIONS = \
    Chinese.ts
