#-------------------------------------------------
#
# Project created by QtCreator 2012-08-15T22:43:46
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = crypto_tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    cryptotests.cpp \
    rsatest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    rsatest.h

unix:!macx:!symbian: LIBS += -L$$PWD/../Crypto-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lCrypto

INCLUDEPATH += $$PWD/../Crypto \
    $$PWD/../DataStructures
DEPENDPATH += $$PWD/../Crypto \
    $$PWD/../DataStructures
