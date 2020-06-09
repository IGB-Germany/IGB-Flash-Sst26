IGB Flash SST26
========================================

[Flash Memory SST26WF016BA] http://ww1.microchip.com/downloads/en/DeviceDoc/20005013D.pdf
![Real Time Clock ](https://www.mouser.de/images/microcrystal/images/RV-3028-C7_series_t.jpg)

[*Application Manual*](https://www.microcrystal.com/fileadmin/Media/Products/RTC/App.Manual/RV-3028-C7_App-Manual.pdf)

The RV-3028-C7 is an extremely precise, extremely low power, highly configurable RTC. Under ideal conditions it runs at approximately 40nA with +/-5ppm per year of deviation (+/- 160 seconds worst case per year).
This library was originally forked from the [Sparkfun RV-1805 library](https://github.com/sparkfun/SparkFun_RV-1805_Arduino_Library), and costumized and enhanced to the RV-3028-C7.

This library allows the user to:

* Get various information
* Configure
* Read data
* Write data

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

#### General functions
<hr>

###### `begin()`
###### `is12Hour()`
###### `isPM()`
###### `set12Hour()`
###### `set24Hour()`

<hr>

#### Set Time functions
<hr>

###### `setTime(sec, min, hour, weekday, date, month, year);`
###### `setSeconds(value)`
###### `setMinutes(value)`
###### `setHours(value)`
###### `setWeekday(value)`
###### `setDate(value)`
###### `setMonth(value)`
###### `setYear(value)`
###### `setToCompilerTime()`

<hr>

#### Get Time functions
<hr>

Please call "updateTime()" before calling one of the other getTime functions.

###### `updateTime()`
###### `getSeconds()`
###### `getMinutes()`
###### `getHours()`
###### `getWeekday()`
###### `getDate()`
###### `getMonth()`
###### `getYear()`
###### `stringDateUSA()`
###### `stringDate()`
###### `stringTime()`
###### `stringTimeStamp()`

<hr>


License Information
-------------------

This product is _**open source**_! 

Please review the LICENSE.md file for license information. 

If you have any questions or concerns on licensing, please contact constantinkoch@outlook.com.

Distributed as-is; no warranty is given.
