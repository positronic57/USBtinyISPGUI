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
    m_ui(new Ui::deviceinfodialog)
{
    m_ui->setupUi(this);
    m_ui->textEdit->setReadOnly(true);
    m_ui->textEdit->setAcceptRichText(true);
    m_ui->textEdit->setAlignment(Qt::AlignJustify);
    m_ui->textEdit->setAutoFormatting(QTextEdit::AutoAll);
    m_ui->textEdit->setLineWrapMode(QTextEdit::WidgetWidth);
}

deviceinfodialog::~deviceinfodialog()
{
    delete m_ui;
}

void deviceinfodialog::changeEvent(QEvent *e)
{
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void deviceinfodialog::setDeviceInformation(QByteArray deviceinfo)
{
    QString txtoutput = deviceinfo;
    m_ui->textEdit->setText(txtoutput);
}

