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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/release/ -lDataStructures
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/debug/ -lDataStructures
else:symbian: LIBS += -lDataStructures
else:unix: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LongArithmetic-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/release/ -lLongArithmetic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LongArithmetic-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/debug/ -lLongArithmetic
else:symbian: LIBS += -lLongArithmetic
else:unix: LIBS += -L$$PWD/../LongArithmetic-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lLongArithmetic

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../
