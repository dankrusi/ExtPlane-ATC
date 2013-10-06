#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QTimer>

#include "googleaudiotranscriber.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    _recorder = new AudioRecorder(this);
    _transcriber = new GoogleAudioTranscriber(this);
    _player = new AudioPlayer(this);

    connect(_transcriber,SIGNAL(transcribeCompleted(QString)),this,SLOT(transcribeCompleted(QString)));
}

Widget::~Widget() {
    delete ui;
}

void Widget::on_pushButton_pressed() {
    _recorder->beginRecording();
}

void Widget::on_pushButton_released() {

    //_player->speak("N 5 4 3 2 request for take off. Clear to take off, head to runway 34.");

    QTimer::singleShot(800,this,SLOT(on_pushButton_released_delayed()));
}

void Widget::on_pushButton_released_delayed() {
    _recorder->stopRecording();
    _transcriber->transcribeAudioFile(_recorder->outputFile());
}

void Widget::transcribeCompleted(QString result) {
    ui->label->setText(result);
    _player->speak(result);


}
