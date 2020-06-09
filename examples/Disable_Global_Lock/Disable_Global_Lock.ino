
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

  
  //Read state and save in local variable
  FlashSst26::registerBlockProtection_t regBlprot;
  regBlprot = flashSst26.readRegisterBlockProtection();
  
  printFlashSst26.printRegisterBlockProtection(regBlprot);

  //Disable protection
  flashSst26.disableGlobalBlockProtection();
  printFlashSst26.printRegisterBlockProtection(flashSst26.readRegisterBlockProtection());

  //Rewrite previous state
  flashSst26.writeRegisterBlockProtection(regBlprot);
  printFlashSst26.printRegisterBlockProtection(flashSst26.readRegisterBlockProtection());

}

void loop()
{

}
