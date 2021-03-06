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
QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app


SOURCES += \
    cryptotests.cpp \
    rsatest.cpp \
    elgamaltest.cpp \
    aestest.cpp \
    cbctest.cpp \
    dhtest.cpp \
    sha2test.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    rsatest.h \
    elgamaltest.h \
    aestest.h \
    cbctest.h \
    dhtest.h \
    sha2test.h

symbian: LIBS += -lDataStructures
else:unix|win32: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lDataStructures

symbian: LIBS += -lLongArithmetic
else:unix|win32: LIBS += -L$$PWD/../LongArithmetic-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lLongArithmetic

symbian: LIBS += -lCrypto
else:unix|win32: LIBS += -L$$PWD/../Crypto-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lCrypto

unix|win32: LIBS += -lgmp -lgmpxx -lboost_random

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
