/*
* Copyright (c) 2013 Goce Boshkovski
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License.
*
*/

#include "deviceinfodialog.h"
#include "ui_deviceinfodialog.h"

deviceinfodialog::deviceinfodialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::deviceinfodialog)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    ui->textEdit->setAcceptRichText(true);
    ui->textEdit->setAlignment(Qt::AlignJustify);
    ui->textEdit->setAutoFormatting(QTextEdit::AutoAll);
    ui->textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
}

deviceinfodialog::~deviceinfodialog()
{
    delete ui;
}

void deviceinfodialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void deviceinfodialog::setDeviceInformation(QByteArray deviceinfo)
{
    QString txtoutput = deviceinfo;
    ui->textEdit->setText(txtoutput);
}

