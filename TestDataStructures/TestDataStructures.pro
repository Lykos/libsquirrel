#-------------------------------------------------
#
# Project created by QtCreator 2012-02-01T11:50:38
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_all_tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    longinttest.cpp \
    arraylisttest.cpp \
    AllTests.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix:!macx:!symbian: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures

INCLUDEPATH += $$PWD/../DataStructures
DEPENDPATH += $$PWD/../DataStructures

HEADERS += \
    longinttest.h \
    arraylisttest.h
