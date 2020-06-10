
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
  uint32_t address = 0x10000;

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

  //0 Byte
  //data buffer
  uint8_t zero[1] = {0xff};
  flashSst26.readData(address, zero, 0);
  printFlashSst26.printData(zero, 0);


  //1 Byte
  //data buffer
  uint8_t bytes[1] = {0xff};
  flashSst26.readData(address, bytes, 1);
  printFlashSst26.printData(bytes, 1);


  //1 Page
  //data buffer
  uint8_t page[0x100];
  for (uint16_t i = 0; i < 0x100; i++)page[i] = 0xff;

  flashSst26.readData(address, page, 0x100);
  printFlashSst26.printData(page, 0x100);


  //2 Pages + 1 Byte
  //data buffer
  uint16_t lenData = 0x201;
  uint8_t data[lenData];
  flashSst26.readData(address, data, lenData);
  printFlashSst26.printData(data, lenData);


  //Test CRC32
  uint32_t addressTestArray = 0x00010000;
  uint32_t sizeTestArray = 0x000003AC;
  uint32_t crc32TestArray = 0x8944b5ae;
  uint32_t crc32 = 0;


}

void loop()
{

}
