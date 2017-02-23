TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    quarternion.cpp

HEADERS += \
    matrix.h \
    quarternion.h

OTHER_FILES += README.md
