#-------------------------------------------------
#
# Project created by QtCreator 2012-02-01T11:08:31
#
#-------------------------------------------------

QT       -= core gui

TARGET = DataStructures
TEMPLATE = lib
CONFIG += warn_on
QMAKE_CXXFLAGS += -std=c++11

DEFINES += DATASTRUCTURES_LIBRARY

SOURCES += \
    longint.cpp \
    infiniterandom.cpp \
    uniformlongintdistribution.cpp \
    longintconverter.cpp \
    divide.cpp \
    multiply.cpp \
    preconditionviolation.cpp \
    algebraicstructure.cpp

HEADERS += \
    longint.h \
    infiniterandom.h \
    treap.h \
    treapnode.h \
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
    uniformlongintdistribution.h \
    algebrahelper.h \
    heaparithmetic.h \
    longintconverter.h \
    divide.h \
    multiply.h \
    add.h \
    subtract.h \
    assembly.h \
    platform.h \
    preconditionviolation.h \
    conditiontype.h \
    ring.h \
    algebraicstructure.h \
    fibonaccinode.h \
    treenode.hpp \
    treeiterator.hpp \
    treapnode.hpp \
    treap.hpp \
    subtract.hpp \
    ring.hpp \
    queue.hpp \
    polynomial.hpp \
    listiterator.hpp \
    heaparithmetic.hpp \
    heap.hpp \
    finitefield.hpp \
    finiteelement.hpp \
    fibonacciheap.hpp \
    basetree.hpp \
    baselist.hpp \
    baseiterator.hpp \
    avltree.hpp \
    avlnode.hpp \
    arraylist.hpp \
    arithmetichelper.hpp \
    algebrahelper.hpp \
    add.hpp \
    uniformlongintdistribution.hpp \
    fibonaccinode.hpp \
    field.hpp \
    field.h

header_files.files = $$HEADERS
header_files.path = /usr/local/include/DataStructures
INSTALLS += header_files

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

unix|win32: LIBS += -lboost_random -lgmp -lgmpxx
