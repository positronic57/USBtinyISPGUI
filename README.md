## USBtinyISPGUI

USBtinyISPGUI is a small [avrdude](http://savannah.nongnu.org/projects/avrdude/) GUI front-end written 
originally in Qt4 for programming AVR 8-bit microcontrollers using [USBtinyISP](http://learn.adafruit.com/usbtinyisp) programmer
from Adafruit.

The following functions are implemented:
- program/erase microcontroller flash/EEPROM;
- configure fuse bits of microcontroller.

The list of supported microcontroller is defined in XML configuration file.
 
### Requirements
- [avrdude] (http://savannah.nongnu.org/projects/avrdude/) version 5.5 or newer;
- libusb (used only to detect presents of the Adafruit USBTinyISP programer.);
- [USBTinyISP](http://learn.adafruit.com/usbtinyisp) programmer from Adafruit.

### Build Requirements and Installation

The latest version of USBtinlyISPGUI is written and build using Qt 5.10.1.

#### External dependencies

For detecting the presents of the MCU programmer, the project realays on libusb library.

#### Installation

After building the binary for example in Qt Creator copy the executable in the desired destination
together with the the "config" folder. 

### Configuration

The configuration file is writen in XML format and it is located in the "config" subfolder.
If "config" subfolder is not present, the application  will start with an error message complaining about the missing configuration file.

The file contains two main sections: configuration entries realted to avrdude and list of supported AVR8 MCUs.
Each MCU description defines the fuse bytes of the MCU and their default values. Presens of EEPROM on the MCU is
set with the value of the <EEPROM> tag.

A sample configuration file is distributed with the source code.


### Supported platforms

Tested on Linux with Qt 5.10.1 and libusb installed.
Windows OS supported only without libusb integeration.

### License

The code is licensed under GNU General Public License Version 2 (see the License file for details).

### WARNING:
The source is provided as it is without any warranty. Use it on your own risk!
The author does not take any responsibility for the damage caused while using this software.

