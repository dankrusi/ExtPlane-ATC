#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent = 0);
    
signals:
    
public slots:
    void speak(QString text);
    void speak(QString text, int profile);

private:
    int _maxProfiles;
    
};

#endif // AUDIOPLAYER_H
