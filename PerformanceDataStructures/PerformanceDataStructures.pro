#-------------------------------------------------
#
# Project created by QtCreator 2012-07-18T13:56:29
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_performance_tests
CONFIG   += console warn_on
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = app


SOURCES += \
    performanceresult.cpp \
    performancetest.cpp \
    AllPerformanceTests.cpp \
    longinttest.cpp

debug {
    unix:!macx:!symbian: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures
}

release {
    unix:!macx:!symbian: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lDataStructures
}

INCLUDEPATH += $$PWD/../DataStructures
DEPENDPATH += $$PWD/../DataStructures

HEADERS += \
    compositeperformanceresult.h \
    performanceresult.h \
    longinttest.h \
    performancetest.h
