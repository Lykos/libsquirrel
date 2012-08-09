#-------------------------------------------------
#
# Project created by QtCreator 2012-02-01T11:08:31
#
#-------------------------------------------------

QT       -= core gui

TARGET = DataStructures
TEMPLATE = lib

DEFINES += DATASTRUCTURES_LIBRARY

SOURCES += \
    longint.cpp \
    arraylist.cpp \
    infiniterandom.cpp \
    treapbaseiterator.cpp

HEADERS +=\
        DataStructures_global.h \
    arraylist.h \
    longint.h \
    infiniterandom.h \
    treap.h \
    treapnode.h \
    treapbaseiterator.h
    basetypes.h

symbian {
    MMP_RULES += EXPORTUNFROZEN
    TARGET.UID3 = 0xE1D035E6
    TARGET.CAPABILITY = 
    TARGET.EPOCALLOWDLLDATA = 1
    addFiles.sources = DataStructures.dll
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
