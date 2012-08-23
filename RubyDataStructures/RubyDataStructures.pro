#-------------------------------------------------
#
# Project created by QtCreator 2012-08-22T21:39:53
#
#-------------------------------------------------

QT       -= gui

TARGET = RubyDataStructures
TEMPLATE = lib
QMAKE_CXXFLAGS += -std=c++11

DEFINES += RUBYDATASTRUCTURES_LIBRARY

SOURCES += \
    RubyDataStructures.c \
    longint_interface.cpp

HEADERS +=\
    RubyDataStructures.h \
    longint_interface.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE2EC9E0B
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = RubyDataStructures.dll
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

debug {
    unix:!macx:!symbian: LIBS += -L$$PWD/../Crypto-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures
}

release {
    unix:!macx:!symbian: LIBS += -L$$PWD/../Crypto-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lDataStructures
}

INCLUDEPATH += $$PWD/../Crypto
DEPENDPATH += $$PWD/../Crypto

debug {
    unix:!macx:!symbian: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures
}

release {
    unix:!macx:!symbian: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lDataStructures
}

INCLUDEPATH += $$PWD/../DataStructures
DEPENDPATH += $$PWD/../DataStructures

unix|win32: LIBS += -lruby

INCLUDEPATH += /usr/include/ruby-1.9.1/ /usr/include/ruby-1.9.1/x86_64-linux
DEPENDPATH += /usr/include/ruby-1.9.1/ /usr/include/ruby-1.9.1/x86_64-linux

OTHER_FILES += \
    extconf.rb

