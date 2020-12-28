//Class for Flash Memory SST26
#include "FlashSst26.h"
//Create object
FlashSst26 flashSst26;

//Class for serial print functions
#include "printSerialFlashSst26.h"
//Create object
PrintSerialFlashSst26 printFlashSst26;

void printDataBuffered(uint32_t address, uint32_t lenData, uint16_t bufferSize = 0x200);

const uint32_t ADDRESS = 0x10000;
const uint32_t SIZE = 0x000003ACUL;
uint8_t data[SIZE];

void setup()
{
  Serial.begin(9600);
  
  //Print depends on size of buffer
  printDataBuffered(ADDRESS, SIZE);
 

  //read data
  //flashSst26.readData(ADDRESS, data, SIZE);
  //print data
  //printFlashSst26.printData(data, SIZE);

}

void loop()
{

}

void printDataBuffered(uint32_t address, uint32_t lenData, uint16_t bufferSize)
{
  uint8_t* buffer = new uint8_t[bufferSize];
  
  uint16_t PAGE_SIZE = 0x100;
  //data buffer
  //uint8_t buffer[PAGE_SIZE];
  
  //number of pages to check
  uint32_t numPages = 0;
  //calculate rest
  uint16_t modulo = lenData % PAGE_SIZE;
  //subtract the rest
  numPages = (lenData - modulo) / PAGE_SIZE;

  Serial.print(F("Number of full pages:\t"));
  Serial.println(numPages);
  Serial.print(F("Modulo:\t"));
  Serial.println(modulo);

  for (uint32_t page = 0; page < numPages; page++)
  {
    //initalize buffer with 0xff
    for (uint16_t i = 0; i < PAGE_SIZE; i++) buffer[i] = 0xff;
    //read a page of data
    flashSst26.readData(address + page * PAGE_SIZE, buffer, PAGE_SIZE);
    //print a page of data
    printFlashSst26.printData(buffer, PAGE_SIZE);
  }

  //is there a modulo ?
  if (modulo)
  {
    //initalize buffer with 0xff
    for (uint16_t i = 0; i < PAGE_SIZE; i++) buffer[i] = 0xff;
    //read modulo
    flashSst26.readData(address +  numPages * PAGE_SIZE, buffer, modulo);
    //print
    printFlashSst26.printData(buffer, modulo);
  }
    delete[] buffer;
}
