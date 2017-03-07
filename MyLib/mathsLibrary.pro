TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

#SOURCES += $$PWD/src/main.cpp

OBJECTS_DIR = $$PWD/obj

HEADERS += \
    $$PWD/include/matrix.h \
    $$PWD/include/quaternion.h

TARGET=$$PWD/lib/myLib

OTHER_FILES += README.md
