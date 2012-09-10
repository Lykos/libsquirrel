#-------------------------------------------------
#
# Project created by QtCreator 2012-08-22T21:39:53
#
#-------------------------------------------------

QT       -= gui

TARGET = RubyCrypto
TEMPLATE = lib
QMAKE_CXXFLAGS += -std=c++11

DEFINES += RUBYCRYPTO_LIBRARY

SOURCES += \
    RubyCrypto.c \
    cryptoexception.cpp \
    crypto.cpp \
    longint.cpp \
    sha2hasher.cpp \
    elgamalsigner.cpp \
    elgamalverifier.cpp \
    cbcencrypter.cpp \
    cbcdecrypter.cpp \
    cbcmac.cpp \
    dhkeyexchange.cpp \
    elgamalkeygenerator.cpp

HEADERS +=\
    RubyCrypto.h \
    cryptoexception.h \
    crypto.h \
    longint.h \
    sha2hasher.h \
    elgamalsigner.h \
    elgamalverifier.h \
    cbcencrypter.h \
    cbcdecrypter.h \
    cbcmac.h \
    dhkeyexchange.h \
    elgamalkeygenerator.h

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

unix:!macx:!symbian: LIBS += -L$$PWD/../Crypto-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lCrypto

INCLUDEPATH += $$PWD/..
DEPENDPATH += $$PWD/..

unix:!macx:!symbian: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures


INCLUDEPATH += $$PWD/..
DEPENDPATH += $$PWD/..

unix|win32: LIBS += -lruby -lboost_random

INCLUDEPATH += /usr/include/ruby-1.9.1/ /usr/include/ruby-1.9.1/x86_64-linux
DEPENDPATH += /usr/include/ruby-1.9.1/ /usr/include/ruby-1.9.1/x86_64-linux

OTHER_FILES += \
    extconf.rb

