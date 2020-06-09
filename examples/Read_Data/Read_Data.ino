
//Class for Flash Memory SST26
#include "FlashSst26.h"
//Create object
FlashSst26 flashSst26;

//Class for serial print functions
#include "printSerialFlashSst26.h"
//Create object
PrintSerialFlashSst26 printFlashSst26;

void setup()
{
  Serial.begin(9600);

  //address to read from
  uint32_t address = 0x1000;
  //data buffer 
  uint16_t lenData = 0x200;
  uint8_t data[lenData];


  /*
  //0 Byte - nothing
  flashSst26.readBytes(address, data, 0);
  printFlashSst26.printData(data, 0);
  
  //1 Byte - min
  flashSst26.readBytes(address, data, 1);
  printFlashSst26.printData(data, 1);

  //0xFF Byte - max
  flashSst26.readBytes(address, data, 0xFF);
  printFlashSst26.printData(data, 0xFF);

  //0x100 Byte - too much
  flashSst26.readBytes(address, data, 0x100);
  printFlashSst26.printData(data, 0x100);
 
  //1 Page
  flashSst26.readPage(address, data);
  printFlashSst26.printData(data, 0x100);
*/
  //1 Byte
  flashSst26.readData(address, data, 0x1);
  printFlashSst26.printData(data, 0x1);

  //1 Page + 1 Byte
  flashSst26.readData(address, data, 0x101);
  printFlashSst26.printData(data, 0x101);
  
  //2 Pages + 1 Byte
  flashSst26.readData(address, data, 0x201);
  printFlashSst26.printData(data, 0x201);

}

void loop()
{

}
