#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>

#include "../settings.h"

namespace Ui {
    class SettingsDialog;
}

/**
 * Main settings for the whole application
 */
class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent, Settings *appSettings);
    ~SettingsDialog();
public slots:
    void loadSettings();
    void saveSettings();
    void updateIntervalChanged();
protected:
    void changeEvent(QEvent *e);
signals:
    void setServerAddress(QString host);
    void setUpdateInterval(double newInterval);
private:
    Ui::SettingsDialog *ui;
    Settings *appSettings;
};

#endif // SETTINGSDIALOG_H
