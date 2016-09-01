#include "widget.h"
#include "ui_widget.h"

#include <QDebug>
#include <QTimer>

#include "googleaudiotranscriber.h"

#include "extplaneconnection.h"
#include "extplaneclient.h"
#include "simulatedextplaneconnection.h"
#include "dialogs/settingsdialog.h"
#include "util/console.h"

#define DATAREF_LATEST_ATC "extplane/atc/124thatc/latest"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    // Setup UI
    ui->setupUi(this);
    this->setWindowTitle("ExtPlane-ATC");

    // Init
    appSettings = NULL;
    settingsDialog = NULL;

    // Load settings
    appSettings = new Settings("com.dankrusi", "extplane-atc", this);

    // Create connection and item factory
    connection = appSettings->valueFromSettingsOrCommandLine("simulate", false).toBool() ? new SimulatedExtPlaneConnection() : new ExtPlaneConnection();

    // Create our panel window client
    client = new ExtPlaneClient(this,"PanelWindow",connection);
    connection->registerClient(client);
    connect(client, SIGNAL(refChanged(QString,QString)), this, SLOT(clientDataRefChanged(QString,QString)));
    connect(client, SIGNAL(refChanged(QString,double)), this, SLOT(clientDataRefChanged(QString,double)));

    // Settings dialog
    settingsDialog = new SettingsDialog(this, appSettings);
    connect(settingsDialog, SIGNAL(setServerAddress(QString)), this, SLOT(setServerAddress(QString)));
    settingsDialog->setModal(false);
    settingsDialog->hide();

    // Status message
    connect(connection, SIGNAL(connectionMessage(QString)), this, SLOT(connectionMessage(QString)));

    // Setup APIs
    _recorder = new AudioRecorder(this, appSettings);
    _transcriber = new GoogleAudioTranscriber(this, appSettings);
    _player = new AudioPlayer(this, appSettings);
    connect(_transcriber,SIGNAL(transcribeCompleted(QString)),this,SLOT(transcribeCompleted(QString)));

    // Start connection to ExtPlane
    this->settingsDialog->loadSettings(); // This will trigger signals to start connection to ExtPlane

    // Subscribe
    client->subscribeDataRef(DATAREF_LATEST_ATC);
}

Widget::~Widget() {
    delete ui;
}

bool Widget::hiddenGUI()
{
    return appSettings->valueFromSettingsOrCommandLine("hidden-gui", false).toBool();
}




void Widget::connectionMessage(QString txt) {
    INFO << txt;
    ui->label->setText(txt);
    ui->label->setToolTip(txt);
}

void Widget::setServerAddress(QString host) {
    // Extract address and port
    unsigned int port = 0;
    QStringList hostport = host.split(":");
    if(hostport.length()==2) port = hostport.value(1).toUInt(NULL);
    if(port==0) port = 51000;
    INFO << "Connecting to" << hostport.value(0) << "on port" << port;

    // Disconnect and reconnect
    connection->disconnectFromHost();
    connection->connectTo(hostport.value(0), port);
}

void Widget::speak(QString txt) {
    _player->speak(txt);
    connectionMessage(txt);
}





// -------------------------------------------------------------------------------------
// -- Client Data Refs
// -------------------------------------------------------------------------------------

void Widget::clientDataRefChanged(QString name, QString val) {
    if(name == DATAREF_LATEST_ATC) {
        DEBUG << "DATAREF_LATEST_ATC:" << val;
        speak(val);
    }
}

void Widget::clientDataRefChanged(QString name, double val) {

}






// -------------------------------------------------------------------------------------
// -- UI Actions
// -------------------------------------------------------------------------------------


void Widget::on_buttonSettings_clicked() {
    settingsDialog->show();
}

void Widget::on_buttonTestTTS_clicked() {
    speak("N 5 4 3 2 request for take off. Clear to take off, head to runway 34.");
}

void Widget::on_buttonTestPTT_pressed() {
    _recorder->beginRecording();
}

void Widget::on_buttonTestPTT_released() {
    QTimer::singleShot(800,this,SLOT(on_pushButton_released_delayed()));
}

void Widget::on_buttonTestPTT_released_delayed() {
    _recorder->stopRecording();
    _transcriber->transcribeAudioFile(_recorder->outputFile());
}

void Widget::transcribeCompleted(QString result) {
    speak(result);
}
