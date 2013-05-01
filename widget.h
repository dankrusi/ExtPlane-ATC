#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "audiorecorder.h"
#include "audiotranscriber.h"
#include "audioplayer.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    
private slots:
    void on_pushButton_pressed();
    void on_pushButton_released();
    void on_pushButton_released_delayed();

public slots:
    void transcribeCompleted(QString result);

private:
    Ui::Widget *ui;
    AudioRecorder *_recorder;
    AudioTranscriber *_transcriber;
    AudioPlayer *_player;
};

#endif // WIDGET_H
