######################################################################
# Automatically generated by qmake (3.0) Mon Jul 8 07:35:53 2019
######################################################################

TEMPLATE = app
TARGET = StockMarketGame
INCLUDEPATH += .

# Input
QT += widgets printsupport

FORMS += \
    UIComponents/GamerunUI.ui \
    UIComponents/Graph.ui \
    UIComponents/MainWindow.ui \
    UIComponents/NewGameUI.ui

HEADERS += \
    ADTs/BasicStock.h \
    ADTs/Bond.h \
    ADTs/Portfolio.h \
    ADTs/Stock.h \
    ADTs/StockManager.h \
    ADTs/User.h \
    ADTs/UserManager.h \
    Exceptions/Exception.h \
    libs/json.hpp \
    libs/qcustomplot.h \
    Managers/Decorator.h \
    Managers/Gamerun.h \
    Managers/GameStateBase.h \
    Managers/GameStateManager.h \
    Managers/LoadGameState.h \
    Managers/NewGameState.h \
    UIHandlers/GamerunUI.h \
    UIHandlers/Graph.h \
    UIHandlers/MainWindow.h \
    UIHandlers/NewGameUI.h

SOURCES += \
    ADTs/BasicStock.cc \
    ADTs/Bond.cc \
    ADTs/Portfolio.cc \
    ADTs/Stock.cc \
    ADTs/StockManager.cc \
    ADTs/User.cc \
    ADTs/UserManager.cc \
    Exceptions/Exception.cc \
    libs/qcustomplot.cpp \
    Managers/Decorator.cc \
    Managers/Gamerun.cc \
    Managers/GameStateBase.cc \
    Managers/GameStateManager.cc \
    Managers/LoadGameState.cc \
    Managers/NewGameState.cc \
    UIHandlers/GamerunUI.cc \
    UIHandlers/Graph.cc \
    UIHandlers/MainWindow.cc \
    UIHandlers/NewGameUI.cc \
    main.cc
