#include "audiotranscriber.h"

AudioTranscriber::AudioTranscriber(QObject *parent, Settings *appSettings) :
    QObject(parent)
{
    _appSettings = appSettings;
}
