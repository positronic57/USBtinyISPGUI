#
# Copyright (c) 2013 Goce Boshkovski
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License.
#
#

# Enable CCACHE use
#QMAKE_CXX = ccache g++

VERSION_MAJOR = 1
VERSION_MINOR = 0
VERSION_RELEASE = 0

QMAKE_CXX = g++
QMAKE_CXXFLAGS += "-fno-sized-deallocation"

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = USBtinyISPGUI

TEMPLATE = app

DEFINES += "APPLICATION_MAJOR_VERSION=$$VERSION_MAJOR" \
           "APPLICATION_MINOR_VERSION=$$VERSION_MINOR" \
           "APPLICATION_RELEASE_VERSION=$$VERSION_RELEASE"

#INCLUDEPATH += /usr/include/
#INCLUDEPATH += /usr/local/include

SOURCES += src/main.cpp \
    src/USBtinyISPGUI.cpp \
    src/confighandler.cpp \
    src/configuredialog.cpp \
    src/deviceinfodialog.cpp \
    src/shellcmdexecutor.cpp

HEADERS += src/USBtinyISPGUI.h \
    src/confighandler.h \
    src/configuredialog.h \
    src/deviceinfodialog.h \
    src/shellcmdexecutor.h

FORMS += src/USBtinyISPGUI.ui \
    src/configureDialog.ui \
    src/deviceinfodialog.ui

#LIBS += -L/usr/lib/x86_64-linux-gnu
#LIBS += -L/usr/local/lib
LIBS += -lpugixml -lusb

RESOURCES += resource.qrc


