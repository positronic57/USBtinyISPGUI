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

#include <QDialog>
#include <QFileDialog>
#include "ui_configureDialog.h"

#include "confighandler.h"

class configureDialog : public QDialog
{
    Q_OBJECT

public:
    configureDialog(ConfigHandler::AvrdudeConfig &avrdude_config, ConfigHandler::BurnerConfig &burner_config, QWidget *parent = 0);
    ~configureDialog();

private:
    Ui::configureDialog *ui;

public slots:
    void accept();
private slots:
    void checkExecLine(QString);
    void checkConfLine(QString);
    void slotExecBrowsePushButtonClicked();
    void slotConfigBrowsePushButtonClicked();

signals:
    void signalNewConfigValuesAvailable(const ConfigHandler::AvrdudeConfig, const ConfigHandler::BurnerConfig);
};

#endif // CONFIGUREDIALOG_H
