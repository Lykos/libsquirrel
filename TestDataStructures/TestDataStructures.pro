#-------------------------------------------------
#
# Project created by QtCreator 2012-02-01T11:50:38
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = datastructures_tests
CONFIG   += console warn_on
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app

SOURCES += \
    infiniterandomtest.cpp \
    queuetest.cpp \
    heaptest.cpp \
    datastructurestests.cpp \
    polynomialtest.cpp \
    finiteelementtest.cpp \
    arithmetichelpertest.cpp \
    longinttest.cpp \
    heaparithmetictest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

unix:!macx:!symbian: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures

INCLUDEPATH += $$PWD/.. $$PWD/../DataStructures
DEPENDPATH += $$PWD/../DataStructures

HEADERS += \
    longinttest.h \
    infiniterandomtest.h \
    queuetest.h \
    heaptest.h \
    treetest.h \
    treaptest.h \
    avltreetest.h \
    polynomialtest.h \
    finiteelementtest.h \
    arithmetichelpertest.h \
    comparemacros.h \
    heaparithmetictest.h \
    listtest.h \
    arraylisttest.h \
    listtest.hpp \
    treetest.hpp
