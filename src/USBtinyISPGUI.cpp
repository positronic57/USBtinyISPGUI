/*
* Copyright (c) 2013 Goce Boshkovski
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License.
*
*/

#include <QDesktopWidget>
#include <QCoreApplication>

#include "USBtinyISPGUI.h"
#include "ui_USBtinyISPGUI.h"
#include "confighandler.h"


USBtinyISPGUI::USBtinyISPGUI(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::USBtinyISPGUIClass)
{

    ui->setupUi(this);
    actionButtonGroup = new QButtonGroup(this);
    fileDialog = new QFileDialog(this);
    deviceInfo = new deviceinfodialog(this);
    statusLabel=new QLabel("Ready",this);
    statusLabel->setFixedSize(50,16);
    ui->actionConfigure->setIcon(QIcon(":/icons/configure.png"));
    ui->actionConvertor->setIcon(QIcon(":/icons/refresh.png"));
    ui->actionDevice_Info->setIcon(QIcon(":/icons/information.png"));
    ui->actionExit->setIcon(QIcon(":/icons/exit.png"));
    ui->startPushButton->setEnabled(false);

    actionButtonGroup->addButton(ui->programRadioButton, 0);
    actionButtonGroup->addButton(ui->eraseRadioButton, 1);

    hFormGroupBox = new QGroupBox;
    lFormGroupBox = new QGroupBox;
    hFormLayout = new QFormLayout;
    lFormLayout = new QFormLayout;

    hfuseBits = new BitsWidget(8, BitsWidget::BIT_BOXES_LAYOUT::Vertical);
    lfuseBits = new BitsWidget(8, BitsWidget::BIT_BOXES_LAYOUT::Vertical);
    lowByteLineEdit = new QLineEdit;
    highByteLineEdit = new QLineEdit;
    lowByteLineEdit->setInputMask("HH");
    highByteLineEdit->setInputMask("HH");

    hFormLayout->addRow(hfuseBits);
    hFormLayout->addRow("Value 0x", highByteLineEdit);
    lFormLayout->addRow(lfuseBits);
    lFormLayout->addRow("Value 0x", lowByteLineEdit);

    hFormGroupBox->setLayout(hFormLayout);
    lFormGroupBox->setLayout(lFormLayout);
    ui->fusesHighByteGroupBox->setLayout(hFormLayout);
    ui->fusesLowByteGroupBox->setLayout(lFormLayout);

    statusProgressBar = new QProgressBar;
    statusProgressBar->setValue(0);
    statusProgressBar->setTextVisible(false);
    fileSizeLabel = new QLabel("File size:");
    showFileSizeLabel = new QLabel("");
    fileModificationTimeLabel = new QLabel("Last Change:");
    showFileModificatonTimeLabel = new QLabel("");

    ui->programRadioButton->setChecked(true);
    ui->tabWidget->setCurrentIndex(0);

    ui->statusBar->insertPermanentWidget(0, fileSizeLabel, 1);
    ui->statusBar->insertPermanentWidget(1, showFileSizeLabel, 1);
    ui->statusBar->insertPermanentWidget(2, fileModificationTimeLabel, 1);
    ui->statusBar->insertPermanentWidget(3, showFileModificatonTimeLabel, 1);
    ui->statusBar->insertPermanentWidget(4, statusLabel, 1);
    ui->statusBar->insertPermanentWidget(5, statusProgressBar, 1);

    timeLine = new QTimeLine(500, this);
    timeLine->setFrameRange(0, 100);

    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setNameFilter("All HEX files (*.HEX *.hex)");;
    fileDialog->setDirectory("/home/");

    connect(timeLine, SIGNAL(frameChanged(int)), statusProgressBar, SLOT(setValue(int)));
    connect(ui->HEXFileLineEdit, SIGNAL(textEdited(QString)), this, SLOT(updateStatusBar(QString)));

    // Radio buttons
    connect(ui->eraseRadioButton, &QRadioButton::clicked, this, &USBtinyISPGUI::eraseDeviceSelected);
    connect(ui->programRadioButton, &QRadioButton::clicked, this, &USBtinyISPGUI::programDeviceSelected);

    // Dialogs
    connect(fileDialog, &QFileDialog::filesSelected, this, &USBtinyISPGUI::fileSelected);

    // Fuse line edits
    connect(lowByteLineEdit, &QLineEdit::textEdited, //this, &USBtinyISPGUI::LFUSEChanged);
            lfuseBits, static_cast<void (BitsWidget:: *)(QString)>(&BitsWidget::setValue));
    connect(highByteLineEdit, &QLineEdit::textEdited, //this, &USBtinyISPGUI::HFUSEChanged);
            hfuseBits, static_cast<void (BitsWidget:: *)(QString)>(&BitsWidget::setValue));

    connect(hfuseBits, &BitsWidget::valueChanged, this, &USBtinyISPGUI::hFuseBitsChanged);
    connect(lfuseBits, &BitsWidget::valueChanged, this, &USBtinyISPGUI::lFuseBitsChanged);

    // Push buttons
    connect(ui->readPushButton, &QPushButton::clicked, this, &USBtinyISPGUI::readPushButtonPressed);
    connect(ui->writePushButton, &QPushButton::clicked, this, &USBtinyISPGUI::writePushButtonPressed);
    connect(ui->openPushButton, &QPushButton::clicked, fileDialog, &QFileDialog::exec);
    connect(ui->startPushButton, &QPushButton::clicked,this, &USBtinyISPGUI::startButtonPressed);
    connect(ui->defaultPushButton, &QPushButton::clicked, this, &USBtinyISPGUI::getDefaultValuesForFuseBits);

    // Execute avrdude command
    connect(this, &USBtinyISPGUI::signalStartAvrdude, this, &USBtinyISPGUI::slotStartAvrdude);

    // Menu actions
    connect(ui->actionAbout_Qt,&QAction::triggered, qApp, &QApplication::aboutQt);
    connect(ui->actionAbout, &QAction::triggered, this, &USBtinyISPGUI::about);
    connect(ui->actionConfigure, &QAction::triggered,this, &USBtinyISPGUI::openConfigureDialog);
    connect(ui->actionExit, &QAction::triggered, this, &USBtinyISPGUI::close);
    connect(ui->actionDevice_Info, &QAction::triggered, this, &USBtinyISPGUI::getDeviceInfo);

    // AVR8 device selected from ComboBox
    connect(ui->microcontrollerComboBox,
            static_cast<void (QComboBox:: *)(int)>(&QComboBox::currentIndexChanged),
            this, &USBtinyISPGUI::AVR8_device_selected);

    // Prepare for executing shell commands
    shell_cmd_executor = new ShellCMDExecutor();
    shell_cmd_executor->moveToThread(&shell_cmd_executor_thread);
    shell_cmd_executor->setProcessChannelMode(QProcess::SeparateChannels);

    // Start the command when the thread has started
    connect(&shell_cmd_executor_thread, &QThread::started,
            shell_cmd_executor, &ShellCMDExecutor::slotStartShellCMDExecution);
    // Catch the error that occurred while executing the command
    connect(shell_cmd_executor, &ShellCMDExecutor::errorOccurred, this, &USBtinyISPGUI::processError);
    // Command is done, get the exit status
    connect(shell_cmd_executor, static_cast<void (QProcess::*)(int)>(&ShellCMDExecutor::finished),
            this, &USBtinyISPGUI::slotShellCmdExecutionFinished);

    setWindowTitle(QString("USBtinyISP GUI v%1").arg(application_version_string));
}

USBtinyISPGUI::~USBtinyISPGUI()
{
    delete ui;
    delete statusLabel;
    delete actionButtonGroup;
    delete configureProgrammer;
    delete timeLine;
    delete statusProgressBar;
    delete fileSizeLabel;
    delete fileModificationTimeLabel;
    delete fileDialog;
    delete deviceInfo;
    delete showFileSizeLabel;
    delete showFileModificatonTimeLabel;
    delete hfuseBits;
    delete lfuseBits;
    delete highByteLineEdit;
    delete lowByteLineEdit;
    delete shell_cmd_executor;
    delete hFormLayout;
    delete lFormLayout;
    delete hFormGroupBox;
    delete lFormGroupBox;

}

int USBtinyISPGUI::init()
{
    xml_configuration.load_config(qApp->applicationDirPath() + "/config/USBtinyISPGUIConfigFile.xml");
    if (xml_configuration.get_general_config(avrdude_config, burner_config) ||
        xml_configuration.get_mcus_definitions(AVR8_devices)) {
        QMessageBox error_msg(
                    QMessageBox::Critical,
                    "Critical Error",
                    QString("Reading of configuration file failed with error #%1:\t\n%2")
                    .arg(static_cast<int>(xml_configuration.last_error.code))
                    .arg(xml_configuration.last_error.message),
                    QMessageBox::Ok,
                    QDesktopWidget().screen(),
                    Qt::Dialog
                    );
        error_msg.exec();
        return static_cast<int>(xml_configuration.last_error.code);
    }

    fillMCUComboBox();
    AVR8_device_selected(0);

    configureProgrammer = new configureDialog(avrdude_config, burner_config, this);
    connect(configureProgrammer, &configureDialog::signalNewConfigValuesAvailable, this, &USBtinyISPGUI::newConfigAvailable);

    return 0;
}

void USBtinyISPGUI::fileSelected(QStringList selectedFiles)
{
    HEXFile.setFile(selectedFiles.first());

    ui->HEXFileLineEdit->setText(selectedFiles.first());
    fileDialog->setDirectory(HEXFile.absolutePath());
    showFileSizeLabel->setText(QString::number(HEXFile.size())+"B");
    showFileModificatonTimeLabel->setText(HEXFile.lastModified().toString("hh:mm dd.MM.yyyy "));
    ui->startPushButton->setEnabled(true);
}

void USBtinyISPGUI::startButtonPressed()
{   
    switch (actionButtonGroup->checkedId())
    {
        case 0:
            {
                processID=USBtinyISPGUI::programDevice;
                emit signalStartAvrdude(USBtinyISPGUI::programDevice);
            }
            break;
        case 1:
            {
                processID=USBtinyISPGUI::eraseDevice;
                emit signalStartAvrdude(USBtinyISPGUI::eraseDevice);
            }
    }
}

void USBtinyISPGUI::readPushButtonPressed()
{
    processID=USBtinyISPGUI::readLFUSEBYTES;
    emit signalStartAvrdude(USBtinyISPGUI::readLFUSEBYTES);
}

void USBtinyISPGUI::writePushButtonPressed()
{
    processID=USBtinyISPGUI::writeFUSEBYTES;
    QMessageBox msgBox;
    msgBox.setText("This will modiffy the AVR microcontroller fuse bits.\nIncorrect values of fuse bits can harm the AVR microcontroller!");
    msgBox.setInformativeText("Do you really want to change the fuse bits?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    msgBox.setIcon(QMessageBox::Warning);
    int ret = msgBox.exec();
    switch(ret)
    {
        case QMessageBox::Ok:
            emit signalStartAvrdude(USBtinyISPGUI::writeFUSEBYTES);
            break;
        default:
            return;

     }
}

void USBtinyISPGUI::slotStartAvrdude(int actionID)
{
    if (!findUSBTinyProgrammer())
    {
        QMessageBox::critical(this,"Error","USBTiny programmer is not present!\nPlease connect the USBTiny and then try again.");
        statusLabel->setText("Ready");
        return;
    }

    shell_cmd_executor->cmd_clear_arguments();
    shell_cmd_executor->cmd(avrdude_config.binary);
    shell_cmd_executor->add_argument("-C");
    shell_cmd_executor->add_argument(avrdude_config.config_file);
    shell_cmd_executor->add_argument("-c");
    shell_cmd_executor->add_argument(burner_config.burner);
    shell_cmd_executor->add_argument("-p");
    shell_cmd_executor->add_argument(AVR8_devices[ui->microcontrollerComboBox->currentIndex()].model);
    shell_cmd_executor->add_argument("-q");

    switch (actionID)
    {
        case USBtinyISPGUI::programDevice:
            if (!burner_config.errase_flash_before_burn) {
                // Disable auto erase before burn
                shell_cmd_executor->add_argument("-D");
            }
            if (!burner_config.verify_after_burn) {
                // Disable automatic verify check after burn
                shell_cmd_executor->add_argument("-V");
            }

            shell_cmd_executor->add_argument("-U");
            shell_cmd_executor->add_argument(
                        QString(cmdLineOptions.at(USBtinyISPGUI::programDevice))
                                .arg(ui->memoryComboBox->currentText().toLower(), ui->HEXFileLineEdit->text())
                        );
            statusLabel->setText("Burning");
            break;
        case USBtinyISPGUI::eraseDevice:
            shell_cmd_executor->add_argument(cmdLineOptions.at(USBtinyISPGUI::eraseDevice));
            statusLabel->setText("Erasing");
            break;
        case USBtinyISPGUI::writeFUSEBYTES:
            shell_cmd_executor->add_argument("-U");
            shell_cmd_executor->add_argument(
                        QString(cmdLineOptions.at(USBtinyISPGUI::writeFUSEBYTES))
                        .arg("lfuse", "0x" + lowByteLineEdit->text())
                        );
            shell_cmd_executor->add_argument("-U");
            shell_cmd_executor->add_argument(
                        QString(cmdLineOptions.at(USBtinyISPGUI::writeFUSEBYTES))
                        .arg("hfuse", "0x" + highByteLineEdit->text())
                        );
            statusLabel->setText("Writing");
            break;
        case USBtinyISPGUI::readLFUSEBYTES:
        case USBtinyISPGUI::readHFUSEBYTES:
            shell_cmd_executor->add_argument("-U");
            shell_cmd_executor->add_argument(cmdLineOptions.at(USBtinyISPGUI::readLFUSEBYTES));
            shell_cmd_executor->add_argument("-U");
            shell_cmd_executor->add_argument(cmdLineOptions.at(USBtinyISPGUI::readHFUSEBYTES));
            statusLabel->setText("Reading");
            break;
        case USBtinyISPGUI::getDeviceInfoData:
             shell_cmd_executor->add_argument("-v");
             statusLabel->setText("Reading");
            break;
    }

    connect(timeLine, &QTimeLine::finished, timeLine, &QTimeLine::start);
    timeLine->start();

    shell_cmd_executor_thread.start();
}

void USBtinyISPGUI::updateStatusBar(QString fileName)
{

    HEXFile.setFile(fileName);

    if (HEXFile.exists() && !HEXFile.isDir())
    {
        showFileSizeLabel->setText(QString::number(HEXFile.size())+"B");
        showFileModificatonTimeLabel->setText(HEXFile.lastModified().toString("hh:mm dd.MM.yyyy "));
    }
    else
    {
        ui->startPushButton->setEnabled(false);
    }

}

void USBtinyISPGUI::processError(QProcess::ProcessError error)
{
    disconnect(timeLine, &QTimeLine::finished, timeLine, &QTimeLine::start);
    timeLine->stop();
    timeLine->setCurrentTime(0);
    statusLabel->setText("Error");

    switch (error)
    {
        case QProcess::FailedToStart:
            QMessageBox::critical(this, "Error","Faild to start AVRDUDE!");
            break;
        case QProcess::UnknownError:
            QMessageBox::critical(this,"Error","Unkown error during execution!");
            break;
        case QProcess::Crashed:
            QMessageBox::critical(this, "Error",QString(shell_cmd_executor->readAllStandardError()).remove("avrdude:"));
            break;
        case QProcess::Timedout:
            break;
        case QProcess::ReadError:
            break;
        case QProcess::WriteError:
            break;
    }
    statusProgressBar->setValue(0);
    statusLabel->setText("Ready");
}


bool USBtinyISPGUI::findUSBTinyProgrammer(void)
{
    struct usb_bus *thisBus;
    struct usb_device *dev;

    usb_init();
    usb_find_busses();
    usb_find_devices();

    for (thisBus = usb_get_busses(); thisBus; thisBus = thisBus->next)
       for (dev = thisBus->devices; dev; dev = dev->next)
           if (dev->descriptor.idVendor==USBTINY_VENDOR_ID && dev->descriptor.idProduct==USBTINY_PRODUCT_ID)
               return true;
    return false;
}

void USBtinyISPGUI::programDeviceSelected()
{
    //ui->selectFileGroupBox->setEnabled(true);
    ui->HEXFileLineEdit->setEnabled(true);
    ui->openPushButton->setEnabled(true);
    ui->memoryComboBox->setEnabled(true);
    if (HEXFile.exists())
        ui->startPushButton->setEnabled(true);
    else
        ui->startPushButton->setDisabled(true);
    statusProgressBar->setValue(0);
}

void USBtinyISPGUI::eraseDeviceSelected()
{
    ui->HEXFileLineEdit->setEnabled(false);
    ui->openPushButton->setEnabled(false);
    ui->memoryComboBox->setEnabled(false);
    ui->startPushButton->setEnabled(true);
    statusProgressBar->setValue(0);
}

void USBtinyISPGUI::openConfigureDialog()
{
    configureProgrammer->show();
}

void USBtinyISPGUI::newConfigAvailable(const ConfigHandler::AvrdudeConfig new_avrdude_cfg, const ConfigHandler::BurnerConfig new_burner_cfg)
{
    avrdude_config = new_avrdude_cfg;
    burner_config = new_burner_cfg;
    xml_configuration.write_general_config(avrdude_config, burner_config);
}

void USBtinyISPGUI::getDeviceInfo()
{
    processID=USBtinyISPGUI::getDeviceInfoData;
    emit signalStartAvrdude(USBtinyISPGUI::getDeviceInfoData);
}

void USBtinyISPGUI::fillMCUComboBox(void)
{
    if (AVR8_devices.empty()) {
        return;
    }

    for(int avr_device = 0; avr_device < AVR8_devices.count(); avr_device++)
    {
        ui->microcontrollerComboBox->addItem(AVR8_devices.at(avr_device).model);
    }
}

void USBtinyISPGUI::getDefaultValuesForFuseBits()
{
    int avr8_device = ui->microcontrollerComboBox->currentIndex();

    QString hex_out = QString("%1").arg(AVR8_devices[avr8_device].hfuses.value.to_ulong(), 2, 16, QLatin1Char('0'));
    highByteLineEdit->setText(hex_out.toUpper());
    hfuseBits->setValue(AVR8_devices[avr8_device].hfuses.value.to_ulong());

    hex_out = QString("%1").arg(AVR8_devices[avr8_device].lfuses.value.to_ulong(), 2, 16, QLatin1Char('0'));
    lowByteLineEdit->setText(hex_out.toUpper());
    lfuseBits->setValue(AVR8_devices[avr8_device].lfuses.value.to_ulong());
}

void USBtinyISPGUI::hFuseBitsChanged()
{
    highByteLineEdit->setText(hfuseBits->toHexQtString());
}

void USBtinyISPGUI::lFuseBitsChanged()
{
    lowByteLineEdit->setText(lfuseBits->toHexQtString());
}

void USBtinyISPGUI::closeEvent(QCloseEvent *event)
{
    event->accept();
}


void USBtinyISPGUI::about() {
QMessageBox::about(this, tr("About USBtinyISP GUI"),
            tr(
               "<h2>USBtinyISP GUI 1.0</h2>"
               "<p>"
               "<p>USBtiny GUI is a small GUI frontend application for "
               "<a href=\"https://github.com/avrdudes/avrdude/\">avrdude</a> (version 5.5 or newer) "
               "and <a href=\"https://learn.adafruit.com/usbtinyisp/overview\">USBtinyISP</a> programmer."
               "<p>XML support done with <a href=\"https://pugixml.org/\">pugixml</a> library."
               "<p>Legacy version 0.1 of <a href=\"https://libusb.info/\">libusb</a> used for detection of USBtinyISP programmer."
               "<p>Author: Goce Boshkovski"
               "<p>License: GNU General Public License Version 2"
               "<p>Version: %1"
               "<p>The program is provided AS IS with NO WARRANTY OF ANY KIND."
               ).arg(application_version_string)
            );
}

void USBtinyISPGUI::AVR8_device_selected(int index)
{
    if (AVR8_devices.empty()) {
        return;
    }

    // Add/remove EEPROM from burn list
    ui->memoryComboBox->clear();
    ui->memoryComboBox->addItem("Flash");
    if (AVR8_devices[index].has_eeprom) {
        ui->memoryComboBox->addItem("EEPROM");
    }

    QStringList hfuse_bits_names;
    QStringList lfuse_bits_names;
    // Set the names of the check box objects for each fuse bit
    for(int bit = 0; bit < 8; bit++)
    {
        lfuse_bits_names.append(AVR8_devices[index].lfuses.fuse_bits[bit]);
        hfuse_bits_names.append(AVR8_devices[index].hfuses.fuse_bits[bit]);
    }
    lfuseBits->setNames(lfuse_bits_names);
    hfuseBits->setNames(hfuse_bits_names);

    getDefaultValuesForFuseBits();
}


void USBtinyISPGUI::slotShellCmdExecutionFinished(int shell_cmd_exit_code)
{
    shell_cmd_executor_thread.quit();
    shell_cmd_executor_thread.wait();

    disconnect(timeLine, &QTimeLine::finished, timeLine, &QTimeLine::start);
    timeLine->stop();

    QString processOutput;
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Critical);

    if (shell_cmd_exit_code)
    {
        // Command exit code different than 0, error
        msgBox.setWindowTitle("Error");
        shell_cmd_executor->setReadChannel(QProcess::StandardError);
        statusLabel->setText("Failed");
        processOutput = QString(shell_cmd_executor->readAllStandardError()).simplified();
        msgBox.setDetailedText(processOutput);
        if(processOutput.contains("initialization failed")) {
            msgBox.setDetailedText("Failed to initialize the target device.");
        }
        if(processOutput.contains("Expected signature")) {
            msgBox.setDetailedText(
                        QString("The target device is not %1. Please select the right device.")
                        .arg(ui->microcontrollerComboBox->currentText())
                        );
        }
        switch(processID)
        {
            case USBtinyISPGUI::programDevice:
                msgBox.setText("Burrning process failed.");
            break;
            case USBtinyISPGUI::eraseDevice:
                msgBox.setText("Failed to erase the device.");
            break;
            case USBtinyISPGUI::writeFUSEBYTES:
                msgBox.setText("Failed to write Fuse Bytes.");
            break;
            case USBtinyISPGUI::readLFUSEBYTES:
            case USBtinyISPGUI::readHFUSEBYTES:
                msgBox.setText("Failed to read Fuse Bytes.");
            break;
            case USBtinyISPGUI::getDeviceInfoData:
                msgBox.setText("Failed to reatrive device info data.");
        }
        msgBox.exec();
    }
    else
    {
        statusProgressBar->setValue(100);
        msgBox.setWindowTitle("Info");
        msgBox.setIcon(QMessageBox::Information);
        switch(processID)
        {
            case USBtinyISPGUI::readLFUSEBYTES:
            case USBtinyISPGUI::readHFUSEBYTES:
            {
                QStringList list;
                shell_cmd_executor->setReadChannel(QProcess::StandardOutput);
                processOutput = shell_cmd_executor->readAllStandardOutput();
                processOutput = processOutput.remove("0x",Qt::CaseInsensitive);
                list = processOutput.split(QRegExp("\\s+"));
                highByteLineEdit->setText(list.at(1).toUpper());
                hfuseBits->setValue(list.at(1));
                lowByteLineEdit->setText(list.at(0).toUpper());
                lfuseBits->setValue(list.at(0));
            }
            break;
            case USBtinyISPGUI::getDeviceInfoData:
            {
                deviceInfo->setDeviceInformation(shell_cmd_executor->readAllStandardError());
                deviceInfo->show();
            }
            break;
            case USBtinyISPGUI::eraseDevice:
            {
                msgBox.setText("Erase process fininished successfuly.");
                msgBox.exec();
            }
            break;
            case USBtinyISPGUI::programDevice:
            {
                msgBox.setText("Burn process finished succsessfuly.");
                msgBox.exec();
            }
            break;
            case USBtinyISPGUI::writeFUSEBYTES:
            {
                msgBox.setText("Fuse Bytes are changed succsessfuly.");
                msgBox.exec();
            }
        }
    }
    statusProgressBar->setValue(0);
    timeLine->setCurrentTime(0);
    statusLabel->setText("Ready");
}

