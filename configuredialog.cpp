/*
* Copyright (c) 2013 Goce Boshkovski
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License.
*
*/

#include "configuredialog.h"

configureDialog::configureDialog(QWidget *parent)
    : QDialog(parent)
{
    ui.setupUi(this);

    execFileDialog=new QFileDialog(this);
    execFileDialog->setViewMode(QFileDialog::Detail);
    execFileDialog->setFileMode(QFileDialog::ExistingFile);
    execFileDialog->setNameFilter("AVRDUDE binary (avrdude)");
    execFileDialog->setViewMode(QFileDialog::Detail);
    execFileDialog->setDirectory("/home/");

    confFileDialog=new QFileDialog(this);
    confFileDialog->setViewMode(QFileDialog::Detail);
    confFileDialog->setFileMode(QFileDialog::ExistingFile);
    confFileDialog->setNameFilter("AVRDUDE conf file (avrdude.conf)");
    confFileDialog->setViewMode(QFileDialog::Detail);
    confFileDialog->setDirectory("/home/");

    execFile=new QFileInfo();
    confFile=new QFileInfo();

    connect(ui.cancelPushButton,SIGNAL(clicked()),this,SLOT(reject()));
    connect(ui.OKPushButton,SIGNAL(clicked()),this,SLOT(AVRDUDEParameters()));
    connect(ui.OKPushButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(ui.execBrowsePushButton,SIGNAL(clicked()),execFileDialog,SLOT(exec()));
    connect(ui.confBrowsePushButton,SIGNAL(clicked()),confFileDialog,SLOT(exec()));
    connect(execFileDialog,SIGNAL(filesSelected(QStringList)),this,SLOT(execFileSelected(QStringList)));
    connect(confFileDialog,SIGNAL(filesSelected(QStringList)),this,SLOT(confFileSelected(QStringList)));
    connect(ui.avrdudeExecLineEdit,SIGNAL(textEdited(QString)),this,SLOT(checkExecLine(QString)));
    connect(ui.confFileLineEdit,SIGNAL(textEdited(QString)),this,SLOT(checkConfLine(QString)));


}

configureDialog::~configureDialog()
{
    delete execFileDialog;
    delete confFileDialog;
    delete execFile;
    delete confFile;
}


void configureDialog::AVRDUDEParameters()
{
    emit parametersChanged(ui.avrdudeExecLineEdit->text(),ui.confFileLineEdit->text(),ui.verifyCheckBox->isChecked(),ui.disableAutoEraseCheckBox->isChecked());
    this->hide();
}

void configureDialog::execFileSelected(QStringList selectedFiles)
{
    ui.avrdudeExecLineEdit->setText(selectedFiles.first());
    execFile->setFile(ui.avrdudeExecLineEdit->text());
        if ((execFile->exists() && !execFile->isDir()) && (confFile->exists() && !confFile->isDir()))
        ui.OKPushButton->setEnabled(true);
    else
        ui.OKPushButton->setEnabled(false);
}

void configureDialog::confFileSelected(QStringList selectedFiels)
{
    ui.confFileLineEdit->setText(selectedFiels.first());
    confFile->setFile(ui.confFileLineEdit->text());
    if ((execFile->exists() && !execFile->isDir()) && (confFile->exists() && !confFile->isDir()))
        ui.OKPushButton->setEnabled(true);
    else
        ui.OKPushButton->setEnabled(false);
}

void configureDialog::setAVRDUDEBin(QString avrdude)
{
    ui.avrdudeExecLineEdit->setText(avrdude);
    execFile->setFile(avrdude);
}

void configureDialog::setAVRDUDEConfigFile(QString configFile)
{
    ui.confFileLineEdit->setText(configFile);
    confFile->setFile(configFile);
}

void configureDialog::checkExecLine(QString execFile)
{
    this->execFile->setFile(execFile);
    if ((this->execFile->exists() && !this->execFile->isDir()) && (confFile->exists() && !confFile->isDir()))
        ui.OKPushButton->setEnabled(true);
    else
        ui.OKPushButton->setEnabled(false);
}

void configureDialog::checkConfLine(QString confFile)
{
    this->confFile->setFile(confFile);
    if ((this->confFile->exists() && !this->confFile->isDir()) && (execFile->exists() && !execFile->isDir()))
        ui.OKPushButton->setEnabled(true);
    else
        ui.OKPushButton->setEnabled(false);
}

void configureDialog::DisableOKButton()
{
    ui.OKPushButton->setEnabled(false);
}

void configureDialog::setConfiguration(QString avrdudeBIN,QString avrdudeConfFile,bool verify,bool autoErase)
{
    setAVRDUDEBin(avrdudeBIN);
    setAVRDUDEConfigFile(avrdudeConfFile);
    ui.verifyCheckBox->setChecked(verify);
    ui.disableAutoEraseCheckBox->setChecked(autoErase);
}






