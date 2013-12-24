/********************************************************************************
** Form generated from reading UI file 'USBtinyISPGUI.ui'
**
** Created: Mon Mar 8 22:22:23 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USBTINYISPGUI_H
#define UI_USBTINYISPGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_USBtinyISPGUIClass
{
public:
    QAction *actionConfigure;
    QAction *actionExit;
    QAction *actionConvertor;
    QAction *actionDevice_Info;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_12;
    QVBoxLayout *verticalLayout_12;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QComboBox *microcontrollerComboBox;
    QTabWidget *tabWidget;
    QWidget *tab;
    QHBoxLayout *horizontalLayout_11;
    QVBoxLayout *verticalLayout_11;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QRadioButton *programRadioButton;
    QRadioButton *erraseRadioButton;
    QComboBox *memoryComboBox;
    QGroupBox *selectFileGroupBox;
    QHBoxLayout *horizontalLayout_8;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *HEXFileLineEdit;
    QPushButton *openPushButton;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QPushButton *startPushButton;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_2;
    QHBoxLayout *horizontalLayout_10;
    QHBoxLayout *horizontalLayout_9;
    QGroupBox *groupBox_2;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QCheckBox *checkBox_1;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QCheckBox *checkBox_4;
    QCheckBox *checkBox_5;
    QCheckBox *checkBox_6;
    QCheckBox *checkBox_7;
    QCheckBox *checkBox_8;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QLineEdit *highByteLineEdit;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_5;
    QCheckBox *checkBox_9;
    QCheckBox *checkBox_10;
    QCheckBox *checkBox_11;
    QCheckBox *checkBox_12;
    QCheckBox *checkBox_13;
    QCheckBox *checkBox_14;
    QCheckBox *checkBox_15;
    QCheckBox *checkBox_16;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QLineEdit *lowByteLineEdit;
    QVBoxLayout *verticalLayout_10;
    QPushButton *readPushButton;
    QPushButton *defaultPushButton;
    QPushButton *writePushButton;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuHelp;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *USBtinyISPGUIClass)
    {
        if (USBtinyISPGUIClass->objectName().isEmpty())
            USBtinyISPGUIClass->setObjectName(QString::fromUtf8("USBtinyISPGUIClass"));
        USBtinyISPGUIClass->resize(541, 400);
        USBtinyISPGUIClass->setMinimumSize(QSize(490, 387));
        USBtinyISPGUIClass->setMaximumSize(QSize(490000, 387000));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/icons/usbtinyisp-gui-48x48.png"), QSize(), QIcon::Normal, QIcon::Off);
        USBtinyISPGUIClass->setWindowIcon(icon);
        USBtinyISPGUIClass->setIconSize(QSize(32, 32));
        actionConfigure = new QAction(USBtinyISPGUIClass);
        actionConfigure->setObjectName(QString::fromUtf8("actionConfigure"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../icons/configure.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConfigure->setIcon(icon1);
        actionExit = new QAction(USBtinyISPGUIClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../../../icons/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon2);
        actionConvertor = new QAction(USBtinyISPGUIClass);
        actionConvertor->setObjectName(QString::fromUtf8("actionConvertor"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../../../icons/refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionConvertor->setIcon(icon3);
        actionDevice_Info = new QAction(USBtinyISPGUIClass);
        actionDevice_Info->setObjectName(QString::fromUtf8("actionDevice_Info"));
        actionAbout = new QAction(USBtinyISPGUIClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout_Qt = new QAction(USBtinyISPGUIClass);
        actionAbout_Qt->setObjectName(QString::fromUtf8("actionAbout_Qt"));
        centralWidget = new QWidget(USBtinyISPGUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_12 = new QHBoxLayout(centralWidget);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        microcontrollerComboBox = new QComboBox(centralWidget);
        microcontrollerComboBox->setObjectName(QString::fromUtf8("microcontrollerComboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(microcontrollerComboBox->sizePolicy().hasHeightForWidth());
        microcontrollerComboBox->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(microcontrollerComboBox);


        verticalLayout_12->addLayout(horizontalLayout_4);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        horizontalLayout_11 = new QHBoxLayout(tab);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        verticalLayout_11 = new QVBoxLayout();
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(tab);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        programRadioButton = new QRadioButton(groupBox);
        programRadioButton->setObjectName(QString::fromUtf8("programRadioButton"));

        horizontalLayout_2->addWidget(programRadioButton);

        erraseRadioButton = new QRadioButton(groupBox);
        erraseRadioButton->setObjectName(QString::fromUtf8("erraseRadioButton"));

        horizontalLayout_2->addWidget(erraseRadioButton);

        memoryComboBox = new QComboBox(groupBox);
        memoryComboBox->setObjectName(QString::fromUtf8("memoryComboBox"));

        horizontalLayout_2->addWidget(memoryComboBox);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(groupBox);

        selectFileGroupBox = new QGroupBox(tab);
        selectFileGroupBox->setObjectName(QString::fromUtf8("selectFileGroupBox"));
        horizontalLayout_8 = new QHBoxLayout(selectFileGroupBox);
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(selectFileGroupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        HEXFileLineEdit = new QLineEdit(selectFileGroupBox);
        HEXFileLineEdit->setObjectName(QString::fromUtf8("HEXFileLineEdit"));
        HEXFileLineEdit->setMinimumSize(QSize(290, 20));

        horizontalLayout->addWidget(HEXFileLineEdit);

        openPushButton = new QPushButton(selectFileGroupBox);
        openPushButton->setObjectName(QString::fromUtf8("openPushButton"));

        horizontalLayout->addWidget(openPushButton);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer = new QSpacerItem(338, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        startPushButton = new QPushButton(selectFileGroupBox);
        startPushButton->setObjectName(QString::fromUtf8("startPushButton"));
        startPushButton->setMinimumSize(QSize(75, 23));

        horizontalLayout_7->addWidget(startPushButton);


        verticalLayout_2->addLayout(horizontalLayout_7);


        horizontalLayout_8->addLayout(verticalLayout_2);


        verticalLayout->addWidget(selectFileGroupBox);


        verticalLayout_11->addLayout(verticalLayout);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_11->addItem(verticalSpacer_3);


        horizontalLayout_11->addLayout(verticalLayout_11);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        horizontalLayout_10 = new QHBoxLayout(tab_2);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        layoutWidget = new QWidget(groupBox_2);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 20, 101, 221));
        verticalLayout_4 = new QVBoxLayout(layoutWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        checkBox_1 = new QCheckBox(layoutWidget);
        checkBox_1->setObjectName(QString::fromUtf8("checkBox_1"));
        checkBox_1->setMinimumSize(QSize(0, 18));

        verticalLayout_3->addWidget(checkBox_1);

        checkBox_2 = new QCheckBox(layoutWidget);
        checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));
        checkBox_2->setMinimumSize(QSize(0, 18));

        verticalLayout_3->addWidget(checkBox_2);

        checkBox_3 = new QCheckBox(layoutWidget);
        checkBox_3->setObjectName(QString::fromUtf8("checkBox_3"));
        checkBox_3->setMinimumSize(QSize(0, 18));

        verticalLayout_3->addWidget(checkBox_3);

        checkBox_4 = new QCheckBox(layoutWidget);
        checkBox_4->setObjectName(QString::fromUtf8("checkBox_4"));
        checkBox_4->setMinimumSize(QSize(0, 18));

        verticalLayout_3->addWidget(checkBox_4);

        checkBox_5 = new QCheckBox(layoutWidget);
        checkBox_5->setObjectName(QString::fromUtf8("checkBox_5"));
        checkBox_5->setMinimumSize(QSize(0, 18));

        verticalLayout_3->addWidget(checkBox_5);

        checkBox_6 = new QCheckBox(layoutWidget);
        checkBox_6->setObjectName(QString::fromUtf8("checkBox_6"));
        checkBox_6->setMinimumSize(QSize(0, 18));

        verticalLayout_3->addWidget(checkBox_6);

        checkBox_7 = new QCheckBox(layoutWidget);
        checkBox_7->setObjectName(QString::fromUtf8("checkBox_7"));
        checkBox_7->setMinimumSize(QSize(0, 18));

        verticalLayout_3->addWidget(checkBox_7);

        checkBox_8 = new QCheckBox(layoutWidget);
        checkBox_8->setObjectName(QString::fromUtf8("checkBox_8"));
        checkBox_8->setMinimumSize(QSize(0, 18));

        verticalLayout_3->addWidget(checkBox_8);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        highByteLineEdit = new QLineEdit(layoutWidget);
        highByteLineEdit->setObjectName(QString::fromUtf8("highByteLineEdit"));
        highByteLineEdit->setMinimumSize(QSize(32, 20));
        highByteLineEdit->setMaximumSize(QSize(32, 20));

        horizontalLayout_5->addWidget(highByteLineEdit);


        verticalLayout_4->addLayout(horizontalLayout_5);


        horizontalLayout_9->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(tab_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        layoutWidget1 = new QWidget(groupBox_3);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(11, 22, 101, 218));
        verticalLayout_6 = new QVBoxLayout(layoutWidget1);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        verticalLayout_6->setContentsMargins(0, 0, 0, 0);
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        checkBox_9 = new QCheckBox(layoutWidget1);
        checkBox_9->setObjectName(QString::fromUtf8("checkBox_9"));
        checkBox_9->setMaximumSize(QSize(16777215, 18));

        verticalLayout_5->addWidget(checkBox_9);

        checkBox_10 = new QCheckBox(layoutWidget1);
        checkBox_10->setObjectName(QString::fromUtf8("checkBox_10"));
        checkBox_10->setMaximumSize(QSize(16777215, 18));

        verticalLayout_5->addWidget(checkBox_10);

        checkBox_11 = new QCheckBox(layoutWidget1);
        checkBox_11->setObjectName(QString::fromUtf8("checkBox_11"));
        checkBox_11->setMaximumSize(QSize(16777215, 18));

        verticalLayout_5->addWidget(checkBox_11);

        checkBox_12 = new QCheckBox(layoutWidget1);
        checkBox_12->setObjectName(QString::fromUtf8("checkBox_12"));
        checkBox_12->setMaximumSize(QSize(16777215, 18));

        verticalLayout_5->addWidget(checkBox_12);

        checkBox_13 = new QCheckBox(layoutWidget1);
        checkBox_13->setObjectName(QString::fromUtf8("checkBox_13"));
        checkBox_13->setMaximumSize(QSize(16777215, 18));

        verticalLayout_5->addWidget(checkBox_13);

        checkBox_14 = new QCheckBox(layoutWidget1);
        checkBox_14->setObjectName(QString::fromUtf8("checkBox_14"));
        checkBox_14->setMaximumSize(QSize(16777215, 18));

        verticalLayout_5->addWidget(checkBox_14);

        checkBox_15 = new QCheckBox(layoutWidget1);
        checkBox_15->setObjectName(QString::fromUtf8("checkBox_15"));
        checkBox_15->setMaximumSize(QSize(16777215, 18));

        verticalLayout_5->addWidget(checkBox_15);

        checkBox_16 = new QCheckBox(layoutWidget1);
        checkBox_16->setObjectName(QString::fromUtf8("checkBox_16"));
        checkBox_16->setMaximumSize(QSize(16777215, 18));

        verticalLayout_5->addWidget(checkBox_16);


        verticalLayout_6->addLayout(verticalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_4 = new QLabel(layoutWidget1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setMinimumSize(QSize(59, 20));
        label_4->setMaximumSize(QSize(59, 20));

        horizontalLayout_6->addWidget(label_4);

        lowByteLineEdit = new QLineEdit(layoutWidget1);
        lowByteLineEdit->setObjectName(QString::fromUtf8("lowByteLineEdit"));
        lowByteLineEdit->setMinimumSize(QSize(32, 20));
        lowByteLineEdit->setMaximumSize(QSize(32, 20));

        horizontalLayout_6->addWidget(lowByteLineEdit);


        verticalLayout_6->addLayout(horizontalLayout_6);


        horizontalLayout_9->addWidget(groupBox_3);

        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        readPushButton = new QPushButton(tab_2);
        readPushButton->setObjectName(QString::fromUtf8("readPushButton"));

        verticalLayout_10->addWidget(readPushButton);

        defaultPushButton = new QPushButton(tab_2);
        defaultPushButton->setObjectName(QString::fromUtf8("defaultPushButton"));

        verticalLayout_10->addWidget(defaultPushButton);

        writePushButton = new QPushButton(tab_2);
        writePushButton->setObjectName(QString::fromUtf8("writePushButton"));

        verticalLayout_10->addWidget(writePushButton);

        verticalSpacer = new QSpacerItem(20, 138, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_10->addItem(verticalSpacer);


        horizontalLayout_9->addLayout(verticalLayout_10);


        horizontalLayout_10->addLayout(horizontalLayout_9);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_12->addWidget(tabWidget);


        horizontalLayout_12->addLayout(verticalLayout_12);

        USBtinyISPGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(USBtinyISPGUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 541, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        USBtinyISPGUIClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(USBtinyISPGUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        USBtinyISPGUIClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionConfigure);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuTools->addAction(actionDevice_Info);
        menuTools->addSeparator();
        menuTools->addAction(actionConvertor);
        menuHelp->addAction(actionAbout);
        menuHelp->addSeparator();
        menuHelp->addAction(actionAbout_Qt);

        retranslateUi(USBtinyISPGUIClass);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(USBtinyISPGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *USBtinyISPGUIClass)
    {
        USBtinyISPGUIClass->setWindowTitle(QApplication::translate("USBtinyISPGUIClass", "USBtinyISP GUI", 0, QApplication::UnicodeUTF8));
        actionConfigure->setText(QApplication::translate("USBtinyISPGUIClass", "&Configure", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("USBtinyISPGUIClass", "&Exit", 0, QApplication::UnicodeUTF8));
        actionConvertor->setText(QApplication::translate("USBtinyISPGUIClass", "Convertor", 0, QApplication::UnicodeUTF8));
        actionDevice_Info->setText(QApplication::translate("USBtinyISPGUIClass", "Device Info", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("USBtinyISPGUIClass", "About", 0, QApplication::UnicodeUTF8));
        actionAbout_Qt->setText(QApplication::translate("USBtinyISPGUIClass", "About Qt", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("USBtinyISPGUIClass", "Atmel Device:", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("USBtinyISPGUIClass", "Action:", 0, QApplication::UnicodeUTF8));
        programRadioButton->setText(QApplication::translate("USBtinyISPGUIClass", "Program Memory", 0, QApplication::UnicodeUTF8));
        erraseRadioButton->setText(QApplication::translate("USBtinyISPGUIClass", "Erase Memory", 0, QApplication::UnicodeUTF8));
        memoryComboBox->clear();
        memoryComboBox->insertItems(0, QStringList()
         << QApplication::translate("USBtinyISPGUIClass", "Flash", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("USBtinyISPGUIClass", "EEPROM", 0, QApplication::UnicodeUTF8)
        );
        selectFileGroupBox->setTitle(QApplication::translate("USBtinyISPGUIClass", "Select File:", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("USBtinyISPGUIClass", "HEX File:", 0, QApplication::UnicodeUTF8));
        openPushButton->setText(QApplication::translate("USBtinyISPGUIClass", "Open", 0, QApplication::UnicodeUTF8));
        startPushButton->setText(QApplication::translate("USBtinyISPGUIClass", "Start", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("USBtinyISPGUIClass", "Programmer", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("USBtinyISPGUIClass", "High Byte", 0, QApplication::UnicodeUTF8));
        checkBox_1->setText(QApplication::translate("USBtinyISPGUIClass", "OCDEN", 0, QApplication::UnicodeUTF8));
        checkBox_2->setText(QApplication::translate("USBtinyISPGUIClass", "JTAGEN", 0, QApplication::UnicodeUTF8));
        checkBox_3->setText(QApplication::translate("USBtinyISPGUIClass", "SPIEN", 0, QApplication::UnicodeUTF8));
        checkBox_4->setText(QApplication::translate("USBtinyISPGUIClass", "CKOPT", 0, QApplication::UnicodeUTF8));
        checkBox_5->setText(QApplication::translate("USBtinyISPGUIClass", "EESAVE", 0, QApplication::UnicodeUTF8));
        checkBox_6->setText(QApplication::translate("USBtinyISPGUIClass", "BOOTSZ1", 0, QApplication::UnicodeUTF8));
        checkBox_7->setText(QApplication::translate("USBtinyISPGUIClass", "BOOTSZ0", 0, QApplication::UnicodeUTF8));
        checkBox_8->setText(QApplication::translate("USBtinyISPGUIClass", "BOOTRST", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("USBtinyISPGUIClass", "Value: 0x", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("USBtinyISPGUIClass", "Low Byte", 0, QApplication::UnicodeUTF8));
        checkBox_9->setText(QApplication::translate("USBtinyISPGUIClass", "BODLEVEL", 0, QApplication::UnicodeUTF8));
        checkBox_10->setText(QApplication::translate("USBtinyISPGUIClass", "BODEN", 0, QApplication::UnicodeUTF8));
        checkBox_11->setText(QApplication::translate("USBtinyISPGUIClass", "SUT1", 0, QApplication::UnicodeUTF8));
        checkBox_12->setText(QApplication::translate("USBtinyISPGUIClass", "SUT0", 0, QApplication::UnicodeUTF8));
        checkBox_13->setText(QApplication::translate("USBtinyISPGUIClass", "CKSEL3", 0, QApplication::UnicodeUTF8));
        checkBox_14->setText(QApplication::translate("USBtinyISPGUIClass", "CKSEL2", 0, QApplication::UnicodeUTF8));
        checkBox_15->setText(QApplication::translate("USBtinyISPGUIClass", "CKSEL1", 0, QApplication::UnicodeUTF8));
        checkBox_16->setText(QApplication::translate("USBtinyISPGUIClass", "CKSEL0", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("USBtinyISPGUIClass", "Value: 0x", 0, QApplication::UnicodeUTF8));
        readPushButton->setText(QApplication::translate("USBtinyISPGUIClass", "Read", 0, QApplication::UnicodeUTF8));
        defaultPushButton->setText(QApplication::translate("USBtinyISPGUIClass", "Default", 0, QApplication::UnicodeUTF8));
        writePushButton->setText(QApplication::translate("USBtinyISPGUIClass", "Write", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("USBtinyISPGUIClass", "Fuse Editor", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("USBtinyISPGUIClass", "File", 0, QApplication::UnicodeUTF8));
        menuTools->setTitle(QApplication::translate("USBtinyISPGUIClass", "Tools", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("USBtinyISPGUIClass", "Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class USBtinyISPGUIClass: public Ui_USBtinyISPGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USBTINYISPGUI_H
