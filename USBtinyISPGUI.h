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
#include <QDomDocument>
#include <QTextStream>
#include <qevent.h>
#include "configuredialog.h"
#include "deviceinfodialog.h"

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
    USBtinyISPGUI(QWidget *parent = 0);
    ~USBtinyISPGUI();
    configureDialog *configureProgrammer;

private:
    Ui::USBtinyISPGUIClass *ui;
    QButtonGroup *actionButtonGroup;
    QFileDialog *fileDialog;
    deviceinfodialog *deviceInfo;
    QProcess *process;
    QStringList microcontrollerList;
    QTimeLine *timeLine;
    QString AVRDUDEexecutable;
    QString AVRDUDEconffile;
    QString autoEraseArgument;
    QString verifyArgument;
    QString Command;
    QFileInfo HEXFile;
    QProgressBar *statusProgressBar;
    QLabel *statusLabel;
    QLabel *fileSizeLabel;
    QLabel *showFileSizeLabel;
    QLabel *fileModificationTimeLabel;
    QLabel *showFileModificatonTimeLabel;
    bool isConfigurationChanged;
    QFile xmlConfigFile;
    QDomDocument xmlDoc;
    QDomNodeList supportedAVRMicrocontrollers;
    QDomNode configNode;
    QList <QString> cmdLineOptions;
    QButtonGroup *hfuseButtonGroup;
    QButtonGroup *lfuseButtonGroup;
    QList <QString> newConfiguration;
    int hfuseByteValue;
    int lfuseByteValue;

public:
    enum Actions {programDevice,
                  eraseDevice,
                  readFUSEBYTES,
                  writeFUSEBYTES,
                  getDeviceInfoData
              };

    USBtinyISPGUI::Actions processID;
    void getProgrammerConfig(void);
    void getMicrocontrollerList(void);
    bool findAVRDUDE(void);
    static bool findUSBTinyProgrammer(void);
    static bool doesConfigFileExist(QString);

private slots:
    void fileSelected(QStringList);
    void startButtonPressed();
    void processFinished(int);
    void updateStatusBar(QString);
    void processError(QProcess::ProcessError);
    void programDeviceSelected();
    void eraseDeviceSelected();
    void openConfigureDialog();
    void AVRDUDESettingsChanged(QString,QString,bool,bool);
    void getDeviceInfo();
    void getAVRFuseBits(int index);
    void getDefaultValuesForFuseBits();
    void LFUSEChanged(QString);
    void HFUSEChanged(QString);
    void HFUSEButtonGroupChanged(int);
    void LFUSEButtonGroupChanged(int);
    void execCommand(int);
    void readPushButtonPressed();
    void writePushButtonPressed();
    void about();

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void setConfiguration(QString,QString,bool,bool);
    void startProcess(int);

};

#endif // USBtinyISPGUI_H
