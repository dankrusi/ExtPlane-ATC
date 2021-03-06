#include "audiorecorder.h"

#include <QDebug>
#include <QApplication>
#include <QDir>

#include "util.h"

AudioRecorder::AudioRecorder(QObject *parent, Settings *appSettings) :
    QObject(parent)
{
    _appSettings = appSettings;
    _recordProcess = NULL;
    _outputFile = _appSettings->getLocalFile("out","out.flac");
}

void AudioRecorder::beginRecording()
{
    qDebug() << Q_FUNC_INFO;
    // arecord -f cd -t wav | flac - -f -o out.flac

    if(_recordProcess) {
        _recordProcess->kill();
        delete _recordProcess;
    }

    QString recordProgram;
    QStringList recordArguments;
    _recordProcess = new QProcess(this);

    if(Util::GetPlatform() == PLATFORM_LINUX) {
        recordProgram = "arecord";
        recordArguments << "-f" << "cd" << "-t" << "wav";
        _recordProcess->setStandardOutputFile(_appSettings->getLocalFile("out","out16.wav"));
    } else if(Util::GetPlatform() == PLATFORM_OSX) {
        recordProgram = _appSettings->getLocalFile("scripts","sox-osx");
        recordArguments << "-d" << _appSettings->getLocalFile("out","out32.wav");
    } else if(Util::GetPlatform() == PLATFORM_WINDOWS) {
        qFatal("Windows not yet supported. Sorry.");
    } else {
        qFatal("Unknown platform.");
    }

    _recordProcess->start(recordProgram,recordArguments);


    qDebug() << Q_FUNC_INFO << "record started:" << recordProgram << recordArguments;
}

void AudioRecorder::stopRecording()
{
    qDebug() << Q_FUNC_INFO;

    // Stop recording
    _recordProcess->close();
    _recordProcess->terminate();
    _recordProcess->kill();

    // Convert to 16bps
    if(Util::GetPlatform() == PLATFORM_OSX) {
        qDebug() << "Converting to 16bps...";
        QProcess convert16Process;
        QString convert16Program = _appSettings->getLocalFile("scripts","sox-osx");
        QStringList convert16Arguments;
        convert16Arguments << _appSettings->getLocalFile("out","out32.wav");
        convert16Arguments << "-b";
        convert16Arguments << "16";
        convert16Arguments << _appSettings->getLocalFile("out","out16.wav");
        convert16Process.execute(convert16Program,convert16Arguments);
    }

    // Convert to flac
    qDebug() << "Converting to flac...";
    QProcess convertFlacProcess;
    QString convertFlacProgram = "flac";
    QStringList convertFlacArguments;

    if(Util::GetPlatform() == PLATFORM_LINUX) {
        convertFlacProgram = "flac";
    } else if(Util::GetPlatform() == PLATFORM_OSX) {
        convertFlacProgram = _appSettings->getLocalFile("scripts","flac-osx");
    } else if(Util::GetPlatform() == PLATFORM_WINDOWS) {
        qFatal("Windows not yet supported. Sorry.");
    } else {
        qFatal("Unknown platform.");
    }

    //convertFlacArguments << "-f";
    //convertFlacArguments << "-8";
    convertFlacArguments << "-f" << "-o" << _outputFile;
    convertFlacArguments << _appSettings->getLocalFile("out","out16.wav");
    convertFlacProcess.execute(convertFlacProgram,convertFlacArguments);
    qDebug() << "Conversion done.";

    //delete _recordProcess;
}
