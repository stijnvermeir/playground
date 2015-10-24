#-------------------------------------------------
#
# Project created by QtCreator 2015-10-23T18:03:36
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = mkmtest
CONFIG   += console
CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp \
    test.cpp

MKMLIB_PATH = $$PWD/../../../mkmlib

CONFIG(release, debug|release): LIBS += -L$$MKMLIB_PATH/build/release/
else:CONFIG(debug, debug|release): LIBS += -L$$MKMLIB_PATH/build/debug/

LIBS += -lmkm

INCLUDEPATH += $$MKMLIB_PATH/mkm
DEPENDPATH += $$MKMLIB_PATH/mkm

HEADERS += \
    test.h
