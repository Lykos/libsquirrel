#-------------------------------------------------
#
# Project created by QtCreator 2012-09-12T18:28:12
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_testlongarithmetictest
CONFIG   += console warn_on
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app


SOURCES += \
    polynomialtest.cpp \
    longinttest.cpp \
    longarithmetictests.cpp \
    finiteelementtest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    polynomialtest.h \
    longinttest.h \
    finiteelementtest.h \
    comparemacros.h

symbian: LIBS += -lDataStructures
else:unix|win32: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lDataStructures

symbian: LIBS += -lLongArithmetic
else:unix|win32: LIBS += -L$$PWD/../LongArithmetic-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lLongArithmetic

unix|win32: LIBS += -lgmp -lgmpxx

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
