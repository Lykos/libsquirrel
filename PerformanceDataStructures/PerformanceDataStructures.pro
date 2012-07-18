#-------------------------------------------------
#
# Project created by QtCreator 2012-07-18T13:56:29
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = PerformanceDataStructures
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    performanceresult.cpp

unix:!macx:!symbian: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures

INCLUDEPATH += $$PWD/../DataStructures
DEPENDPATH += $$PWD/../DataStructures

HEADERS += \
    compositeperformanceresult.h \
    performanceresult.h
