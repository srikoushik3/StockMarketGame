######################################################################
# Automatically generated by qmake (3.0) Mon Jul 8 07:35:53 2019
######################################################################

TEMPLATE = app
TARGET = StockMarketGame
INCLUDEPATH += .

# Input
QT += widgets
HEADERS += BasicStock.h Bond.h json.hpp Stock.h StockManager.h \
    mainwindow.h \
    newgamefilemanager.h
SOURCES += BasicStock.cc Bond.cc Stock.cc StockManager.cc \
    mainwindow.cpp \
    main.cc \
    newgamefilemanager.cpp

FORMS += \
    mainwindow.ui \
    newgamefilemanager.ui
