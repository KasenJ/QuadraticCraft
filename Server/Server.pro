QT += \
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
    ./Handlers/DropEventHandle.cpp \
    ./Handlers/GetEventHandle.cpp \
    ./Handlers/MoveEventHandle.cpp

HEADERS += \
    Types.h \
    Handler.h

LIBS += -L../Libs\
    -lTypes
