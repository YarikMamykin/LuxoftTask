#-------------------------------------------------
#
# Project created by QtCreator 2018-01-24T15:27:24
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = LuxoftTask
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    FileController.cpp \
    WordController.cpp \
    UnitTest.cpp

HEADERS += \
    WordController.h \
    FileController.h \
    UnitTest.h

OTHER_FILES += \
    example.txt \
    example_out.txt \
    test.qml
