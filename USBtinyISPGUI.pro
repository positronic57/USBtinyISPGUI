#
# Copyright (c) 2013 Goce Boshkovski
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License.
#
#

# Enable CCACHE use
QMAKE_CXX = ccache g++

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QT += xml
TARGET = USBtinyISPGUI

TEMPLATE = app

SOURCES += main.cpp \
    USBtinyISPGUI.cpp \
    configuredialog.cpp \
    deviceinfodialog.cpp

HEADERS += USBtinyISPGUI.h \
    configuredialog.h \
    deviceinfodialog.h

FORMS += USBtinyISPGUI.ui \
    configureDialog.ui \
    deviceinfodialog.ui

INCLUDEPATH += /usr/include/

LIBS += -L/usr/lib/x86_64-linux-gnu/ \
    -lusb

RESOURCES += resource.qrc
