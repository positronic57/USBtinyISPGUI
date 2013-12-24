/*
* Copyright (c) 2013 Goce Boshkovski
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License.
*
*/

#include <QtGui/QApplication>
#include "USBtinyISPGUI.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    USBtinyISPGUI w;
    if (!w.findUSBTinyProgrammer())
    {
        QMessageBox::critical(&w,"Error","USBtinyISP programmer is not present!\nPlease connect the USBTinyISP and then start the program again.");
        return 1;
    }

    if (!w.doesConfigFileExist(a.applicationDirPath()+"/config/USBtinyISPGUIConfigFile.xml"))
    {
        QMessageBox::critical(&w,"Error","AVRProgrammer Confguration File is missing!");
        return 1;
    }

    w.show();
    return a.exec();
}
