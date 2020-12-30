
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

  uint32_t addressStart = 0;
  const uint16_t LEN = 0x100;
  
  uint8_t testArray[LEN];
 
  Serial.println(F("Erasing data"));
  
  //Read state and save in local variable
  FlashSst26::registerBlockProtection_t regBlprot;
  regBlprot = flashSst26.readRegisterBlockProtection();
  //Disable protection
  flashSst26.disableGlobalBlockProtection();
  
  //Erase 4kBytes = 0x1000
  flashSst26.erase4kByte(addressStart);

  //write
  for(uint16_t i=0; i<LEN; i++) testArray[i] = i;
  Serial.println(F("Writing test array"));
  flashSst26.writeData(addressStart, testArray, LEN);
  
  Serial.println(F("Reading test array"));
  flashSst26.readData(addressStart, testArray, LEN);
  printFlashSst26.printData(testArray, LEN);
  
  Serial.println(F("Calculating CRC32"));
  Serial.println();
  
  uint32_t crc32 = 0;
  crc32 = flashSst26.readCrc32(addressStart, LEN);
  char charArray[] = "CRC32:";
  printFlashSst26.printMessage(charArray, crc32, true);
  if(crc32 == 0x29058C73) Serial.println(F("CRC32 correct"));

  //Erase 4kBytes = 0x1000
  flashSst26.erase4kByte(addressStart);
  
  flashSst26.readData(addressStart, testArray, LEN);
  printFlashSst26.printData(testArray, LEN);

  //Rewrite previous state
  flashSst26.writeRegisterBlockProtection(regBlprot);

}

void loop()
{

}
