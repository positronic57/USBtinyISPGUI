/********************************************************************************
** Form generated from reading UI file 'configureDialog.ui'
**
** Created: Mon Mar 8 22:22:23 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGUREDIALOG_H
#define UI_CONFIGUREDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_configureDialog
{
public:
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *confFileLineEdit;
    QPushButton *confBrowsePushButton;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout;
    QLineEdit *avrdudeExecLineEdit;
    QPushButton *execBrowsePushButton;
    QPushButton *OKPushButton;
    QPushButton *cancelPushButton;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;
    QCheckBox *verifyCheckBox;
    QCheckBox *disableAutoEraseCheckBox;

    void setupUi(QDialog *configureDialog)
    {
        if (configureDialog->objectName().isEmpty())
            configureDialog->setObjectName(QString::fromUtf8("configureDialog"));
        configureDialog->resize(400, 249);
        QFont font;
        font.setBold(false);
        font.setWeight(50);
        configureDialog->setFont(font);
        groupBox = new QGroupBox(configureDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 80, 381, 61));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 361, 30));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        confFileLineEdit = new QLineEdit(layoutWidget);
        confFileLineEdit->setObjectName(QString::fromUtf8("confFileLineEdit"));

        horizontalLayout_2->addWidget(confFileLineEdit);

        confBrowsePushButton = new QPushButton(layoutWidget);
        confBrowsePushButton->setObjectName(QString::fromUtf8("confBrowsePushButton"));

        horizontalLayout_2->addWidget(confBrowsePushButton);

        groupBox_2 = new QGroupBox(configureDialog);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 10, 381, 61));
        layoutWidget1 = new QWidget(groupBox_2);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 20, 361, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        avrdudeExecLineEdit = new QLineEdit(layoutWidget1);
        avrdudeExecLineEdit->setObjectName(QString::fromUtf8("avrdudeExecLineEdit"));

        horizontalLayout->addWidget(avrdudeExecLineEdit);

        execBrowsePushButton = new QPushButton(layoutWidget1);
        execBrowsePushButton->setObjectName(QString::fromUtf8("execBrowsePushButton"));

        horizontalLayout->addWidget(execBrowsePushButton);

        OKPushButton = new QPushButton(configureDialog);
        OKPushButton->setObjectName(QString::fromUtf8("OKPushButton"));
        OKPushButton->setGeometry(QRect(207, 210, 84, 28));
        cancelPushButton = new QPushButton(configureDialog);
        cancelPushButton->setObjectName(QString::fromUtf8("cancelPushButton"));
        cancelPushButton->setGeometry(QRect(297, 210, 84, 28));
        layoutWidget2 = new QWidget(configureDialog);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(10, 149, 363, 56));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        verifyCheckBox = new QCheckBox(layoutWidget2);
        verifyCheckBox->setObjectName(QString::fromUtf8("verifyCheckBox"));
        verifyCheckBox->setChecked(true);

        verticalLayout->addWidget(verifyCheckBox);

        disableAutoEraseCheckBox = new QCheckBox(layoutWidget2);
        disableAutoEraseCheckBox->setObjectName(QString::fromUtf8("disableAutoEraseCheckBox"));
        disableAutoEraseCheckBox->setChecked(true);

        verticalLayout->addWidget(disableAutoEraseCheckBox);

        QWidget::setTabOrder(avrdudeExecLineEdit, execBrowsePushButton);
        QWidget::setTabOrder(execBrowsePushButton, confFileLineEdit);
        QWidget::setTabOrder(confFileLineEdit, confBrowsePushButton);
        QWidget::setTabOrder(confBrowsePushButton, verifyCheckBox);
        QWidget::setTabOrder(verifyCheckBox, OKPushButton);
        QWidget::setTabOrder(OKPushButton, disableAutoEraseCheckBox);
        QWidget::setTabOrder(disableAutoEraseCheckBox, cancelPushButton);

        retranslateUi(configureDialog);

        QMetaObject::connectSlotsByName(configureDialog);
    } // setupUi

    void retranslateUi(QDialog *configureDialog)
    {
        configureDialog->setWindowTitle(QApplication::translate("configureDialog", "Configure USBtinyISP GUI", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("configureDialog", "Valid AVRDUDE Configuration file:", 0, QApplication::UnicodeUTF8));
        confFileLineEdit->setText(QString());
        confBrowsePushButton->setText(QApplication::translate("configureDialog", "Browse", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("configureDialog", "AVRDUDE executable:", 0, QApplication::UnicodeUTF8));
        avrdudeExecLineEdit->setText(QString());
        execBrowsePushButton->setText(QApplication::translate("configureDialog", "Browse", 0, QApplication::UnicodeUTF8));
        OKPushButton->setText(QApplication::translate("configureDialog", "OK", 0, QApplication::UnicodeUTF8));
        cancelPushButton->setText(QApplication::translate("configureDialog", "Cancel", 0, QApplication::UnicodeUTF8));
        verifyCheckBox->setText(QApplication::translate("configureDialog", "Verify content of the microcontroller after burrning.", 0, QApplication::UnicodeUTF8));
        disableAutoEraseCheckBox->setText(QApplication::translate("configureDialog", "Auto erase of flash memory before burning", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class configureDialog: public Ui_configureDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGUREDIALOG_H
