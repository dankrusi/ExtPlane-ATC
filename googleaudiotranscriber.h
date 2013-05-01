#ifndef GOOGLEAUDIOTRANSCRIBER_H
#define GOOGLEAUDIOTRANSCRIBER_H

#include "audiotranscriber.h"

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>

class GoogleAudioTranscriber : public AudioTranscriber
{
    Q_OBJECT
public:
    explicit GoogleAudioTranscriber(QObject *parent = 0);
    virtual void transcribeAudioFile(QString filename);
    
signals:
    
public slots:
    void networkRequestFinished(QNetworkReply *reply);

private:
    QNetworkAccessManager *_netManager;
    
};

#endif // GOOGLEAUDIOTRANSCRIBER_H
