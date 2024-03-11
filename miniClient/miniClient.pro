QT += core network gui widgets

TARGET = miniClient
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS


CONFIG += debug_and_release

SOURCES += \
    chatitemwidget.cpp \
    chatprotocol.cpp \
    clientmanager.cpp \
    itemwidget.cpp \
    mainwindow.cpp \
    main.cpp

FORMS += \
    chatitemwidget.ui \
    itemwidget.ui \
    mainwindow.ui
    

HEADERS += \
    chatitemwidget.h \
    chatprotocol.h \
    clientmanager.h \
    itemwidget.h \
    mainwindow.h 
