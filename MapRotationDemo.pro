#-------------------------------------------------
#
# Project created by QtCreator 2012-09-12T19:27:19
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = MapRotationDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mazewindow.cpp \
    glwidget.cpp \
    qmazegen.cpp

HEADERS  += mainwindow.h \
    mazewindow.h \
    glwidget.h \
    qmazegen.h

FORMS    += mainwindow.ui \
    mazewindow.ui


QMAKE_CXXFLAGS += -std=c++0x


!win32 {
    LIBS += -lglut -lGL -lGLU
}
