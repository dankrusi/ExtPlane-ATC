#include "audioplayer.h"

#include <QProcess>
#include <QDebug>

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

    QProcess *p = new QProcess(this);
    QStringList args;
    args << QString::number(profile);
    args << QString("\"%1\"").arg(text);
    p->start("/home/dankrusi/Code/ExtPlane-ATC/scripts/tts-linux.sh",args);
}
