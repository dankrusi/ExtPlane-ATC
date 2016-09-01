#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include "audiorecorder.h"
#include "audiotranscriber.h"
#include "audioplayer.h"

#include "settings.h"

class SettingsDialog;
class ExtPlaneConnection;
class ExtPlaneClient;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    bool hiddenGUI();

public slots:

    void connectionMessage(QString txt);
    void setServerAddress(QString host);
    void clientDataRefChanged(QString name, QString val);
    void clientDataRefChanged(QString name, double val);
    
private slots:
    void on_buttonSettings_clicked();
    void on_buttonTestTTS_clicked();
    void on_buttonTestPTT_pressed();
    void on_buttonTestPTT_released();
    void on_buttonTestPTT_released_delayed();

public slots:
    void transcribeCompleted(QString result);
    void speak(QString txt);

private:
    Ui::Widget *ui;
    SettingsDialog *settingsDialog;

    AudioRecorder *_recorder;
    AudioTranscriber *_transcriber;
    AudioPlayer *_player;

    ExtPlaneConnection *connection; // The master connection which all panel item clients will use
    ExtPlaneClient *client; // Client for performing universal action such as automatically chaning the panel when aircraft changes, dimming lights, et cetera

    Settings *appSettings; // Loaded on app start, contains general settings, passed on to settings dialog. Use valueFromSettingsOrCommandLine to extract settings from both the file and command line.

};

#endif // WIDGET_H
