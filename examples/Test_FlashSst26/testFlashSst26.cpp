/*Test functions*/
#include "testFlashSst26.h"
/*Test data*/
#include "testData.h"

/*Print functions*/
#include "printSerialFlashSst26.h"
/*Create object*/
PrintSerialFlashSst26 printFlashSst26;

/*Functions for Flash Memory SST26*/
#include "FlashSst26.h"

/*Create object*/
//FlashSst26 flashSst26;//ok default 2
//FlashSst26 flashSst26();//not working
//FlashSst26 flashSst26(2);//ok
FlashSst26 flashSst26(2, 4000000);//ok

void test_sequence()
{
  test_reset();//ok
  test_readIds();//ok
  test_powerDownUp();//ok

  test_readRegisterStatus();//ok
  test_readRegisterConfiguration();//ok
  test_readRegisterBlockProtection();//ok

  //test_writeRegisterConfiguration();//ok
  //test_writeRegisterBlockProtection();//ok

  //test_disableGlobalBlockProtection();//ok
  //test_erase(1000);//ok

  //test_readDataSecurity(0,100);//ok
  //test_writeDataSecurity(0,100);//careful OTP

  //Read Tests
  
  //0 Byte - nothing
  //test_readData(0x0, 0x10000);//ok
  //1 Byte - min
  //test_readData(0x1, 0x10000);//ok
  
  //test_readData(0x100, 0x10000);//1 Page
  
  //test_readData(0x101, 0x10000);//1 Page + 1 Byte
  
  //test_readData(0x104, 0x10000);//1 Page + 4 Bytes

  //test_readData(0x500, 0xFFF0);//Offset -1


  //Write tests

  //0 Byte - nothing
  //test_writeBytes(0, 0);//ok
  //1 Byte - min
  //test_writeBytes(1, 0);//ok
  //256 Bytes - max
  //test_writeBytes(255, 0);//ok
  //256 Bytes - too many
  //test_writeBytes(256, 0);//ok

  //0 - first
  //test_writePage(0x0000);//ok
  //10 - wrong address
  //test_writePage(10);//ok

  //4 pages
  //test_writePages(0x0000, 4);//ok


  //0 Bytes - Nothing
  //test_writeData(0, 0);//ok
  //1 Byte - Min
  //test_writeData(0x1, 0);//ok
  //255 Bytes
  //test_writeData(255, 0);//ok
  //1 Page
  //test_writeData(256, 0);//ok
  //1 Page + 1 Byte
  //test_writeData(257, 0);//ok
  //4 Page + 1 Byte
  //test_writeData(0x401, 0);//ok

  //Offset address 23 Bytes
  //test_writeData(23, 100);//ok

}

void test_writeData(uint32_t lenData, uint32_t address)
{
  //buffer too big for arduino
  if (lenData > 0x500) return;

  uint8_t data[lenData];
  //set to 0xff
  for (uint32_t i = 0; i < lenData; i++) data[i] = 0xAA;

  flashSst26.writeData(data, lenData, address);
  printFlashSst26.printData(data, lenData);

}

/*
  void test_writeData(uint32_t lenData, uint32_t address)
  {
  uint8_t data[lenData];
  //set to value
  for (uint32_t i = 0; i < lenData; i++) data[i] = 0xAA;

  flashSst26.disableGlobalBlockProtection();

  //erase every 4kB
  flashSst26.erase4kByte(addressTestArray);

  //flashSst26.writeData(addressTestArray, testArray, sizeTestArray);

  //flashSst26.readData(address, lenData);
  }
*/

void test_writePages(uint32_t address, uint32_t number)
{
  for (uint32_t i = 0; i < number; i++)
  {
    test_writePage(address);
    address = address + 0x100;
  }
}

void test_writePage(uint32_t address)
{
  //create local object
  uint16_t lenData = 0x100;
  uint8_t data[lenData];
  for (uint16_t i = 0; i < lenData; i++)
  {
    data[i] = 0x22;
  }

  flashSst26.disableBlockProtection();
  flashSst26.erase4kByte(address);

  flashSst26.writeData(data, lenData, address);
  flashSst26.readData(data, lenData, address);
  printFlashSst26.printData(data, lenData);

}

void test_writeBytes(uint8_t lenData, uint32_t address)
{
  uint8_t data[lenData];
  //set to value
  for (uint8_t i = 0; i < lenData; i++) data[i] = 0xAA;

  flashSst26.disableBlockProtection();

  flashSst26.erase4kByte(address);

  flashSst26.writeData(data, lenData, address);

  flashSst26.readData(data, lenData, address);
  printFlashSst26.printData(data, lenData);

}

void test_readData(uint32_t lenData, uint32_t address)
{
  //buffer too big for arduino
  if (lenData > 0x500) return;

  uint8_t data[lenData];
  //set to 0xff
  for (uint32_t i = 0; i < lenData; i++) data[i] = 0xff;

  flashSst26.readData(data, lenData, address);
  printFlashSst26.printData(data, lenData);

}


void test_writeDataSecurity(uint8_t lenDataSec, uint16_t address)
{
  uint8_t data[lenDataSec];
  for (uint16_t i = 0; i < lenDataSec; i++) data[i] = 0x11;

  flashSst26.writeSecurityData(data, lenDataSec, address);

  printFlashSst26.printData(data, lenDataSec);
}


void test_readDataSecurity(uint8_t lenDataSec, uint32_t address)
{
  uint8_t data[lenDataSec];
  for (uint32_t i = 0; i < lenDataSec; i++) data[i] = 0xff;

  flashSst26.readSecurityData(data, lenDataSec, address);

  printFlashSst26.printData(data, lenDataSec);
}

void test_writeRegisterConfiguration()
{
  FlashSst26::registerConfiguration_t registerConfiguration;

  registerConfiguration = {0, 1, 0, 0, 0, 0, 0, 0};
  flashSst26.writeRegisterConfiguration(registerConfiguration);
  printFlashSst26.printRegisterConfiguration(flashSst26.readRegisterConfiguration());

  registerConfiguration = {0, 0, 0, 0, 0, 0, 0, 0};
  flashSst26.writeRegisterConfiguration(registerConfiguration);
  printFlashSst26.printRegisterConfiguration(flashSst26.readRegisterConfiguration());
}

void test_writeRegisterBlockProtection()
{
  FlashSst26::registerBlockProtection_t registerBlockProtection;

  registerBlockProtection = {152, 1, 51, 0, 1, 255};
  flashSst26.writeRegisterBlockProtection(registerBlockProtection);
  printFlashSst26.printRegisterBlockProtection(flashSst26.readRegisterBlockProtection());

  registerBlockProtection = {0, 0, 0, 0, 0, 0};
  flashSst26.writeRegisterBlockProtection(registerBlockProtection);
  printFlashSst26.printRegisterBlockProtection(flashSst26.readRegisterBlockProtection());

}

void test_erase(uint32_t address)
{
  //create local object
  uint16_t pageSize = 0x100;
  uint8_t testPage[pageSize];
  for (unsigned short i = 0; i < pageSize; i++)
  {
    testPage[i] = 0xA1;
  }

  flashSst26.disableBlockProtection();
  flashSst26.erase4kByte(address);
  flashSst26.writeData(testPage, pageSize, address);

  for (unsigned short i = 0; i < pageSize; i++)
  {
    testPage[i] = 0xFF;
  }

  flashSst26.readData(testPage, pageSize, address);
  printFlashSst26.printData(testPage, pageSize);
  /*
    flashSst26.erase4kByte(address);
    flashSst26.readPage(address, pageSize);
    printFlashSst26.printData(testPage, pageSize);
  */
}

void test_readPage(uint32_t address)
{
  //create local object
  uint16_t sizePage = 0x100;
  uint8_t data[sizePage];
  //initalize to 0xff
  for (uint16_t i = 0; i < sizePage; i++)
  {
    data[i] = 0xff;
  }

  flashSst26.readData(data, sizePage, address);
  printFlashSst26.printData(data, sizePage);
}

void test_readPages(uint32_t address, uint32_t number)
{
  for (uint32_t i = 0; i < number; i++)
  {
    test_readPage(address);
    address = address + 0x100;
  }
}

/*
  void test_writePage(uint32_t address)
  {
  //create local object
  unsigned short testDataLen = 0x100;
  unsigned char testData[testDataLen];
  for (unsigned short i = 0; i < testDataLen; i++)
  {
    testData[i] = 0x22;
  }

  printFlashSst26.printAddress(address);

  flashSst26.disableGlobalBlockProtection();
  flashSst26.erase4kByte(address);

  flashSst26.writePage(address, testData);
  flashSst26.readData(testData, testDataLen, address);
  printFlashSst26.printData(testData, testDataLen);

  flashSst26.erase4kByte(address);
  flashSst26.readData(testData, testDataLen, address);
  printFlashSst26.printData(testData, testDataLen);
  }
*/


void test_disableGlobalBlockProtection()
{
  flashSst26.disableBlockProtection();
  printFlashSst26.printRegisterBlockProtection(flashSst26.readRegisterBlockProtection());
}

void test_reset()
{
  Serial.println(F("test_reset()"));
  //Change config register
  printFlashSst26.printRegisterConfiguration(flashSst26.readRegisterConfiguration());
  flashSst26.reset();
  //should be default config register values
  printFlashSst26.printRegisterConfiguration(flashSst26.readRegisterConfiguration());
}

void test_readIds()
{
  printFlashSst26.printId(flashSst26.readId());
  printFlashSst26.printUniqueId(flashSst26.readUniqueId());
}

void test_readRegisterStatus()
{
  printFlashSst26.printRegisterStatus(flashSst26.readRegisterStatus());
}

void test_readRegisterConfiguration()
{
  printFlashSst26.printRegisterConfiguration(flashSst26.readRegisterConfiguration());
}

void test_readRegisterBlockProtection()
{
  printFlashSst26.printRegisterBlockProtection(flashSst26.readRegisterBlockProtection());
}

void test_powerDownUp()
{
  flashSst26.enableDeepPowerDown();
  printFlashSst26.printId(flashSst26.readId());
  flashSst26.releaseDeepPowerDown();
  printFlashSst26.printId(flashSst26.readId());
}
