#-------------------------------------------------
#
# Project created by QtCreator 2012-07-22T13:55:47
#
#-------------------------------------------------

QT       -= gui

TARGET = Crypto
TEMPLATE = lib

DEFINES += CRYPTO_LIBRARY

SOURCES += crypto.cpp

HEADERS += crypto.h\
        Crypto_global.h

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
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
