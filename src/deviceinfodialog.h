/*
* Copyright (c) 2013 Goce Boshkovski
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License.
*
*/

#ifndef DEVICEINFODIALOG_H
#define DEVICEINFODIALOG_H

#include <QDialog>
#include <qtextedit.h>

namespace Ui {
    class deviceinfodialog;
}

class deviceinfodialog : public QDialog {
    Q_OBJECT
    Q_DISABLE_COPY(deviceinfodialog)
public:
    explicit deviceinfodialog(QWidget *parent = 0);
    virtual ~deviceinfodialog();
    void setDeviceInformation(QByteArray);

protected:
    virtual void changeEvent(QEvent *e);

private:
    Ui::deviceinfodialog *ui;
};

#endif // DEVICEINFODIALOG_H
