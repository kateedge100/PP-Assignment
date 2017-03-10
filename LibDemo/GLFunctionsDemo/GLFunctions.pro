# we are going to build an app
TARGET=app.bin
CONFIG+=c++11
# qt 5 wants this may cause errors with 4
isEqual(QT_MAJOR_VERSION, 5) {cache() }
QT += core
QT +=opengl

OBJECTS_DIR=$$PWD/obj
SOURCES=$$PWD/src/main.cpp \
        $$PWD/src/SDLOpenGL.cpp \
        $$PWD/src/GLFunctions.cpp

HEADERS += \
          $$PWD/include/SDLOpenGL.h \
          $$PWD/include/GLFunctions.h

CONFIG-=app_bundle


INCLUDEPATH+=../../MyLib/include
DEPENDPATH+=../../MyLib/include
LIBS+= -L../../MyLib/lib -lmyLib

QMAKE_RPATHDIR+=../../MyLib/lib

QMAKE_CXXFLAGS+= -msse -msse2 -msse3
macx:QMAKE_CXXFLAGS+= -arch x86_64

QMAKE_CXXFLAGS += $$system(sdl2-config --cflags)
LIBS+=$$system(sdl2-config --libs)

OTHER_FILES+=$$PWD/app


LIBS += -L/usr/local/lib
macx:LIBS+= -framework OpenGL
# now if we are under unix and not on a Mac (i.e. linux) define GLEW
linux-g++:linux-g++-64 {
    LIBS+= -lGLEW
}
linux-clang {
    LIBS+= -lGLEW
}
