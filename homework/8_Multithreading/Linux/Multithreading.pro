TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -pthread

SOURCES += main.cpp \
    getUnsignedInt.cpp \
    getch.cpp \
    ArrayFunctions.cpp

HEADERS += \
    getUnsignedInt.h \
    getch.h \
    ArrayFunctions.h
