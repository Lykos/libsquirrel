#-------------------------------------------------
#
# Project created by QtCreator 2012-09-12T17:31:59
#
#-------------------------------------------------

QT       -= core gui

TARGET = LongArithmetic
TEMPLATE = lib
CONFIG += warn_on
QMAKE_CXXFLAGS += -std=c++11
CONFIG(release, debug|release) QMAKE_CXXFLAGS += -O3

DEFINES += LONGARITHMETIC_LIBRARY
CONFIG(debug, debug|release) DEFINES += ARITHMETIC_DEBUG

SOURCES += \
    uniformlongintdistribution.cpp \
    multiply.cpp \
    longintconverter.cpp \
    longint.cpp \
    divide.cpp \
    algebraicstructure.cpp \
    preconditionviolation.cpp

HEADERS += \
    uniformlongintdistribution.hpp \
    uniformlongintdistribution.h \
    thresholds.h \
    subtract.hpp \
    subtract.h \
    shifts.hpp \
    shifts.h \
    ring.hpp \
    ring.h \
    polynomial.hpp \
    polynomial.h \
    platform.h \
    multiply.h \
    longintconverter.h \
    longint.h \
    incdec.hpp \
    incdec.h \
    finitefield.hpp \
    finitefield.h \
    finiteelement.hpp \
    finiteelement.h \
    field.hpp \
    field.h \
    divide.h \
    compare.hpp \
    compare.h \
    assembly.h \
    algebraicstructure.h \
    algebrahelper.hpp \
    algebrahelper.h \
    add.hpp \
    add.h \
    arithmetichelper.hpp \
    arithmetichelper.h \
    conditiontype.h \
    prec_macro.h \
    preconditionviolation.h \
    debug.h

header_files.files = $$HEADERS
header_files.path = /usr/local/include/LongArithmetic
INSTALLS += header_files

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE1E3FF27
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = LongArithmetic.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lDataStructures
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures
else:symbian: LIBS += -lDataStructures
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lDataStructures
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures

INCLUDEPATH += $$PWD/../
DEPENDPATH += $$PWD/../

LIBS += -lgmp -lgmpxx
