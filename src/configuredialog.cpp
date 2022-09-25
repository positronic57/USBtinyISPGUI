/*
* Copyright (c) 2013 Goce Boshkovski
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License.
*
*/

#include "configuredialog.h"

configureDialog::configureDialog(ConfigHandler::AvrdudeConfig &avrdude_config, ConfigHandler::BurnerConfig &burner_config, QWidget *parent)
    : QDialog(parent),
      ui(new Ui::configureDialog)
{
    ui->setupUi(this);

    ui->avrdudeExecLineEdit->setText(avrdude_config.binary);
    ui->confFileLineEdit->setText(avrdude_config.config_file);
    ui->verifyCheckBox->setChecked(burner_config.verify_after_burn);
    ui->disableAutoEraseCheckBox->setChecked(burner_config.errase_flash_before_burn);

    connect(ui->cancelPushButton,SIGNAL(clicked()),this, SLOT(reject()));
    connect(ui->OKPushButton,SIGNAL(clicked()),this, SLOT(accept()));

    connect(ui->execBrowsePushButton, &QPushButton::clicked, this , &configureDialog::slotExecBrowsePushButtonClicked);
    connect(ui->confBrowsePushButton, &QPushButton::clicked, this , &configureDialog::slotConfigBrowsePushButtonClicked);

    connect(ui->avrdudeExecLineEdit,SIGNAL(textEdited(QString)),this,SLOT(checkExecLine(QString)));
    connect(ui->confFileLineEdit,SIGNAL(textEdited(QString)),this,SLOT(checkConfLine(QString)));
}


configureDialog::~configureDialog()
{
    delete ui;
}

void configureDialog::checkExecLine(QString execFile)
{
    if (QFileInfo::exists(execFile) && QFileInfo::exists(ui->confFileLineEdit->text()))
        ui->OKPushButton->setEnabled(true);
    else
        ui->OKPushButton->setEnabled(false);
}

void configureDialog::checkConfLine(QString confFile)
{
    if (QFileInfo::exists(ui->avrdudeExecLineEdit->text()) && QFileInfo::exists(confFile))
        ui->OKPushButton->setEnabled(true);
    else
        ui->OKPushButton->setEnabled(false);
}

void configureDialog::accept()
{
    ConfigHandler::AvrdudeConfig avrdude_conf(
                ui->avrdudeExecLineEdit->text(),
                ui->confFileLineEdit->text()
                );
    ConfigHandler::BurnerConfig burner_config(
                ui->disableAutoEraseCheckBox->isChecked(),
                ui->verifyCheckBox->isChecked(),
                "usbtiny"
                );

    emit signalNewConfigValuesAvailable(avrdude_conf, burner_config);

    this->close();
}

void configureDialog::slotExecBrowsePushButtonClicked()
{
    QFileDialog *execFileDialog = new QFileDialog(this);

    execFileDialog->setViewMode(QFileDialog::Detail);
    execFileDialog->setFileMode(QFileDialog::ExistingFile);
    execFileDialog->setNameFilter("AVRDUDE binary (avrdude)");
    execFileDialog->setViewMode(QFileDialog::Detail);
    execFileDialog->setDirectory("/home/");

    if (execFileDialog->exec() == QDialog::Accepted) {
        // User clicked OK
        ui->avrdudeExecLineEdit->setText(execFileDialog->selectedFiles().at(0));
        ui->OKPushButton->setEnabled(true);
    }

    delete execFileDialog;
}

void configureDialog::slotConfigBrowsePushButtonClicked()
{
    QFileDialog  *confFileDialog = new QFileDialog(this);

    confFileDialog->setViewMode(QFileDialog::Detail);
    confFileDialog->setFileMode(QFileDialog::ExistingFile);
    confFileDialog->setNameFilter("AVRDUDE conf file (avrdude.conf)");
    confFileDialog->setViewMode(QFileDialog::Detail);
    confFileDialog->setDirectory("/home/");

    if (confFileDialog->exec() == QDialog::Accepted) {
        // User clicked OK
        ui->confFileLineEdit->setText(confFileDialog->selectedFiles().at(0));
        ui->OKPushButton->setEnabled(true);
    }

    delete confFileDialog;
}






