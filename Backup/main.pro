TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    backup.cpp \
    client.cpp \
    generalbackup.cpp \
    backupwithcheck.cpp

HEADERS += \
    backup.h \
    client.h \
    testhandler.h \
    generalbackup.h \
    backupwithcheck.h \
    BACKUP_STATUSES.h
