## USBtinyISPGUI

USBtinyISPGUI is a small [avrdude](https://github.com/avrdudes/avrdude/) GUI front-end written
in Qt5 for programming AVR 8-bit microcontrollers using [USBtinyISP](http://learn.adafruit.com/usbtinyisp) programmer
from Adafruit.

The following functions are implemented:
- program/erase microcontroller flash/EEPROM;
- write/read fuse bits of AVR8 microcontroller.

Only the MCUs listed in the configuration file will appear in the application as posible target devices.

 
### Requirements
- [avrdude](https://github.com/avrdudes/avrdude/) version 5.5 or newer;
- [USBTinyISP](http://learn.adafruit.com/usbtinyisp) programmer from Adafruit.

### External Dependencies

For detecting the presence of USBtinyISP programmer, the project relies on
legacy version 0.1 of [libusb]( https://libusb.info) library.
XML support done with [pugixml](https://pugixml.org/) library.

### Configuration

The configuration file is writen in XML format and it is located in the "config" subfolder.
If "config" subfolder is not present, the application  will start with an error message complaining about the missing configuration file.

The file contains two main sections: configuration entries realted to avrdude and list of AVR8 MCUs.
Each MCU description defines the fuse bytes of the MCU and their default values. Presens of EEPROM on the MCU is
set with the value of the <EEPROM> tag.

A sample configuration file is distributed with the source code.

### License

The code is licensed under GNU General Public License Version 2 (see the License file for details).

### WARNING:
The source is provided as is without any warranty. Use it on your own risk!
The author does not take any responsibility for the damage caused while using this software.

