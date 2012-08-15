#-------------------------------------------------
#
# Project created by QtCreator 2012-07-18T13:56:29
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_performance_tests
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    performanceresult.cpp \
    performancetest.cpp \
    AllPerformanceTests.cpp \
    longinttest.cpp

unix:!macx:!symbian: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures

INCLUDEPATH += $$PWD/../DataStructures
DEPENDPATH += $$PWD/../DataStructures

HEADERS += \
    compositeperformanceresult.h \
    performanceresult.h \
    longinttest.h \
    performancetest.h