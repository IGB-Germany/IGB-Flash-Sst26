
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

  //change register value Write Enabled = 1
  flashSst26.enableWrite();
  printFlashSst26.printRegisterStatus(flashSst26.readRegisterStatus());
  Serial.println(F("Reset"));
  Serial.println();
  flashSst26.reset();
  //should be default register values Write Enabled = 0
  printFlashSst26.printRegisterStatus(flashSst26.readRegisterStatus());

}

void loop()
{

}
