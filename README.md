## Simple Avrdude GUI Front End

Simple Avrdude GUI Front End is a small application written
in Qt5 for programming Microchip AVR 8-bit microcontrollers using [avrdude tool](https://github.com/avrdudes/avrdude/)
and USB In-Circuit Programmers like: [USBtinyISP](http://learn.adafruit.com/usbtinyisp) and [Microchip MPLAB PICkit4](https://www.microchip.com/en-us/education/developer-help/learn-tools-software/programmers-debuggers/pickit4).

_Avrdude_ functions coverd in Simple avrdude GUI Front End:
- program/erase microcontroller flash/EEPROM;
- write/read fuse bits of AVR8 microcontroller.

Only the MCUs listed in the configuration file will appear in the application as posible target devices.
The same applies to the in-circuit programmers. An ISP must by listed in the configuration file to be available
in the application.
 
### Requirements
- [avrdude](https://github.com/avrdudes/avrdude/) version 5.5 or newer. Minumum v7.0 for support of _Microchip MPLAB PICkit 4_;
- an USB ISP for _Microchip AVR8 MCUs_ supported by _avrdude_ and defined in the configuration file.

### External Dependencies

For detecting the presence of an ISP programmer, the project relies on
legacy version 0.1 of [libusb]( https://libusb.info) library.
XML support done with [pugixml](https://pugixml.org/) library.

### Configuration

The configuration file is writen in XML format and it is located in the **config** subfolder.
It defines the  MCUs and ISPs  within the application and provides the locations of
the avrdude binary and configuration files. Application options are also stored there.

The file contains two main sections:
- general configuration entries realted to avrdude and a list of ISPs;
- a list of of AVR8 MCUs.

#### MCU Entry in Configuration File

Each MCU description defines the fuse bytes of the MCU and their default values. Presens of EEPROM on the MCU is
set with the value of the <EEPROM> tag.

#### ISP Definition in Configuration File

An ISP is defined as a _burner node_ under the _burners section_. The defitintion requires:
- ISP name (displayed in the application);
- _avrdude_ designation for the ISP;
- USB vendor ID and product ID assigned to the ISP.
The vendor ID and product ID should be unique for an USB device. Under Linux command line, they can be optained with the lsusb command.
They are used to detect the presence of the ISP before executing avrdude commands for the selected MCU.

A sample configuration file is distributed with the source code.

### Building the Application From Source on Linux

The external dipendencies are usually available in the repositories of all major Linux distrubutions.
In case of Ubuntu install the following packages:
```
  #sudo apt install libpugixml-dev libusb-0.1 libusb-dev
```
If the packages are not available, install the librires from the source code as described in the their documentation.

Load the project file in _Qt Creator_, correct the linker settings in the project file in case the external libraries are not installed in the default locations and build the project.

#### Building with CMake

Create  a new forlder for the build within the project folder:
```
  #mkdir build
```
Prepare for the build with cmake:
```
  #cd build
  #cmake ..
```
Use cmake argument _-DCMAKE_BUILD_TYPE=Debug_ for building a debug version. By default a release version will be build. 
Installation folder can be defined before the build with _-DCMAKE_INSTALL_PREFIX=destination_folder_ macro as cmake argument:
```
  #cmake -DCMAKE_INSTALL_PREFIX=~/tools ..
```
Start the build process with:
```
  #make
```

### Installation

Copy the binary file together with the ***config*** folder into the desired destination.

#### Installation with cmake install

After successfull build execute:
```
  #make install
```
Start the command with _sudo_ if your account does not have enough rights for writing in the destination folder.


### License

The code is licensed under GNU General Public License Version 2 (see the License file for details).

### WARNING:
The source is provided as is without any warranty. Use it on your own risk!
The author does not take any responsibility for the damage caused while using this software.

### DISCLAIMER: 
The code is a result of a hobby work and the author is not affiliated with any of the hardware/components/boards/tools manufacturers/creators mentioned in the code, documentation or the description of this project. All trademarks are the property of the respective owners.

