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

# Place ExtPlane plugin to a directory next to or inside build directory, or
# define the directory here:
EXTPLANE_PLUGIN_PATH=../ExtPlane
!exists($$EXTPLANE_PLUGIN_PATH/client/extplane-client-qt) {
        EXTPLANE_PLUGIN_PATH=ExtPlane
        !exists($$EXTPLANE_PLUGIN_PATH/client/extplane-client-qt) {
                error("You don't have ExtPlane checked out in directory next to this. Place it there or build will fail.")
        }
}
EXTPLANE_CLIENT_PATH=$$EXTPLANE_PLUGIN_PATH/client/extplane-client-qt
INCLUDEPATH += $$EXTPLANE_CLIENT_PATH

# Debug settings
CONFIG(debug, debug|release) {
    # Debug
} else {
    # Release
    DEFINES += QT_NO_DEBUG
    DEFINES += QT_NO_DEBUG_OUTPUT
}

SOURCES += \
    $$EXTPLANE_CLIENT_PATH/extplaneconnection.cpp \
    $$EXTPLANE_CLIENT_PATH/extplaneclient.cpp \
    $$EXTPLANE_CLIENT_PATH/clientdataref.cpp \
    $$EXTPLANE_CLIENT_PATH/clientdatarefprovider.cpp \
    $$EXTPLANE_CLIENT_PATH/simulateddatarefs/simulateddataref.cpp \
    $$EXTPLANE_CLIENT_PATH/simulateddatarefs/fixedsimulateddataref.cpp \
    $$EXTPLANE_CLIENT_PATH/simulateddatarefs/alternatingsimulateddataref.cpp \
    $$EXTPLANE_CLIENT_PATH/simulatedextplaneconnection.cpp \
    main.cpp \
    widget.cpp \
    audiorecorder.cpp \
    audiotranscriber.cpp \
    googleaudiotranscriber.cpp \
    json.cpp \
    audioplayer.cpp \
    util.cpp

HEADERS  += \
    $$EXTPLANE_CLIENT_PATH/extplaneconnection.h \
    $$EXTPLANE_CLIENT_PATH/extplaneclient.h \
    $$EXTPLANE_CLIENT_PATH/clientdataref.h \
    $$EXTPLANE_CLIENT_PATH/clientdatarefprovider.h \
    $$EXTPLANE_CLIENT_PATH/simulateddatarefs/simulateddataref.h \
    $$EXTPLANE_CLIENT_PATH/simulateddatarefs/fixedsimulateddataref.h \
    $$EXTPLANE_CLIENT_PATH/simulateddatarefs/alternatingsimulateddataref.h \
    $$EXTPLANE_CLIENT_PATH/simulatedextplaneconnection.h \
    widget.h \
    audiorecorder.h \
    audiotranscriber.h \
    googleaudiotranscriber.h \
    json.h \
    audioplayer.h \
    util.h

FORMS    += widget.ui \
    settings.ui


OTHER_FILES += README.md \
    scripts/tts-linux.sh \
    scripts/tts-osx.sh


macx {
    copyfiles.commands += cp -Rf ../$${TARGET}/scripts ./$${TARGET}.app/Contents/MacOS/
}
QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles
