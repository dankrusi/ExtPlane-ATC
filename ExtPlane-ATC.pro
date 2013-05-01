#-------------------------------------------------
#
# Project created by QtCreator 2013-04-13T18:55:35
#
#-------------------------------------------------

QT       += core gui network

TARGET = ExtPlane-ATC
TEMPLATE = app


SOURCES += main.cpp\
        widget.cpp \
    audiorecorder.cpp \
    audiotranscriber.cpp \
    googleaudiotranscriber.cpp \
    json.cpp \
    audioplayer.cpp

HEADERS  += widget.h \
    audiorecorder.h \
    audiotranscriber.h \
    googleaudiotranscriber.h \
    json.h \
    audioplayer.h

FORMS    += widget.ui
