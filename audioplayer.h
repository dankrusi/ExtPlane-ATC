#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>

#include "settings.h"

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent, Settings *appSettings);
    
signals:
    
public slots:
    void speak(QString text);
    void speak(QString text, int profile);

private:
    int _maxProfiles;
    Settings *_appSettings;
    
};

#endif // AUDIOPLAYER_H
