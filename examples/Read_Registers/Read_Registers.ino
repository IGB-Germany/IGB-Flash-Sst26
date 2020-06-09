
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

  printFlashSst26.printRegisterStatus(flashSst26.readRegisterStatus());
  printFlashSst26.printRegisterConfiguration(flashSst26.readRegisterConfiguration());
  printFlashSst26.printRegisterBlockProtection(flashSst26.readRegisterBlockProtection());

}

void loop()
{

}
