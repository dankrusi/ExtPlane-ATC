#include "audioplayer.h"

#include <QProcess>
#include <QDebug>
#include <QApplication>
#include <QDir>

#include "util.h"

AudioPlayer::AudioPlayer(QObject *parent, Settings *appSettings) :
    QObject(parent)
{
    _appSettings = appSettings;
    _maxProfiles = 5;
}

void AudioPlayer::speak(QString text) {
    int profile = (qrand() % _maxProfiles) + 1;
    speak(text,profile);
}

void AudioPlayer::speak(QString text, int profile) {
    qDebug() << profile << text;

    QStringList processArgs;
    QString script;
    QString processName;
    QString scriptPath;

    if(Util::GetPlatform() == PLATFORM_LINUX) {
        processName = "sh";
        scriptPath = _appSettings->getLocalFile("scripts","tts-linux.sh");
    } else if(Util::GetPlatform() == PLATFORM_OSX) {
        processName = "sh";
        scriptPath = _appSettings->getLocalFile("scripts","tts-osx.sh");
    } else if(Util::GetPlatform() == PLATFORM_WINDOWS) {
        qFatal("Windows not yet supported. Sorry.");
    } else {
        qFatal("Unknown platform.");
    }

    processArgs << scriptPath;
    processArgs << QString::number(profile);
    processArgs << QString("\"%1\"").arg(text);

    QProcess *p = new QProcess(this);
    p->startDetached(processName,processArgs); // p->start() does not work on osx

}
