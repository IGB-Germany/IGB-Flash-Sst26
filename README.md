IGB Arduino Library for SPI Flash Memory SST26WF
================================================

[*Datasheet Flash Memory SST26WF016BA*] (http://ww1.microchip.com/downloads/en/DeviceDoc/20005013D.pdf)

The SST26WF is a low voltage (1,8V) SPI based Flash Memory circuit.

This library allows the user to:

* Get various information about the memory (Ids, security data)
* Configuration of the memory (protection, speed, sleep)
* Read data from memory
* Write data to memory

Examples are included to get you started.

Repository Contents
-------------------

* **/examples** - Example sketches for the library (.ino). Run these from the Arduino IDE. 
* **/src** - Source files for the library (.cpp, .h).
* **keywords.txt** - Keywords from this library that will be highlighted in the Arduino IDE. 
* **library.properties** - General library properties for the Arduino package manager. 

Documentation
--------------
The library enables the following functions:
<hr>

#### General methods for class
<hr>

###### FlashSst26()
###### FlashSst26(uint8_t slaveSelectPin)
###### FlashSst26(uint8_t slaveSelectPin, uint32_t frequency)
	
<hr>

#### Get various information
<hr>

###### `readId()`
###### `readUniqueId()`
###### `readRegisterConfiguration()`
###### `readRegisterStatus()`
###### `readRegisterBlockProtection()`

<hr>



License Information
-------------------

This product is _**open source**_! 

Please review the LICENSE.md file for license information. 

If you have any questions or concerns on licensing, please contact igb@posteo.de.

Distributed as-is; no warranty is given.
