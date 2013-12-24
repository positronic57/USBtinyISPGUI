/*
* Copyright (c) 2013 Goce Boshkovski
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License.
*
*/

#include "USBtinyISPGUI.h"
#include "ui_USBtinyISPGUI.h"

USBtinyISPGUI::USBtinyISPGUI(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::USBtinyISPGUIClass)
{

    ui->setupUi(this);
    configureProgrammer = new configureDialog(this);
    actionButtonGroup = new QButtonGroup(this);
    fileDialog = new QFileDialog(this);
    deviceInfo = new deviceinfodialog(this);
    process = new QProcess(this);
    statusLabel=new QLabel("Ready",this);
    statusLabel->setFixedSize(50,16);
    ui->actionConfigure->setIcon(QIcon(":/icons/configure.png"));
    ui->actionConvertor->setIcon(QIcon(":/icons/refresh.png"));
    ui->actionDevice_Info->setIcon(QIcon(":/icons/information.png"));
    ui->actionExit->setIcon(QIcon(":/icons/exit.png"));

    actionButtonGroup->addButton(ui->programRadioButton,0);
    actionButtonGroup->addButton(ui->erraseRadioButton,1);
    hfuseButtonGroup=new QButtonGroup(this);
    hfuseButtonGroup->setExclusive(false);
    hfuseButtonGroup->addButton(ui->checkBox_1,7);
    hfuseButtonGroup->addButton(ui->checkBox_2,6);
    hfuseButtonGroup->addButton(ui->checkBox_3,5);
    hfuseButtonGroup->addButton(ui->checkBox_4,4);
    hfuseButtonGroup->addButton(ui->checkBox_5,3);
    hfuseButtonGroup->addButton(ui->checkBox_6,2);
    hfuseButtonGroup->addButton(ui->checkBox_7,1);
    hfuseButtonGroup->addButton(ui->checkBox_8,0);
    lfuseButtonGroup=new QButtonGroup(this);
    lfuseButtonGroup->setExclusive(false);
    lfuseButtonGroup->addButton(ui->checkBox_9,7);
    lfuseButtonGroup->addButton(ui->checkBox_10,6);
    lfuseButtonGroup->addButton(ui->checkBox_11,5);
    lfuseButtonGroup->addButton(ui->checkBox_12,4);
    lfuseButtonGroup->addButton(ui->checkBox_13,3);
    lfuseButtonGroup->addButton(ui->checkBox_14,2);
    lfuseButtonGroup->addButton(ui->checkBox_15,1);
    lfuseButtonGroup->addButton(ui->checkBox_16,0);

    ui->programRadioButton->setChecked(true);
    ui->lowByteLineEdit->setInputMask("HH");
    ui->highByteLineEdit->setInputMask("HH");
    hfuseByteValue=0;
    lfuseByteValue=0;

    cmdLineOptions << " -U flash:w:" << " -U eeprom:w:" << " -e" << "  -U lfuse:r:-:h -U hfuse:r:-:h" << " -U lfuse:w:" << " -U hfuse:w:";

    process->setProcessChannelMode(QProcess::SeparateChannels);

    timeLine = new QTimeLine(500, this);
    timeLine->setFrameRange(0, 100);

    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setFileMode(QFileDialog::ExistingFile);
    fileDialog->setFilter(tr("HEX files (*.HEX *.hex)"));
    fileDialog->setViewMode(QFileDialog::Detail);
    fileDialog->setDirectory("/home/");

    ui->startPushButton->setEnabled(false);

    connect(this,SIGNAL(setConfiguration(QString,QString,bool,bool)),configureProgrammer,SLOT(setConfiguration(QString,QString,bool,bool)));
    xmlConfigFile.setFileName(qApp->applicationDirPath()+"/config/USBtinyISPGUIConfigFile.xml");
    if (!xmlConfigFile.open(QIODevice::ReadOnly))
    {
        QMessageBox::critical(this,"Error","Cannot Open Configuration File!");
        exit(1);
    }
    xmlDoc.setContent(&xmlConfigFile);
    xmlConfigFile.close();
    getProgrammerConfig();
    getMicrocontrollerList();
    isConfigurationChanged=false;
    getAVRFuseBits(0);

    AVRDUDEexecutable+=" -c usbtiny";
    AVRDUDEconffile=" -C "+AVRDUDEconffile;
    Command=AVRDUDEexecutable+AVRDUDEconffile+verifyArgument+autoEraseArgument;

    statusProgressBar=new QProgressBar(this);
    statusProgressBar->setFixedSize(80,16);
    statusProgressBar->setValue(0);
    statusProgressBar->setTextVisible(false);
    fileSizeLabel=new QLabel("File size:",this);
    fileSizeLabel->setFixedSize(55,16);
    showFileSizeLabel=new QLabel("",this);
    showFileSizeLabel->setFixedSize(60,16);
    fileModificationTimeLabel=new QLabel("Last Change:",this);
    fileModificationTimeLabel->setFixedSize(80,16);
    showFileModificatonTimeLabel=new QLabel("",this);
    showFileModificatonTimeLabel->setFixedSize(114,16);

    ui->statusBar->insertPermanentWidget(0,fileSizeLabel,0);
    ui->statusBar->insertPermanentWidget(1,showFileSizeLabel,0);
    ui->statusBar->insertPermanentWidget(2,fileModificationTimeLabel,0);
    ui->statusBar->insertPermanentWidget(3,showFileModificatonTimeLabel,0);
    ui->statusBar->insertPermanentWidget(4,statusLabel,0);
    ui->statusBar->insertPermanentWidget(5,statusProgressBar,0);

    connect(ui->openPushButton,SIGNAL(clicked()),fileDialog,SLOT(exec()));
    connect(timeLine, SIGNAL(frameChanged(int)), statusProgressBar, SLOT(setValue(int)));
    connect(fileDialog,SIGNAL(filesSelected(QStringList)),this,SLOT(fileSelected(QStringList)));
    connect(ui->startPushButton,SIGNAL(clicked()),this,SLOT(startButtonPressed()));
    connect(process,SIGNAL(finished(int)),this,SLOT(processFinished(int)));
    connect(process,SIGNAL(error(QProcess::ProcessError)),this,SLOT(processError(QProcess::ProcessError)));
    connect(ui->HEXFileLineEdit,SIGNAL(textEdited(QString)),this,SLOT(updateStatusBar(QString)));
    connect(ui->erraseRadioButton,SIGNAL(clicked()),this,SLOT(eraseDeviceSelected()));
    connect(ui->programRadioButton,SIGNAL(clicked()),this,SLOT(programDeviceSelected()));
    connect(ui->actionConfigure,SIGNAL(triggered()),this,SLOT(openConfigureDialog()));
    connect(ui->actionExit,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->actionDevice_Info,SIGNAL(triggered()),this,SLOT(getDeviceInfo()));
    connect(configureProgrammer,SIGNAL(parametersChanged(QString,QString,bool,bool)),this,SLOT(AVRDUDESettingsChanged(QString,QString,bool,bool)));
    connect(ui->microcontrollerComboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(getAVRFuseBits(int)));
    connect(ui->defaultPushButton,SIGNAL(clicked()),this,SLOT(getDefaultValuesForFuseBits()));
    connect(ui->lowByteLineEdit,SIGNAL(textEdited(QString)),this,SLOT(LFUSEChanged(QString)));
    connect(ui->highByteLineEdit,SIGNAL(textEdited(QString)),this,SLOT(HFUSEChanged(QString)));
    connect(hfuseButtonGroup,SIGNAL(buttonClicked(int)),this,SLOT(HFUSEButtonGroupChanged(int)));
    connect(lfuseButtonGroup,SIGNAL(buttonClicked(int)),this,SLOT(LFUSEButtonGroupChanged(int)));
    connect(ui->readPushButton,SIGNAL(clicked()),this,SLOT(readPushButtonPressed()));
    connect(ui->writePushButton,SIGNAL(clicked()),this,SLOT(writePushButtonPressed()));
    connect(this,SIGNAL(startProcess(int)),this,SLOT(execCommand(int)));
    connect(ui->actionAbout_Qt,SIGNAL(triggered()),qApp,SLOT(aboutQt()));
    connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(about()));
}

USBtinyISPGUI::~USBtinyISPGUI()
{
    delete ui;
    delete statusLabel;
    delete process;
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
    delete lfuseButtonGroup;
    delete hfuseButtonGroup;
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

void USBtinyISPGUI::processFinished(int exitCode)
{

    disconnect(timeLine,SIGNAL(finished()),timeLine,SLOT(start()));
    timeLine->stop();

    QString processOutput;
    bool ok;
    QMessageBox msgBox;
    msgBox.setStandardButtons(QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setIcon(QMessageBox::Critical);

    if(exitCode)
    {
        msgBox.setWindowTitle("Error");
        process->setReadChannel(QProcess::StandardError);
        statusLabel->setText("Failed");
        processOutput=QString(process->readAllStandardError()).simplified();
        msgBox.setDetailedText(processOutput);
        if(processOutput.contains("initialization failed"))
            msgBox.setDetailedText("Failed to initialize the target device.");
        if(processOutput.contains("Expected signature"))
            msgBox.setDetailedText("Target device is not "+ui->microcontrollerComboBox->currentText()+". Plase select the right device.");
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
            case USBtinyISPGUI::readFUSEBYTES:
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
            case USBtinyISPGUI::readFUSEBYTES:
            {
                QStringList list;
                process->setReadChannel(QProcess::StandardOutput);
                processOutput=process->readAllStandardOutput();
                processOutput=processOutput.remove("0x",Qt::CaseInsensitive);
                list=processOutput.split(QRegExp("\\s+"));
                ui->highByteLineEdit->setText(list.at(1));
                hfuseByteValue=ui->highByteLineEdit->text().toInt(&ok,16);
                HFUSEChanged(list.at(1));
                ui->lowByteLineEdit->setText(list.at(0));
                LFUSEChanged(list.at(0));
                lfuseByteValue=ui->lowByteLineEdit->text().toInt(&ok,16);
            }
            break;
            case USBtinyISPGUI::getDeviceInfoData:
            {
                deviceInfo->setDeviceInformation(process->readAllStandardError());
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


void USBtinyISPGUI::startButtonPressed()
{   
    switch (actionButtonGroup->checkedId())
    {
        case 0:
            {
                processID=USBtinyISPGUI::programDevice;
                emit startProcess(USBtinyISPGUI::programDevice);
            }
            break;
        case 1:
            {
                processID=USBtinyISPGUI::eraseDevice;
                emit startProcess(USBtinyISPGUI::eraseDevice);
            }
    }
}

void USBtinyISPGUI::readPushButtonPressed()
{
    processID=USBtinyISPGUI::readFUSEBYTES;
    emit startProcess(USBtinyISPGUI::readFUSEBYTES);
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
            emit startProcess(USBtinyISPGUI::writeFUSEBYTES);
            break;
        default:
            return;

     }
}

void USBtinyISPGUI::execCommand(int actionID)
{
    QString cmd;

    if (!findUSBTinyProgrammer())
    {
        QMessageBox::critical(this,"Error","USBTiny programmer is not present!\nPlease connect the USBTiny and then try again.");
        statusLabel->setText("Ready");
        return;
    }

    cmd=Command+" -q"+" -p "+microcontrollerList.at(ui->microcontrollerComboBox->currentIndex());
    switch (actionID)
    {
        case USBtinyISPGUI::programDevice:
            {
                cmd+=cmdLineOptions.at(ui->memoryComboBox->currentIndex())+ui->HEXFileLineEdit->text();
                statusLabel->setText("Burning");
            }
            break;
        case USBtinyISPGUI::eraseDevice:
            {
                cmd+=cmdLineOptions.at(2);
                statusLabel->setText("Erasing");
            }
            break;
        case USBtinyISPGUI::writeFUSEBYTES:
            {
                cmd+=cmdLineOptions.at(USBtinyISPGUI::writeFUSEBYTES+1)+"0x"+ui->highByteLineEdit->text()+":m";
                cmd+=cmdLineOptions.at(USBtinyISPGUI::writeFUSEBYTES+2)+"0x"+ui->lowByteLineEdit->text()+":m";
                statusLabel->setText("Writing");
            }
            break;
        case USBtinyISPGUI::readFUSEBYTES:
            {
                cmd+=cmdLineOptions.at(USBtinyISPGUI::readFUSEBYTES+1)+" -q";
                statusLabel->setText("Reading");
            }
            break;
        case USBtinyISPGUI::getDeviceInfoData:
            {
                cmd+=" -v";
                statusLabel->setText("Reading");
            }
            break;
        default:
            return;
    }

    connect(timeLine,SIGNAL(finished()),timeLine,SLOT(start()));
    timeLine->start();
    process->start(cmd,QProcess::ReadWrite);

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
    disconnect(timeLine,SIGNAL(finished()),timeLine,SLOT(start()));
    timeLine->stop();
    timeLine->setCurrentTime(0);
    statusLabel->setText("Error");

    //statusProgressBar->setValue(0);

    Command=AVRDUDEexecutable+AVRDUDEconffile+verifyArgument+autoEraseArgument;

    switch (error)
    {
        case QProcess::FailedToStart:
            QMessageBox::critical(this, "Error","Faild to start AVRDUDE!");
            break;
        case QProcess::UnknownError:
            QMessageBox::critical(this,"Error","Unkown error during execution!");
            break;
        case QProcess::Crashed:
            QMessageBox::critical(this, "Error",QString(process->readAllStandardError()).remove("avrdude:"));
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
    //ui->selectFileGroupBox->setEnabled(false);
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

void USBtinyISPGUI::AVRDUDESettingsChanged(QString exe,QString conf,bool verify, bool eraseBefore)
{

    QString verifyXML="1";
    QString eraseBeforeXML="1";

    newConfiguration.clear();
    AVRDUDEexecutable=exe+" -c usbtiny";
    AVRDUDEconffile=" -C "+conf;
    newConfiguration << exe << conf;

    if(verify)
        verifyArgument="";
    else
    {
        verifyArgument=" -V";
        verifyXML="0";
    }
    if(eraseBefore)
        autoEraseArgument="";
    else
    {
        autoEraseArgument=" -D";
        eraseBeforeXML="0";
    }

    newConfiguration << verifyXML << eraseBeforeXML;

    Command=AVRDUDEexecutable+AVRDUDEconffile+verifyArgument+autoEraseArgument;
    isConfigurationChanged=true;

}

bool USBtinyISPGUI::findAVRDUDE(void)
{
    QProcess findDude;
    QFileInfo confDude("/etc/avrdude.conf");

    findDude.start("which avrdude",QProcess::ReadWrite);
    while(!findDude.waitForFinished()) ;
    if (!confDude.exists() || findDude.exitCode())
    {
        configureProgrammer->DisableOKButton();
        return false;
    }
    configureProgrammer->setAVRDUDEConfigFile("/etc/avrdude.conf");
    configureProgrammer->setAVRDUDEBin(findDude.readAll().simplified());
    return true;
}

void USBtinyISPGUI::getDeviceInfo()
{
    processID=USBtinyISPGUI::getDeviceInfoData;
    emit startProcess(USBtinyISPGUI::getDeviceInfoData);
}

bool USBtinyISPGUI::doesConfigFileExist(QString configurationFile)
{
    QFileInfo confFile(configurationFile);

    if (!confFile.exists() && !confFile.isReadable() && !confFile.isWritable())
        return false;

    return true;
}

void USBtinyISPGUI::getProgrammerConfig(void)
{

    bool verify=false;
    bool autoErase=false;
    QDomNodeList configNode = xmlDoc.elementsByTagName("config");
    QDomElement child = configNode.at(0).firstChild().toElement();
    QDomText textNode;

    this->configNode=configNode.at(0);

    textNode=child.firstChild().toText();
    AVRDUDEexecutable=textNode.data().remove('"');
    child=child.nextSiblingElement();

    textNode=child.firstChild().toText();
    AVRDUDEconffile=textNode.data().remove('"');
    child=child.nextSiblingElement();

    if(child.firstChild().toText().data().toInt()==1)
    {
       autoEraseArgument="";
       autoErase=true;
    }
    else
       autoEraseArgument=" -D";

    child=child.nextSiblingElement();
    if(child.firstChild().toText().data().toInt()==1)
    {
       verifyArgument="";
       verify=true;
    }
    else
       verifyArgument=" -V";

    emit setConfiguration(AVRDUDEexecutable,AVRDUDEconffile,verify,autoErase);

}

void USBtinyISPGUI::getMicrocontrollerList(void)
{
    QDomNodeList configNode = xmlDoc.elementsByTagName("AVRDevice");
    QDomAttr attr;

    supportedAVRMicrocontrollers=configNode;

    for(int i=0;i<configNode.count();i++)
    {
        attr=configNode.at(i).toElement().attributeNode("id");
        microcontrollerList << attr.value();
        ui->microcontrollerComboBox->addItem(attr.value());
    }

}

void USBtinyISPGUI::getAVRFuseBits(int index)
{
    int i=7;
    QDomElement microcontroller = supportedAVRMicrocontrollers.at(index).firstChild().toElement();
    QButtonGroup *buttonGroup=hfuseButtonGroup;

    ui->memoryComboBox->clear();
    ui->memoryComboBox->addItem("Flash");
    //ui->lowByteLineEdit->clear();
    //ui->highByteLineEdit->clear();

    if (microcontroller.nodeName()=="EEPROM")
        if (microcontroller.text().toInt())
            ui->memoryComboBox->addItem("EEPROM");
    microcontroller=microcontroller.nextSiblingElement();

    while (!microcontroller.isNull())
    {
        if (microcontroller.hasChildNodes())
        {
            if (microcontroller.nodeName()=="LFUSE")
            {
                i=7;
                buttonGroup=lfuseButtonGroup;
            }
            QDomElement child = microcontroller.firstChild().toElement();
            while (!child.isNull())
            {
                if (child.nodeName().contains("bit",Qt::CaseInsensitive))
                    buttonGroup->button(i--)->setText(child.text());
                child=child.nextSiblingElement();
            }
        }
        microcontroller=microcontroller.nextSiblingElement();
    }
}

void USBtinyISPGUI::getDefaultValuesForFuseBits()
{
    QDomElement microcontroller = supportedAVRMicrocontrollers.at(ui->microcontrollerComboBox->currentIndex()).firstChild().toElement();
    bool ok;

    while (!microcontroller.isNull())
    {
        if (microcontroller.nodeName()=="HFUSE")
                ui->highByteLineEdit->setText(microcontroller.attributeNode("defaultValue").value().remove(0,2));
        HFUSEChanged(ui->highByteLineEdit->text());
        hfuseByteValue=ui->highByteLineEdit->text().toInt(&ok,16);
        if (microcontroller.nodeName()=="LFUSE")
                ui->lowByteLineEdit->setText(microcontroller.attributeNode("defaultValue").value().remove(0,2));
        LFUSEChanged(ui->lowByteLineEdit->text());
        lfuseByteValue=ui->lowByteLineEdit->text().toInt(&ok,16);
     microcontroller=microcontroller.nextSiblingElement();
    }
}

void USBtinyISPGUI::LFUSEChanged(QString newValue)
{
    int mask=128;
    int index=7;
    bool ok;
    lfuseByteValue=newValue.toInt(&ok,16);

    while(mask)
    {
        if (lfuseByteValue & mask)
            lfuseButtonGroup->button(index--)->setChecked(true);
        else
            lfuseButtonGroup->button(index--)->setChecked(false);
        mask>>=1;
    }
}

void USBtinyISPGUI::HFUSEChanged(QString newValue)
{
    int mask=128;
    int index=7;
    bool ok;
    hfuseByteValue=newValue.toInt(&ok,16);

    while(mask)
    {
        if (hfuseByteValue & mask)
            hfuseButtonGroup->button(index--)->setChecked(true);
        else
            hfuseButtonGroup->button(index--)->setChecked(false);
        mask>>=1;
    }
}

void USBtinyISPGUI::HFUSEButtonGroupChanged(int id)
{
    int mask=1;

    mask<<=id;
    if (hfuseButtonGroup->button(id)->isChecked())
        hfuseByteValue|=mask;
    else
        hfuseByteValue&=~mask;
    ui->highByteLineEdit->setText(QString::number(hfuseByteValue,16));

}

void USBtinyISPGUI::LFUSEButtonGroupChanged(int id)
{
    int mask=1;

    mask<<=id;
    if (lfuseButtonGroup->button(id)->isChecked())
        lfuseByteValue|=mask;
    else
        lfuseByteValue&=~mask;
    ui->lowByteLineEdit->setText(QString::number(lfuseByteValue,16));
}

void USBtinyISPGUI::closeEvent(QCloseEvent *event)
{
    QDomElement child = configNode.firstChild().toElement();
    QTextStream outStream(&xmlConfigFile);
    QDomText textNode;

    if(!xmlConfigFile.open(QIODevice::WriteOnly))
        QMessageBox::critical(this,"Error","Cannot Write to the configuration file!");
    else
    {
        outStream.flush();

        for(int i=0;i<newConfiguration.length();i++)
        {
            textNode=child.firstChild().toText();
            textNode.setData(newConfiguration.at(i));
            child=child.nextSiblingElement();
        }

        xmlDoc.save(outStream,3);
        xmlConfigFile.close();
    }

    event->accept();

}


void USBtinyISPGUI::about() {
QMessageBox::about(this, tr("About USBtinyISP GUI"),
            tr("<h2>USBtinyISP GUI 1.0</h2>"
               "<p>"
               "<p>USBtiny GUI is a small GUI frontend application for "
               "avrdude and USBtinyISP programmer."
               "<p>Minimal software requerements: <br>"
               "- <a href=\"http://savannah.nongnu.org/projects/avrdude/\">avrdude</a> min. version 5.5 or newer;<br>"
               "- <a href=\"http://www.ladyada.net/make/usbtinyisp/\">USBtinyISP</a> programmer."
               "<p>Author: Goce Boshkovski"
               ));
}
