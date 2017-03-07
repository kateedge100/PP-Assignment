TARGET = app.bin
#CONFIG += console c++11
#CONFIG -= app_bundle
#CONFIG -= qt

SOURCES += $$PWD/src/main.cpp

INCLUDEPATH+=../MyLib/include
DEPENDPATH+=../MyLib/include
LIBS+= -L../MyLib/lib -lmyLib
OTHER_FILES+=$$PWD/app

QMAKE_RPATHDIR+=../MyLib/lib
