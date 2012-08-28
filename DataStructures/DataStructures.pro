#-------------------------------------------------
#
# Project created by QtCreator 2012-02-01T11:08:31
#
#-------------------------------------------------

QT       -= core gui

TARGET = DataStructures
TEMPLATE = lib
CONFIG += warn_on
QMAKE_CXXFLAGS += -std=c++0x

DEFINES += DATASTRUCTURES_LIBRARY

SOURCES += \
    longint.cpp \
    infiniterandom.cpp \
    baselist.cpp \
    heap.cpp \
    uniformlongintdistribution.cpp

HEADERS += \
    DataStructures_global.h \
    longint.h \
    infiniterandom.h \
    treap.h \
    treapnode.h \
    basetypes.h \
    baseiterator.h \
    queue.h \
    listiterator.h \
    baselist.h \
    arraylist.h \
    basetree.h \
    treenode.h \
    treeiterator.h \
    heap.h \
    avltree.h \
    avlnode.h \
    fibonacciheap.h \
    finitefield.h \
    finiteelement.h \
    polynomial.h \
    arithmetichelper.h \
    uniformlongintdistribution.h

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

unix|win32: LIBS += -lboost_random
