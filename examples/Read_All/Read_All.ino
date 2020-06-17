
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
  printData(0x10000, 0x000003AC);
}

void loop()
{

}

void printData(uint32_t address, uint32_t lenData)
{
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
    printFlashSst26.printData(buffer, 0x100);
  }

  //is there a modulo ?
  if (modulo)
  {
    //initalize buffer with 0xff
    for (uint16_t i = 0; i < 0x100; i++) buffer[i] = 0xff;
    //read modulo
    flashSst26.readData(address +  numPages * 0x100, buffer, modulo);
    //print
    printFlashSst26.printData(buffer, modulo);
  }
}
