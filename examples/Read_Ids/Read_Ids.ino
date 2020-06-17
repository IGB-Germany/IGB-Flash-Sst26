
//Class for Flash Memory SST26
#include "FlashSst26.h"
//Create object
FlashSst26 flashSst26;

//Class for serial print functions
#include "PrintSerialFlashSst26.h"
//Create object
PrintSerialFlashSst26 printFlashSst26;

void setup()
{
  Serial.begin(9600);

  //Manufacturer Silicon Storage Technolgies = 0xBF
  //Device SST26WF016B/016BA = 0x51
  
  printFlashSst26.printId(flashSst26.readId());
  printFlashSst26.printUniqueId(flashSst26.readUniqueId());

}

void loop()
{

}
