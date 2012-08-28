#-------------------------------------------------
#
# Project created by QtCreator 2012-08-15T22:43:46
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = crypto_tests
CONFIG   += console warn_on
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = app


SOURCES += \
    cryptotests.cpp \
    rsatest.cpp \
    elgamaltest.cpp \
    aestest.cpp \
    sha256test.cpp \
    cbctest.cpp \
    dhtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    rsatest.h \
    elgamaltest.h \
    aestest.h \
    sha256test.h \
    cbctest.h \
    dhtest.h

unix:!macx:!symbian: LIBS += -L$$PWD/../Crypto-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lCrypto

INCLUDEPATH += $$PWD/../Crypto
DEPENDPATH += $$PWD/../Crypto

unix:!macx:!symbian: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures

INCLUDEPATH += $$PWD/../DataStructures
DEPENDPATH += $$PWD/../DataStructures
