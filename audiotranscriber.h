#ifndef AUDIOTRANSCRIBER_H
#define AUDIOTRANSCRIBER_H

#include <QObject>

class AudioTranscriber : public QObject
{
    Q_OBJECT
public:
    explicit AudioTranscriber(QObject *parent = 0);
    virtual void transcribeAudioFile(QString filename) = 0;
    
signals:
    void transcribeCompleted(QString result);
    
public slots:
    
};

#endif // AUDIOTRANSCRIBER_H
