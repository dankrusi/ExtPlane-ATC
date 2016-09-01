#ifndef AUDIOTRANSCRIBER_H
#define AUDIOTRANSCRIBER_H

#include <QObject>

#include "settings.h"

class AudioTranscriber : public QObject
{
    Q_OBJECT
public:
    explicit AudioTranscriber(QObject *parent, Settings *appSettings);
    virtual void transcribeAudioFile(QString filename) = 0;
    
signals:
    void transcribeCompleted(QString result);
    
public slots:

private:
    Settings *_appSettings;
    
};

#endif // AUDIOTRANSCRIBER_H
