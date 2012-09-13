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
    heaptest.cpp \
    datastructurestests.cpp \
    arithmetichelpertest.cpp \
    heaparithmetictest.cpp \
    queuetest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    infiniterandomtest.h \
    heaptest.h \
    treetest.h \
    treaptest.h \
    avltreetest.h \
    arithmetichelpertest.h \
    comparemacros.h \
    heaparithmetictest.h \
    arraylisttest.h \
    listtest.h \
    listtest.hpp \
    treetest.hpp \
    queuetest.h

symbian: LIBS += -lDataStructures
else:unix|win32: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
