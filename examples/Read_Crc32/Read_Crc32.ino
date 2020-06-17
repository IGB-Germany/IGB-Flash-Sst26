
//Class for Flash Memory SST26
#include "FlashSst26.h"
//Create object
FlashSst26 flashSst26;

//Class for serial print functions
#include "printSerialFlashSst26.h"
//Create object
PrintSerialFlashSst26 printFlashSst26;

void printCrc32(uint32_t address, uint32_t lenData, bool printEnable = false);

void setup()
{
  Serial.begin(9600);

  //printCrc32(0x10000, 0x000003AC);
  //const uint32_t crc32TestArray = 0x8944b5ae;

  //printCrc32(0x00020000, 0x000016A4);
  //const uint32_t crc32BootloaderPatchFull = 0xa93227b5;
  
  //printCrc32(0x00030000, 0x00081704);
  //const uint32_t crc32FirmwareFm = 0x40fbbd93;

  //printCrc32(0x000C0000, 0x0007F4E8);
  //const uint32_t crc32FirmwareDab = 0xb5edae86;

  printCrc32(0x00140000, 0x000813CC);
  //const uint32_t crc32FirmwareAm = 0x375e4a88;
  
}

void loop()
{

}

void printCrc32(uint32_t address, uint32_t lenData, bool printEnable)
{
  //CRC32 value
  uint32_t crc32 = 0;
  //data buffer
  uint8_t buffer[0x100];
  //number of pages to check
  uint32_t numPages = 0;
  //calculate rest
  uint16_t modulo = lenData % 0x100;
  //subtract the rest
  numPages = (lenData - modulo) / 0x100;

  Serial.print(F("Number of full pages:\t"));
  Serial.println(numPages);
  Serial.print(F("Modulo:\t"));
  Serial.println(modulo);

  for (uint32_t page = 0; page < numPages; page++)
  {
    //initalize buffer with 0xff
    for (uint16_t i = 0; i < 0x100; i++) buffer[i] = 0xff;
    //read a page of data
    flashSst26.readData(address + page * 0x100, buffer, 0x100);
    //print a page of data
    if (printEnable) printFlashSst26.printData(buffer, 0x100);
    //calculate crc32
    crc32 = flashSst26.calculateCrc32(buffer, 0x100, crc32);
  }

  //is there a modulo ?
  if (modulo)
  {
    //initalize buffer with 0xff
    for (uint16_t i = 0; i < 0x100; i++) buffer[i] = 0xff;
    //read modulo
    flashSst26.readData(address +  numPages * 0x100, buffer, modulo);
    //print
    if (printEnable) printFlashSst26.printData(buffer, modulo);
    //calculate crc32
    crc32 = flashSst26.calculateCrc32(buffer, modulo, crc32);
  }

  Serial.print(F("CRC32:\t"));
  Serial.print(F("0x"));
  Serial.println(crc32, HEX);

}
