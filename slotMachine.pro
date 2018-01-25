#-------------------------------------------------
#
# Project created by QtCreator 2017-10-21T19:05:58
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SlotMachine
TEMPLATE = app

LIBS = -lglu32 -lopengl32

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp\
        sources/glwidget.cpp \
    sources/canvas.cpp \
    sources/textureobjectmanager.cpp \
    sources/button.cpp \
    sources/buttonstart.cpp \
    sources/buttonstop.cpp \
    sources/object.cpp \
    sources/wheel.cpp \
    sources/slotmachine.cpp

HEADERS  += headers/glwidget.h \
    headers/common.h \
    headers/canvas.h \
    headers/textureobjectmanager.h \
    headers/button.h \
    headers/buttonstart.h \
    headers/buttonstop.h \
    headers/object.h \
    headers/wheel.h \
    headers/slotmachine.h

RESOURCES += \
    resources.qrc
