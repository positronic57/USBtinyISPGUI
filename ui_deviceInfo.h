/********************************************************************************
** Form generated from reading ui file 'deviceinfo.ui'
**
** Created: Sat Apr 4 01:38:18 2009
**      by: Qt User Interface Compiler version 4.4.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DEVICEINFO_H
#define UI_DEVICEINFO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_deviceInfoDialog
{
public:
    QDialogButtonBox *buttonBox;
    QListWidget *listWidget;

    void setupUi(QDialog *deviceInfoDialog)
    {
    if (deviceInfoDialog->objectName().isEmpty())
        deviceInfoDialog->setObjectName(QString::fromUtf8("deviceInfoDialog"));
    deviceInfoDialog->resize(497, 300);
    buttonBox = new QDialogButtonBox(deviceInfoDialog);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setGeometry(QRect(400, 19, 81, 31));
    buttonBox->setOrientation(Qt::Vertical);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok);
    listWidget = new QListWidget(deviceInfoDialog);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setGeometry(QRect(20, 20, 371, 261));

    retranslateUi(deviceInfoDialog);
    QObject::connect(buttonBox, SIGNAL(accepted()), deviceInfoDialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), deviceInfoDialog, SLOT(reject()));

    QMetaObject::connectSlotsByName(deviceInfoDialog);
    } // setupUi

    void retranslateUi(QDialog *deviceInfoDialog)
    {
    deviceInfoDialog->setWindowTitle(QApplication::translate("deviceInfoDialog", "Device Info", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(deviceInfoDialog);
    } // retranslateUi

};

namespace Ui {
    class deviceInfoDialog: public Ui_deviceInfoDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEINFO_H
