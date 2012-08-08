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
    rsakey.cpp \
    rsaencrypter.cpp \
    rsakeygenerator.cpp \
    rsadecrypter.cpp \
    rsadirectstrategy.cpp \
    rsapqstrategy.cpp \
    keypair.cpp \
    rsakeypair.cpp \
    rsastrategy.cpp

HEADERS +=\
        Crypto_global.h \
    rsakey.h \
    rsastrategy.h \
    rsaencrypter.h \
    rsakeygenerator.h \
    rsadecrypter.h \
    rsadirectstrategy.h \
    rsapqstrategy.h \
    decrypter.h \
    key.h \
    keypair.h \
    encrypter.h \
    rsakeypair.h \
    keygenerator.h

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
