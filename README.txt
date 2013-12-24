USBtinyISPGUI

USBtinyISPGUI is a small avrdude (http://savannah.nongnu.org/projects/avrdude/)
GUI front-end written in Qt4 for programming AVR 8-bit microcontrollers using USBtinyISP programmer 
from Adafruit (http://learn.adafruit.com/usbtinyisp).

The following functions are implemented:
- program/erase microcontroller flash;
- configure fuse bits of microcontroller.

The list of supported microcontroller is defined in
 XML configuration file.

Requirements:
- avrdude (http://savannah.nongnu.org/projects/avrdude/) version 5.5 or newer;
- libusb (used only to detect presents of the Adafruit USBTinyISP programer);
- USBTinyISP programmer from Adafruit (http://learn.adafruit.com/usbtinyisp).

Tested on Linux with Qt 4.8.1. It works on Windows OS with libusb integeration removed.

WARNING: 
The source is provided as it is without any warranty. Use it on your own risk!
The author does not take any responsibility for the damage caused while using this software.
