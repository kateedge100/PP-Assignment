TARGET = app.bin

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH+=../../include
DEPENDPATH+=../../include

LIBS+= -lgtest \
        -L../../lib -lmyLib

QMAKE_RPATHDIR+=../../lib

SOURCES += \
    matrixTesting.cpp

OTHER_FILES+=$$PWD/app
