
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

  //total 0x07FF len of data !!
  //7 pages
  for (uint16_t page = 0; page < 7; page++)
  {
    Serial.print(F("Page: "));
    Serial.println(page);
    for (uint16_t i = 0; i < 0x100; i++)
    {
      securityData[i] = flashSst26.readSecurityData(i + page * 0x100);
    }
    //Print page data
    printFlashSst26.printData(securityData, 0x100);
  }
}

void loop()
{

}
