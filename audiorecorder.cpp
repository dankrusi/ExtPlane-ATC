#include "audiorecorder.h"

#include <QDebug>

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

    QString recordProgram = "arecord";
    QStringList recordArguments;
    recordArguments << "-f" << "cd" << "-t" << "wav";


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
