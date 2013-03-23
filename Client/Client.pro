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
    Login.cpp \
    Buffer.cpp

HEADERS += \
    Types.h \
    Interface.h \
    Login.h \
    Buffer.h

LIBS += -L../Libs\
    -lTypes \
    -lUtils

RESOURCES += \
    Resource.qrc

TRANSLATIONS = \
    zh_CN.ts
