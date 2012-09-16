#-------------------------------------------------
#
# Project created by QtCreator 2012-07-22T13:55:47
#
#-------------------------------------------------

QT       -= gui

TARGET = Crypto
TEMPLATE = lib
CONFIG += warn_on
QMAKE_CXXFLAGS += -std=c++11

DEFINES += CRYPTO_LIBRARY

SOURCES += \
    rsa_decrypter.cpp \
    rsa_directstrategy.cpp \
    rsa_pqstrategy.cpp \
    rsa_encrypter.cpp \
    primetester.cpp \
    elgamal_decrypter.cpp \
    elgamal_encrypter.cpp \
    aes_keyexpander.cpp \
    aes_encrypter.cpp \
    aes_helper.cpp \
    aes_decrypter.cpp \
    aes_constants.cpp \
    elgamal_signer.cpp \
    elgamal_verifier.cpp \
    primes.cpp \
    elgamal_keygenerator.cpp \
    dh_keygenerator.cpp \
    dh_converter.cpp \
    dh_constants.cpp \
    elgamal_converter.cpp \
    dh_keyexchange.cpp \
    sha2hasher.cpp \
    preconditionviolation.cpp

HEADERS +=\
    rsa_decrypter.h \
    rsa_decryptstrategy.h \
    rsa_directstrategy.h \
    rsa_encrypter.h \
    rsa_keygenerator.h \
    rsa_pqstrategy.h \
    rsa_types.h \
    primetester.h \
    elgamal_decrypter.h \
    elgamal_encrypter.h \
    elgamal_keygenerator.h \
    keypair.h \
    aes_keyexpander.h \
    aes_constants.h \
    aes_encrypter.h \
    aes_helper.h \
    aes_decrypter.h \
    elgamal_signer.h \
    elgamal_verifier.h \
    primes.h \
    cbc_encrypter.h \
    cbc_mac.h \
    dh_converter.h \
    dh_keygenerator.h \
    dh_types.h \
    dh_constants.h \
    elgamal_types.h \
    elgamal_converter.h \
    dh_keyexchange.h \
    sha2hasher.h \
    preconditionviolation.h \
    readnumber_macro.h \
    conditiontype.h \
    cbc_decrypter.h \
    types.h

header_files.files = $$HEADERS
header_files.path = /usr/local/include/Crypto
INSTALLS += header_files

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

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lDataStructures
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures
else:symbian: LIBS += -lDataStructures
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lDataStructures
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../DataStructures-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lDataStructures

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LongArithmetic-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lLongArithmetic
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LongArithmetic-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lLongArithmetic
else:symbian: LIBS += -lDataStructures
else:unix:CONFIG(release, debug|release): LIBS += -L$$PWD/../LongArithmetic-build-desktop-Qt_4_8_0_in_Pfad__System__Release/ -lLongArithmetic
else:unix:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LongArithmetic-build-desktop-Qt_4_8_0_in_Pfad__System__Debug/ -lLongArithmetic

INCLUDEPATH += $$PWD/..
DEPENDPATH += $$PWD/..
