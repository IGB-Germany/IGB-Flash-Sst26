
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
  
  Serial.println(F("Power Down!"));
  flashSst26.enableDeepPowerDown();
  printFlashSst26.printId(flashSst26.readId());
  Serial.println(F("Power Up!"));
  flashSst26.releaseDeepPowerDown();
  printFlashSst26.printId(flashSst26.readId());

}

void loop()
{

}
