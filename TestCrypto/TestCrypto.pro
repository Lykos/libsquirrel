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
    elgamaltest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    rsatest.h \
    elgamaltest.h

debug {
    unix:!macx:!symbian: LIBS += -L$$PWD/../Crypto-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures
}

release {
    unix:!macx:!symbian: LIBS += -L$$PWD/../Crypto-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lDataStructures
}

INCLUDEPATH += $$PWD/../Crypto
DEPENDPATH += $$PWD/../Crypto

debug {
    unix:!macx:!symbian: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures
}

release {
    unix:!macx:!symbian: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lDataStructures
}

INCLUDEPATH += $$PWD/../DataStructures
DEPENDPATH += $$PWD/../DataStructures
