TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    SmartPointer.cpp \
    point.cpp \
    line.cpp \
    Array.cpp

HEADERS += \
    SmartPointer.h \
    line.h \
    point.h \
    Array.h
