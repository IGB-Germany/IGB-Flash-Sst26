
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

  //buffer
  uint8_t securityData[0x100];
  uint8_t address = 0;

  //address 0 - 0x07FF = 2048 len of data
  //Unique ID Pre-Programmed at factory address 0000 – 0007H
  //User Programmable address 0008H to 07FFH
  for (uint8_t i = 0; i < 8; i++)
  {
    Serial.print(F("Address:\t"));
    Serial.print(address + (i * 0x100));
    flashSst26.readSecurityData(address + (i * 0x100), securityData, 0x100);
    //Print page data
    printFlashSst26.printData(securityData, 0x100);
  }
}

void loop()
{

}
