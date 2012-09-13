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
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3

TEMPLATE = app


SOURCES += \
    performanceresult.cpp \
    performancetest.cpp \
    AllPerformanceTests.cpp \
    longinttest.cpp \
    comparemilliseconds.cpp

HEADERS += \
    compositeperformanceresult.h \
    performanceresult.h \
    longinttest.h \
    performancetest.h \
    comparemacros.h \
    comparemilliseconds.h

symbian: LIBS += -lDataStructures
else:CONFIG(release, debug|release): LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lDataStructures
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures

symbian: LIBS += -lLongArithmetic
else:CONFIG(release, debug|release): LIBS += -L$$PWD/../LongArithmetic-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lLongArithmetic
else:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LongArithmetic-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lLongArithmetic

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

CONFIG(debug, debug|release): LIBS += -lgmp -lgmpxx
