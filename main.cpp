/*
* Copyright (c) 2013 Goce Boshkovski
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License.
*
*/

#include <QApplication>
#include "USBtinyISPGUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    USBtinyISPGUI w;


    /* Show warning message in case USBtinyISP programmer is not present/connected. */
    if (!w.findUSBTinyProgrammer())
    {
        QMessageBox::warning(&w, "Warrning", "USBtinyISP programmer is not present/connected!\n\nConnect it before using the programmer related functions.", QMessageBox::Ok);
    }


    /* Exit in case the configuration file of USBtunyISP doesn't exist. */
    if (!w.doesConfigFileExist(a.applicationDirPath()+"/config/USBtinyISPGUIConfigFile.xml"))
    {
        QMessageBox::critical(&w, "Error","USBtinyISPGUI confguration file is missing!");
        return -1;
    }

    w.show();

    return a.exec();
}
