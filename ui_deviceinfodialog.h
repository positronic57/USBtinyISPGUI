/********************************************************************************
** Form generated from reading UI file 'deviceinfodialog.ui'
**
** Created: Mon Mar 8 22:22:23 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEVICEINFODIALOG_H
#define UI_DEVICEINFODIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHeaderView>
#include <QtGui/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_deviceinfodialog
{
public:
    QDialogButtonBox *buttonBox;
    QTextEdit *textEdit;

    void setupUi(QDialog *deviceinfodialog)
    {
        if (deviceinfodialog->objectName().isEmpty())
            deviceinfodialog->setObjectName(QString::fromUtf8("deviceinfodialog"));
        deviceinfodialog->resize(820, 300);
        buttonBox = new QDialogButtonBox(deviceinfodialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(722, 20, 81, 31));
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Ok);
        textEdit = new QTextEdit(deviceinfodialog);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(20, 20, 681, 261));

        retranslateUi(deviceinfodialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), deviceinfodialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), deviceinfodialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(deviceinfodialog);
    } // setupUi

    void retranslateUi(QDialog *deviceinfodialog)
    {
        deviceinfodialog->setWindowTitle(QApplication::translate("deviceinfodialog", "Connected Device Info", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class deviceinfodialog: public Ui_deviceinfodialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEVICEINFODIALOG_H
