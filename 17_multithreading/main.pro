TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -pthread

SOURCES += main.cpp \
    ArrayFunctions.cpp \
    getch.cpp \
    getUnsignedInt.cpp

HEADERS += \
    ArrayFunctions.h \
    getch.h \
    getUnsignedInt.h
