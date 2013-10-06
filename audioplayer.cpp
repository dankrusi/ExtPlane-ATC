#include "audioplayer.h"

#include <QProcess>
#include <QDebug>
#include <QApplication>
#include <QDir>

#include "util.h"

AudioPlayer::AudioPlayer(QObject *parent) :
    QObject(parent)
{
    _maxProfiles = 5;
}

void AudioPlayer::speak(QString text) {
    int profile = (qrand() % _maxProfiles) + 1;
    speak(text,profile);
}

void AudioPlayer::speak(QString text, int profile) {
    qDebug() << profile << text;

    QStringList processArgs;
    //processArgs << QString::number(profile);
    //processArgs << QString("\"%1\"").arg(text);
    //processArgs << "/Users/dankrusi/Code/ExtPlane-ATC-build-Desktop_Qt_5_0_1_clang_64bit-Debug/ExtPlane-ATC.app/Contents/MacOS/tts-osx.sh";
    QString script;
    QString processName;

    if(Util::GetPlatform() == PLATFORM_LINUX) {
        processName = "sh";
        script = "scripts/tts-linux.sh";
    } else if(Util::GetPlatform() == PLATFORM_OSX) {
        processName = "sh";
        script = "scripts/tts-osx.sh";
    } else if(Util::GetPlatform() == PLATFORM_WINDOWS) {
        qFatal("Windows not yet supported. Sorry.");
    } else {
        qFatal("Unknown platform.");
    }

    QString scriptPath = QApplication::applicationDirPath() + QDir::separator() + script;
    processArgs << scriptPath;
    processArgs << QString::number(profile);
    processArgs << QString("\"%1\"").arg(text);

    QProcess *p = new QProcess(this);
    p->startDetached(processName,processArgs); // p->start() does not work on osx

}
