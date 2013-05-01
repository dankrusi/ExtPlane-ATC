#ifndef AUDIORECORDER_H
#define AUDIORECORDER_H

#include <QObject>
#include <QProcess>

class AudioRecorder : public QObject
{
    Q_OBJECT
public:
    explicit AudioRecorder(QObject *parent = 0);
    void beginRecording();
    void stopRecording();
    QString outputFile() { return _outputFile; }
    
signals:
    
public slots:
    
private:
    QString _outputFile;
    QProcess *_recordProcess;
};

#endif // AUDIORECORDER_H
