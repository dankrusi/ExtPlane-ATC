#include "googleaudiotranscriber.h"

#include <QDebug>
#include <QFile>
#include <QNetworkRequest>

#include "json.h"

GoogleAudioTranscriber::GoogleAudioTranscriber(QObject *parent) :
    AudioTranscriber(parent)
{
    // Setup network manager
    _netManager = new QNetworkAccessManager(this);
    connect(_netManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(networkRequestFinished(QNetworkReply*)));
}

void GoogleAudioTranscriber::transcribeAudioFile(QString filename)
{
    QString url = QString("https://www.google.com/speech-api/v1/recognize?xjerr=1&client=chromium&lang=en-US");
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setRawHeader("Content-Type","audio/x-flac; rate=44100");

    QFile file(filename);
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    file.close();

    qDebug() << Q_FUNC_INFO << "will HTTP post with" << data.length() << "bytes:" << url << "from" << filename;
    _netManager->post(request,data);


}

void GoogleAudioTranscriber::networkRequestFinished(QNetworkReply *reply)
{


    // Validate
    if (reply->error() != QNetworkReply::NoError) {
        qDebug() << "could not get response:" << reply->errorString();
        return;
    }

    // Read data
    QByteArray data = reply->readAll();
    qDebug() << "response:" << QString(data);

    // Get json result
    bool ok;
    QVariantMap result = QtJson::parse(QString(data), ok).toMap();
    if(!ok) {
        qDebug() << "could not decode response:" << QString(data);
        return;
    }
    QVariantList hypotheses = result["hypotheses"].toList();

    if(hypotheses.length() > 0) {
        QVariantMap hypothesis = hypotheses.at(0).toMap();
        QString utterance = hypothesis["utterance"].toString();
        double confidence = hypothesis["confidence"].toDouble();
        qDebug() << "hypothesis" << utterance << "@" << confidence;
        if(confidence > 0.50) emit transcribeCompleted(utterance);
    }

}


