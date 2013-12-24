/*
* Copyright (c) 2013 Goce Boshkovski
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License.
*
*/

#ifndef CONFIGUREDIALOG_H
#define CONFIGUREDIALOG_H

#include <QtGui/QDialog>
#include <QFileDialog>
#include "ui_configureDialog.h"

class configureDialog : public QDialog
{
        Q_OBJECT

    public:
        configureDialog(QWidget *parent = 0);
        ~configureDialog();
        void setAVRDUDEBin(QString);
        void setAVRDUDEConfigFile(QString);
        void DisableOKButton();

    private:
        Ui::configureDialog ui;
        QFileDialog *execFileDialog;
        QFileDialog *confFileDialog;
        QFileInfo *execFile;
        QFileInfo *confFile;

    public slots:
        void AVRDUDEParameters();
        void execFileSelected(QStringList);
        void confFileSelected(QStringList);
        void checkExecLine(QString);
        void checkConfLine(QString);
        void setConfiguration(QString,QString,bool,bool);

    signals:
        void parametersChanged(QString,QString,bool,bool);

};

#endif // CONFIGUREDIALOG_H
