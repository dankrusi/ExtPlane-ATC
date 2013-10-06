#include "audiorecorder.h"

#include <QDebug>

#include "util.h"

AudioRecorder::AudioRecorder(QObject *parent) :
    QObject(parent)
{
    _recordProcess = NULL;
    _outputFile = "/home/flightsim/ExtPlane-ATC/out/out.flac";
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

    if(Util::GetPlatform() == PLATFORM_LINUX) {
        recordProgram = "arecord";
        recordArguments << "-f" << "cd" << "-t" << "wav";
    } else if(Util::GetPlatform() == PLATFORM_OSX) {
        qFatal("OSX not yet supported. Sorry.");
    } else if(Util::GetPlatform() == PLATFORM_WINDOWS) {
        qFatal("Windows not yet supported. Sorry.");
    } else {
        qFatal("Unknown platform.");
    }

    _recordProcess = new QProcess(this);
    _recordProcess->setStandardOutputFile("/home/flightsim/ExtPlane-ATC/out/out.wav");
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

    // Convert
    QProcess convertProcess;
    QString convertProgram = "flac";
    QStringList convertArguments;
    convertArguments << "-f";
    convertArguments << "-8";
    convertArguments << "-f" << "-o" << _outputFile;
    convertArguments << "/home/flightsim/ExtPlane-ATC/out/out.wav";
    //convertArguments << "--sample-rate=44100";
    convertProcess.execute(convertProgram,convertArguments);

    //delete _recordProcess;
}
