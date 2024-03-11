QT += core network gui widgets

TARGET = miniServer
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += debug_and_release

SOURCES += \
    clientchats.cpp \
    chatprotocol.cpp \
    clientmanager.cpp \
    servermanager.cpp \
    mainwindow.cpp \
    main.cpp

FORMS += \
    clientchats.ui \
    mainwindow.ui


HEADERS += \
    clientchats.h \
    chatprotocol.h \
    clientmanager.h \
    servermanager.h \
    mainwindow.h
