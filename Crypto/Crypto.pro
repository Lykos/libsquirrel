#-------------------------------------------------
#
# Project created by QtCreator 2012-07-22T13:55:47
#
#-------------------------------------------------

QT       -= gui

TARGET = Crypto
TEMPLATE = lib

DEFINES += CRYPTO_LIBRARY

SOURCES += \
    rsa_decrypter.cpp \
    rsa_directstrategy.cpp \
    rsa_keygenerator.cpp \
    rsa_pqstrategy.cpp \
    rsa_encrypter.cpp \
    primetester.cpp \
    elgamal_decrypter.cpp \
    elgamal_encrypter.cpp \
    elgamal_keygenerator.cpp \
    elgamal_keypersonalizer.cpp

HEADERS +=\
        Crypto_global.h \
    decrypter.h \
    encrypter.h \
    keygenerator.h \
    rsa_decrypter.h \
    rsa_decryptstrategy.h \
    rsa_directstrategy.h \
    rsa_encrypter.h \
    rsa_keygenerator.h \
    rsa_pqstrategy.h \
    rsa_types.h \
    primetester.h \
    keyreader.h \
    keywriter.h \
    elgamal_decrypter.h \
    elgamal_types.h \
    elgamal_encrypter.h \
    elgamal_keygenerator.h \
    keypersonalizer.h \
    elgamal_keypersonalizer.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE86CA0F1
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = Crypto.dll
    addFiles.path = !:/sys/bin
    DEPLOYMENT += addFiles
}

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/local/lib
    } else {
        target.path = /usr/local/lib
    }
    INSTALLS += target
}

unix:!macx:!symbian: LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures

INCLUDEPATH += $$PWD/../DataStructures
DEPENDPATH += $$PWD/../DataStructures
