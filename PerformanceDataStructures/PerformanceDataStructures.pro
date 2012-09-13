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
QMAKE_CXXFLAGS += -std=c++0x -O2

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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Release/release/ -lDataStructures
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Release/debug/ -lDataStructures
else:symbian: LIBS += -lDataStructures
else:unix: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lDataStructures

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LongArithmetic-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/release/ -lLongArithmetic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LongArithmetic-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/debug/ -lLongArithmetic
else:symbian: LIBS += -lLongArithmetic
else:unix: LIBS += -L$$PWD/../LongArithmetic-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lLongArithmetic

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

LIBS += -lgmp -lgmpxx
