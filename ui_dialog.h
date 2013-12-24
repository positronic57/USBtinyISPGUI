/********************************************************************************
** Form generated from reading ui file 'dialog.ui'
**
** Created: Sun Apr 5 01:14:57 2009
**      by: Qt User Interface Compiler version 4.4.1
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QListWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QDialogButtonBox *buttonBox;
    QListWidget *listWidget;

    void setupUi(QDialog *Dialog)
    {
    if (Dialog->objectName().isEmpty())
        Dialog->setObjectName(QString::fromUtf8("Dialog"));
    Dialog->resize(519, 318);
    buttonBox = new QDialogButtonBox(Dialog);
    buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
    buttonBox->setGeometry(QRect(420, 20, 81, 31));
    buttonBox->setOrientation(Qt::Vertical);
    buttonBox->setStandardButtons(QDialogButtonBox::Ok);
    listWidget = new QListWidget(Dialog);
    listWidget->setObjectName(QString::fromUtf8("listWidget"));
    listWidget->setGeometry(QRect(20, 20, 381, 281));

    retranslateUi(Dialog);
    QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

    QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
    Dialog->setWindowTitle(QApplication::translate("Dialog", "Device Info", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Dialog);
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
