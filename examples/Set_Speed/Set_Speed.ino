
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

  Serial.println(flashSst26.getFrequency());
  
  //Max Speed Arduino: 8MHz
  flashSst26.setFrequency(100000000);
  
  Serial.println(flashSst26.getFrequency());

}

void loop()
{

}
