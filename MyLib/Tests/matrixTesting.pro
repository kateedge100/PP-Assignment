TARGET = app.bin

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH+=../../MyLib/include
DEPENDPATH+=../../MyLib/include

LIBS+= -lgtest \
        -L../../MyLib/lib -lmyLib

QMAKE_RPATHDIR+=../../MyLib/lib

SOURCES += \
    matrixTesting.cpp

OTHER_FILES+=$$PWD/app
