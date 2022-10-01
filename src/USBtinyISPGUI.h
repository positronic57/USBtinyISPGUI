/*
* Copyright (c) 2013 Goce Boshkovski
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License.
*
*/

#ifndef USBtinyISPGUI_H
#define USBtinyISPGUI_H

#include <QMainWindow>
#include <QFileDialog>
#include <QProcess>
#include <QMessageBox>
#include <QFileInfo>
#include <QDateTime>
#include <qbuttongroup.h>
#include <QTimer>
#include <qdatetime.h>
#include <QTimeLine>
#include <qprogressbar.h>
#include <qevent.h>
#include <QLineEdit>
#include <QThread>
#include <QFormLayout>

#include "configuredialog.h"
#include "deviceinfodialog.h"
#include "confighandler.h"
#include "shellcmdexecutor.h"
#include "bitswidget.h"

extern "C"
{
    #include "usb.h"
}

#define USBTINY_VENDOR_ID 0x1781
#define USBTINY_PRODUCT_ID 0x0C9F

namespace Ui
{
    class USBtinyISPGUIClass;
}

class USBtinyISPGUI : public QMainWindow
{
    Q_OBJECT

public:
    enum Actions {
        programDevice = 0,
        eraseDevice,
        readLFUSEBYTES,
        readHFUSEBYTES,
        writeFUSEBYTES,
        getDeviceInfoData
    };
    USBtinyISPGUI(QWidget *parent = 0);
    ~USBtinyISPGUI();

    int init();

private:
    Ui::USBtinyISPGUIClass *ui = nullptr;
    QFileInfo HEXFile;
    QVector<ConfigHandler::MCU> AVR8_devices;
    ConfigHandler xml_configuration;
    ConfigHandler::AvrdudeConfig avrdude_config;
    ConfigHandler::BurnerConfig burner_config;
    QThread shell_cmd_executor_thread;
    configureDialog *configureProgrammer = nullptr;
    QButtonGroup *actionButtonGroup = nullptr;;
    QFileDialog *fileDialog = nullptr;;
    deviceinfodialog *deviceInfo = nullptr;;
    QTimeLine *timeLine = nullptr;
    ShellCMDExecutor *shell_cmd_executor = nullptr;
    QProgressBar *statusProgressBar = nullptr;;
    QLabel *statusLabel = nullptr;;
    QLabel *fileSizeLabel = nullptr;;
    QLabel *showFileSizeLabel = nullptr;;
    QLabel *fileModificationTimeLabel = nullptr;;
    QLabel *showFileModificatonTimeLabel = nullptr;
    QLineEdit *lowByteLineEdit = nullptr;
    QLineEdit *highByteLineEdit = nullptr;
    QFormLayout *lFormLayout = nullptr;
    QFormLayout *hFormLayout = nullptr;
    QGroupBox *hFormGroupBox = nullptr;
    QGroupBox *lFormGroupBox = nullptr;
    BitsWidget *hfuseBits = nullptr;
    BitsWidget *lfuseBits = nullptr;

    const QStringList cmdLineOptions = {
        "%1:w:%2",
        "-e",
        "lfuse:r:-:h",
        "hfuse:r:-:h",
        "%1:w:%2m"
    };

    const QString application_version_string = QString("%1.%2.%3")
            .arg(APPLICATION_MAJOR_VERSION)
            .arg(APPLICATION_MINOR_VERSION)
            .arg(APPLICATION_RELEASE_VERSION);

public:
    USBtinyISPGUI::Actions processID;
    static bool findUSBTinyProgrammer(void);

private slots:
    void fillMCUComboBox(void);
    void fileSelected(QStringList);
    void startButtonPressed();
    void updateStatusBar(QString);
    void processError(QProcess::ProcessError);
    void programDeviceSelected();
    void eraseDeviceSelected();
    void openConfigureDialog();
    void newConfigAvailable(const ConfigHandler::AvrdudeConfig new_avrdude_cfg, const ConfigHandler::BurnerConfig new_burner_cfg);
    void getDeviceInfo();
    void getDefaultValuesForFuseBits();
    void hFuseBitsChanged();
    void lFuseBitsChanged();
    void slotStartAvrdude(int);
    void readPushButtonPressed();
    void writePushButtonPressed();
    void about();
    void AVR8_device_selected(int);
    void slotShellCmdExecutionFinished(int cmd_exit_code);

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void signalStartAvrdude(int);
    void signalExitApp(int);
};

#endif // USBtinyISPGUI_H
