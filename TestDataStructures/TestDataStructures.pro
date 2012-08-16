#-------------------------------------------------
#
# Project created by QtCreator 2012-02-01T11:50:38
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = datastructures_tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    longinttest.cpp \
    arraylisttest.cpp \
    infiniterandomtest.cpp \
    treaptest.cpp \
    queuetest.cpp \
    heaptest.cpp \
    datastructurestests.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix:!macx:!symbian: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures

INCLUDEPATH += $$PWD/../DataStructures
DEPENDPATH += $$PWD/../DataStructures

HEADERS += \
    longinttest.h \
    arraylisttest.h \
    infiniterandomtest.h \
    treaptest.h \
    queuetest.h \
    heaptest.h
