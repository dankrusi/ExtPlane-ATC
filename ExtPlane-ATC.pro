#-------------------------------------------------
#
# Project created by QtCreator 2013-04-13T18:55:35
#
#-------------------------------------------------

QT       += core gui network widgets

TARGET = ExtPlane-ATC
TEMPLATE = app

OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
INCLUDEPATH += build

SOURCES += main.cpp\
        widget.cpp \
    audiorecorder.cpp \
    audiotranscriber.cpp \
    googleaudiotranscriber.cpp \
    json.cpp \
    audioplayer.cpp \
    util.cpp

HEADERS  += widget.h \
    audiorecorder.h \
    audiotranscriber.h \
    googleaudiotranscriber.h \
    json.h \
    audioplayer.h \
    util.h

FORMS    += widget.ui


OTHER_FILES += README.md \
    scripts/tts-linux.sh \
    scripts/tts-osx.sh


macx {
    copyfiles.commands += cp -Rf ../$${TARGET}/scripts ./$${TARGET}.app/Contents/MacOS/
}
QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles
