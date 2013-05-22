QT += \
    sql \
    core \
    network

TARGET = Server

CONFIG += console

TEMPLATE = app

CONFIG += c++11

SOURCES += \
    Server.cpp \
    Handler.cpp \
    ./Handlers/UpdateEventHandle.cpp \
    ./Handlers/UserEventHandle.cpp \
    ./Handlers/ItemEventHandle.cpp \
    ./Handlers/PlayerEventHandle.cpp

HEADERS += \
    Types.h \
    Handler.h

LIBS += -L../Libs\
    -lTypes \
    -lUtils
