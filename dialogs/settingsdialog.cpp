#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QDebug>
#include <QDialog>

SettingsDialog::SettingsDialog(QWidget *parent, Settings *appSettings) :
    QDialog(parent), ui(new Ui::SettingsDialog), appSettings(appSettings) {
    ui->setupUi(this);
    connect(ui->serverAddressEdit, SIGNAL(textChanged(QString)), this, SIGNAL(setServerAddress(QString)));
    connect(ui->updateIntervalComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateIntervalChanged()));
    connect(this, SIGNAL(finished(int)), this, SLOT(saveSettings()));
}

SettingsDialog::~SettingsDialog() {
    delete ui;
}

void SettingsDialog::changeEvent(QEvent *e) {
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void SettingsDialog::loadSettings() {

    // Server line edit
    ui->serverAddressEdit->setText(appSettings->valueFromSettingsOrCommandLine("serveraddress", "127.0.0.1:51000").toString());
    emit setServerAddress(ui->serverAddressEdit->text());

    // Update interval combobox
    ui->updateIntervalComboBox->setCurrentIndex(appSettings->valueFromSettingsOrCommandLine("updateinterval", 0).toInt());
    updateIntervalChanged();

}

void SettingsDialog::updateIntervalChanged() {
    bool ok;
    float newInterval = ui->updateIntervalComboBox->currentText().toFloat(&ok);
    if(!ok) {
        newInterval = 0;
    } else {
        newInterval = 1.f / newInterval; // Convert Hz to delay in s
    }

    emit setUpdateInterval(newInterval);
}

void SettingsDialog::saveSettings() {
    appSettings->setValue("serveraddress", ui->serverAddressEdit->text());
    appSettings->setValue("updateinterval", ui->updateIntervalComboBox->currentIndex());
    appSettings->sync();
}

