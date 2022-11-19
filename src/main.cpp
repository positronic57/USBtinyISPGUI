/*
* Copyright (c) 2013 Goce Boshkovski
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License.
*
*/

#include <QApplication>
#include <QDesktopWidget>

#include "USBtinyISPGUI.h"
#include "confighandler.h"

void show_messages_on_start(QMessageBox::Icon icon, const QString &title, const QString &msg, bool quit_app = false, int exit_code = 0)
{
    QMessageBox warrning_msg(
                icon,
                title,
                msg,
                QMessageBox::Ok,
                QDesktopWidget().screen(),
                Qt::Dialog
                );
    warrning_msg.exec();

    if (quit_app) {
        exit(exit_code);
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    USBtinyISPGUI w;

    /* Exit in case the configuration file of USBtunyISP doesn't exist. */
    if (!ConfigHandler::config_file_exists(qApp->applicationDirPath() + "/config/USBtinyISPGUIConfigFile.xml"))
    {
        // Missing configuration file. Exit
        show_messages_on_start(
                    QMessageBox::Critical,
                    "Critical Error",
                    "USBtinyISPGUI confguration file is missing!",
                    true,
                    1
                    );
    }

    if (!ConfigHandler::is_config_file_writable(qApp->applicationDirPath() + "/config/USBtinyISPGUIConfigFile.xml")) {
        // Configuration file is not writable
        show_messages_on_start(
                    QMessageBox::Warning,
                    "Warrning",
                    "USBtinyISPGUI confguration file is not writable.\nAll changes made within configuration dialog cannot be saved."
                    );
    }

    if (!ConfigHandler::is_config_file_readable(qApp->applicationDirPath() + "/config/USBtinyISPGUIConfigFile.xml")) {
        // Configuration file is not readable
        show_messages_on_start(
                    QMessageBox::Critical,
                    "Critical Error",
                    "USBtinyISPGUI confguration file is not readable!",
                    true,
                    1
                    );
    }

    // Load configuration
    int error_code = w.init();
    if (error_code) {
        exit(error_code);
    }

    w.show();

    return a.exec();
}
