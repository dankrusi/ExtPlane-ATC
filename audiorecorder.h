#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <QObject>
#include <QProcess>

#include "settings.h"

class AudioRecorder : public QObject
{
    Q_OBJECT
public:
    explicit AudioRecorder(QObject *parent, Settings *appSettings);
    void beginRecording();
    void stopRecording();
    QString outputFile() { return _outputFile; }
    
signals:
    
public slots:
    
private:
    QString _outputFile;
    QProcess *_recordProcess;
    Settings *_appSettings;
};

#endif // AUDIORECORDER_H
