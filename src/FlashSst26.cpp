//Class for Flash Memory SST26
#include "FlashSst26.h"

FlashSst26::FlashSst26()
  : _comDriverSpi(2, 4000000)
{
  _address                  = 0;
  _id                       = {0xffffff, 0xff, 0xff, 0xff};
  _registerStatus           = {1, 1, 1, 1, 1, 1, 1, 1};
  _registerConfiguration    = {1, 1, 1, 1, 1, 1, 1, 1};
  _registerBlockProtection  = {0, 0, 0, 0, 0, 0};
  _uniqueId                 = {0xffffffff, 0xffffffff};

}

FlashSst26::FlashSst26(uint8_t slaveSelectPin)
  : _comDriverSpi(slaveSelectPin, 4000000)
{
  _address                  = 0;
  _id                       = {0xffffff, 0xff, 0xff, 0xff};
  _registerStatus           = {1, 1, 1, 1, 1, 1, 1, 1};
  _registerConfiguration    = {1, 1, 1, 1, 1, 1, 1, 1};
  _registerBlockProtection  = {0, 0, 0, 0, 0, 0};
  _uniqueId                 = {0xffffffff, 0xffffffff};
}

FlashSst26::FlashSst26(uint8_t slaveSelectPin, uint32_t  frequency)
  : _comDriverSpi(slaveSelectPin, frequency)
{
  _address                  = 0;
  _id                       = {0xffffff, 0xff, 0xff, 0xff};
  _registerStatus           = {1, 1, 1, 1, 1, 1, 1, 1};
  _registerConfiguration    = {1, 1, 1, 1, 1, 1, 1, 1};
  _registerBlockProtection  = {0, 0, 0, 0, 0, 0};
  _uniqueId                 = {0xffffffff, 0xffffffff};
}

bool FlashSst26::enableWrite(void)
{
  uint8_t cmd[1];

  cmd[0] = ENABLE_WRITE;

  _comDriverSpi.writeSpi(cmd, sizeof(cmd));

  return true;
}

bool FlashSst26::disableWrite(void)
{
  uint8_t cmd[1];

  cmd[0] = DISABLE_WRITE;

  _comDriverSpi.writeSpi(cmd, sizeof(cmd));

  return true;
}

FlashSst26::id_t FlashSst26::readId()
{
  uint8_t cmd[1];
  uint8_t data[3] = { 0xff };

  cmd[0] = READ_JEDEC_ID;

  _comDriverSpi.writeSpi(cmd, sizeof(cmd), ComDriverSpi::transferStart);
  _comDriverSpi.readSpi(data, sizeof(data), ComDriverSpi::transferEnd);

  _id.manufacturerId = data[0];
  _id.deviceType = data[1];
  _id.deviceId = data[2];
  _id.jedecId = ((unsigned long)data[0] << 16) | (data[1] << 8) | data[2];

  return _id;
}

FlashSst26::uniqueId_t FlashSst26::readUniqueId()
{
  uint8_t cmd[4];
  uint8_t data[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};

  cmd[0] = READ_SECURITY_DATA;
  cmd[1] = 0x00;//address
  cmd[2] = 0x00;//address
  cmd[3] = 0xff;//dummy

  _comDriverSpi.writeSpi(cmd, sizeof(cmd), ComDriverSpi::transferStart);
  _comDriverSpi.readSpi(data, sizeof(data), ComDriverSpi::transferEnd);

  _uniqueId.uniqueIdLower =  (uint32_t long) data[4] << 24
                             | (uint32_t long) data[5] << 16
                             | (uint32_t long) data[6] << 8
                             | (uint32_t long) data[7];

  _uniqueId.uniqueIdUpper =  (uint32_t long) data[0] << 24
                             | (uint32_t long) data[1] << 16
                             | (uint32_t long) data[2] << 8
                             | (uint32_t long) data[3];

  return _uniqueId;
}

FlashSst26::registerStatus_t FlashSst26::readRegisterStatus()
{
  uint8_t cmd[1];
  uint8_t data[1] = { 0xff };

  cmd[0] = READ_STATUS_REGISTER;

  _comDriverSpi.writeSpi(cmd, sizeof(cmd), ComDriverSpi::transferStart);
  _comDriverSpi.readSpi(data, sizeof(data), ComDriverSpi::transferEnd);

  _registerStatus.busy1            = data[0] & 1;
  _registerStatus.writeEnableLatch = data[0] >> 1 & 1;
  _registerStatus.suspendErase     = data[0] >> 2 & 1;
  _registerStatus.suspendProgram   = data[0] >> 3 & 1;
  _registerStatus.writeProtection  = data[0] >> 4 & 1;
  _registerStatus.securityId       = data[0] >> 5 & 1;
  _registerStatus.reserved1        = data[0] >> 6 & 1;
  _registerStatus.busy2            = data[0] >> 7 & 1;

  return _registerStatus;
}

FlashSst26::registerConfiguration_t FlashSst26::readRegisterConfiguration()
{
  uint8_t cmd[1];
  uint8_t data[1] = { 0xff };

  cmd[0] = READ_CONFIGURATION_REGISTER;

  _comDriverSpi.writeSpi(cmd, sizeof(cmd), ComDriverSpi::transferStart);
  _comDriverSpi.readSpi(data, sizeof(data), ComDriverSpi::transferEnd);

  _registerConfiguration.reserved1       = data[0] & 1;
  _registerConfiguration.ioConfiguration = data[0] >> 1 & 1;
  _registerConfiguration.reserved2       = data[0] >> 2 & 1;
  _registerConfiguration.blockProtectionVolatility = data[0] >> 3 & 1;
  _registerConfiguration.reserved3       = data[0] >> 4 & 1;
  _registerConfiguration.reserved4       = data[0] >> 5 & 1;
  _registerConfiguration.reserved5       = data[0] >> 6 & 1;
  _registerConfiguration.writeProtectionPin  = data[0] >> 7 & 1;

  return _registerConfiguration;
}

bool FlashSst26::writeRegisterConfiguration(registerConfiguration_t registerConfiguration)
{
  _registerConfiguration  = registerConfiguration;

  uint8_t cmd[3] = {0xff, 0xff, 0xff};

  cmd[0] = WRITE_STATUS_REGISTER;

  cmd[1] = 0;
  /*
    (unsigned char)_registerStatus.busy1 |
    (unsigned char)_registerStatus.writeEnableLatch << 1 |
    (unsigned char)_registerStatus.suspendErase << 2 |
    (unsigned char)_registerStatus.suspendProgram << 3 |
    (unsigned char)_registerStatus.writeProtection << 4 |
    (unsigned char)_registerStatus.securityId << 5 |
    (unsigned char)_registerStatus.reserved1 << 6 |
    (unsigned char)_registerStatus.busy2 << 7;
  */
  cmd[2] =
    (unsigned char)_registerConfiguration.reserved1 |
    (unsigned char)_registerConfiguration.ioConfiguration << 1 |
    (unsigned char)_registerConfiguration.reserved2 << 2 |
    (unsigned char)_registerConfiguration.blockProtectionVolatility << 3 |
    (unsigned char)_registerConfiguration.reserved3 << 4 |
    (unsigned char)_registerConfiguration.reserved4 << 5 |
    (unsigned char)_registerConfiguration.reserved5 << 6 |
    (unsigned char)_registerConfiguration.writeProtectionPin << 7;

  enableWrite();

  _comDriverSpi.writeSpi(cmd, sizeof(cmd));

  return true;
}

FlashSst26::registerBlockProtection_t FlashSst26::readRegisterBlockProtection()
{
  uint8_t cmd[1];
  uint8_t data[6] = { 0xff, 0xff, 0xff, 0xff, 0xff, 0xff };

  cmd[0] = READ_BP_REGISTER;

  _comDriverSpi.writeSpi(cmd, sizeof(cmd), ComDriverSpi::transferStart);
  _comDriverSpi.readSpi(data, sizeof(data), ComDriverSpi::transferEnd);

  _registerBlockProtection.adressRange0 = data[0];
  _registerBlockProtection.adressRange1 = data[1];
  _registerBlockProtection.adressRange2 = data[2];
  _registerBlockProtection.adressRange3 = data[3];
  _registerBlockProtection.adressRange4 = data[4];
  _registerBlockProtection.adressRange5 = data[5];

  return _registerBlockProtection;
}

bool FlashSst26::writeRegisterBlockProtection(registerBlockProtection_t registerBlockProtection)
{
  _registerBlockProtection = registerBlockProtection;

  uint8_t data[7];

  data[0] = WRITE_BP_REGISTER;
  data[1] = _registerBlockProtection.adressRange0;
  data[2] = _registerBlockProtection.adressRange1;
  data[3] = _registerBlockProtection.adressRange2;
  data[4] = _registerBlockProtection.adressRange3;
  data[5] = _registerBlockProtection.adressRange4;
  data[6] = _registerBlockProtection.adressRange5;

  enableWrite();

  _comDriverSpi.writeSpi(data, sizeof(data));

  /*retry until device not busy anymore*/
  for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
  {
    if (!isBusy()) break;
    if (retry == MAX_RETRY)return false;
  }

  return true;
}

bool FlashSst26::writeByte(uint32_t adressStart, uint8_t data[])
{
  uint8_t cmd[5];

  cmd[0] = WRITE_DATA;
  cmd[1] = adressStart >> 16 & 0xFF;
  cmd[2] = adressStart >> 8 & 0xFF;
  cmd[3] = adressStart & 0xFF;
  cmd[4] = data[0];

  enableWrite();

  _comDriverSpi.writeSpi(cmd, sizeof(cmd));

  /*retry until device not busy anymore*/
  for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
  {
    if (!isBusy()) break;
    if (retry == MAX_RETRY)return false;
  }
  return true;
}



bool FlashSst26::writePage(uint32_t addressStart, uint8_t page[])
{
  /*Adress has to start at begin of page*/
  //if (addressStart % _sizePage != 0) return false;

  /*Adress has to start at begin of page*/
  addressStart = addressStart & 0xFFFFFF00;

  /*
    Serial.print(F("Address: "));
    Serial.println(adressStart, HEX);
    uint16_t i = 0;
     while(i < 0x100)
    {
      Serial.print(page[i], HEX);
      Serial.print(F(" "));
      i++;
    }
  */

  uint8_t cmd[4];

  cmd[0] = WRITE_DATA;
  cmd[1] = addressStart >> 16 & 0xFF;
  cmd[2] = addressStart >> 8 & 0xFF;
  cmd[3] = addressStart & 0xFF;

  enableWrite();

  _comDriverSpi.writeSpi(cmd, sizeof(cmd), ComDriverSpi::transferStart);
  _comDriverSpi.writeSpi(page, SIZE_PAGE, ComDriverSpi::transferEnd);

  /*retry until device not busy anymore*/
  for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
  {
    delay(durationWritePage);
    if (!isBusy()) break;
    if (retry == MAX_RETRY)return false;
  }
  return true;
}


bool FlashSst26::writeData(uint32_t addressStart, uint8_t data[], uint32_t lenData)
{
  /*Adress has to start at begin of page*/
  if (addressStart % SIZE_PAGE != 0) return false;

  //position in data[]
  uint32_t position = 0;
  //number of buffers written
  uint16_t numBuffer = 0;

  /*
    Serial.println();
    Serial.println("Address:");
    Serial.print("Length:\t");
    Serial.print(F("0x"));
    Serial.println(lenData, HEX);
    Serial.print("Start:\t");
    Serial.print(F("0x"));
    Serial.println(addressStart, HEX);
    Serial.println();
  */
  //cycle trough array data[]
  while (position < lenData)
  {

    //create local buffer
    uint8_t buffer[SIZE_PAGE];
    //initalize local buffer with 0xff
    for (uint16_t i = 0; i < SIZE_PAGE; i++)buffer[i] = 0xff;

    //fill buffer
    for (uint16_t j = 0; j < SIZE_PAGE; j++)
    {
      //copy data in buffer
      buffer[j] = data[position];
      //next position in data[]
      position++;

      //end of data[] reached before buffer[] full
      if (position >= lenData)break;
    }
    //buffer full ..write page at right address...if not full write 0xff
    writePage(addressStart + numBuffer * SIZE_PAGE, buffer);

    //count buffers written for next page address
    numBuffer++;
  }
  return true;
}

void FlashSst26::readData(uint32_t adressStart, uint8_t data[], uint32_t lenData)
{
  //analyze lenData
  //nothing
  if (lenData == 0)
  {
    return;
  }

  //multiple bytes up to 0x100
  else if (lenData > 0 && lenData <= 0x100)
  {
    for(uint32_t i = 0; i< lenData; i++)  data[i] = 0xff;
    
    readBytes(adressStart, data, lenData);
  }

  //More than a page
  else if (lenData > 0x100)
  {
    uint8_t numPages = 0;
    uint8_t modulo = lenData % SIZE_PAGE;

    //multiple pages
    if (modulo == 0)
    {
      numPages = lenData / SIZE_PAGE;
      for (uint8_t i = 0; i < numPages; i++)
      {
        for(uint32_t j = 0; j< lenData; j++)  data[j + i * SIZE_PAGE] = 0xff;
        //read page wise
        readPage(adressStart + i * SIZE_PAGE, data + i * SIZE_PAGE);
      }
    }

    //multiple pages plus some bytes
    else if (modulo != 0)
    {
      uint8_t restBytes = lenData - modulo;
      //subtract the restbytes
      numPages = (lenData - restBytes) / SIZE_PAGE;

      for (uint8_t i = 0; i < numPages; i++)
      {
        for(uint32_t j = 0; j< lenData; j++)  data[j + i * SIZE_PAGE] = 0xff;
        //read page wise
        readPage(adressStart + i * SIZE_PAGE, data + i * SIZE_PAGE);
      }

      //read restbytes
      for(uint32_t k = 0; k< restBytes; k++)  data[k + numPages * SIZE_PAGE] = 0xff;
      readBytes(adressStart + numPages * SIZE_PAGE, data + numPages * SIZE_PAGE, restBytes);
    }
  }
 
  //error
  else
  {
    return;
  }

}

void FlashSst26::readPage(uint32_t addressStart, uint8_t page[])
{
  uint8_t cmd[4];

  cmd[0] = READ_DATA;
  cmd[1] = addressStart >> 16 & 0xFF;
  cmd[2] = addressStart >> 8 & 0xFF;
  cmd[3] = addressStart & 0xFF;

  _comDriverSpi.writeSpi(cmd, sizeof(cmd), ComDriverSpi::transferStart);
  _comDriverSpi.readSpi(page, SIZE_PAGE, ComDriverSpi::transferEnd);

  //retry until device not busy anymore
  for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
  {
    if (!isBusy()) break;
    if (retry == MAX_RETRY)return;
  }
}

void FlashSst26::readBytes(uint32_t adressStart, uint8_t bytes[], uint16_t numBytes)
{  
  //nothing to read
  if (numBytes == 0) return;

  //initalize
  for (uint16_t i = 0; i < numBytes; i++) bytes[i] = {0xff};

  uint8_t cmd[4];

  cmd[0] = READ_DATA;
  cmd[1] = adressStart >> 16 & 0xFF;
  cmd[2] = adressStart >> 8 & 0xFF;
  cmd[3] = adressStart & 0xFF;

  _comDriverSpi.writeSpi(cmd, sizeof(cmd), ComDriverSpi::transferStart);
  _comDriverSpi.readSpi(bytes, numBytes, ComDriverSpi::transferEnd);

  //retry until device not busy anymore
  for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
  {
    if (!isBusy()) break;
    if (retry == MAX_RETRY)return;
  }

}

bool FlashSst26::erase4kByte(uint32_t addressStart)
{
  /*Adress has to start at begin of sector*/
  addressStart = addressStart & 0xFFFFF000;
  /*
    Serial.print(F("Address to Erase:\t0x"));
    Serial.println(addressStart, HEX);

    Serial.print(F("Sector to Erase:\t0x"));
    Serial.println(addressStart, HEX);
  */
  uint8_t cmd[4];

  cmd[0] = ERASE_4KB;
  cmd[1] = addressStart >> 16 & 0xFF;
  cmd[2] = addressStart >> 8 & 0xFF;
  cmd[3] = addressStart & 0xFF;

  enableWrite();

  _comDriverSpi.writeSpi(cmd, sizeof(cmd));

  /*retry until device not busy anymore*/
  for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
  {
    delay(durationEraseSector);
    if (!isBusy()) break;
    if (retry == MAX_RETRY)return false;
  }
  return true;
}

bool FlashSst26::erase8kByte(uint32_t addressStart)
{
  /*Adress has to start at begin of Block*/
  if (addressStart % 0x2000 != 0) return false;

  /*Adress has to start at begin of sector*/
  /*
    Serial.print(F("Address to Erase:\t0x"));
    Serial.println(addressStart, HEX);
    //addressStart = addressStart & 0xFFFFF000;
    Serial.print(F("Sector to Erase:\t0x"));
    Serial.println(addressStart, HEX);
  */

  uint8_t cmd[4];

  cmd[0] = ERASE_8KB;
  cmd[1] = addressStart >> 16 & 0xFF;
  cmd[2] = addressStart >> 8 & 0xFF;
  cmd[3] = addressStart & 0xFF;

  enableWrite();

  _comDriverSpi.writeSpi(cmd, sizeof(cmd));

  /*retry until device not busy anymore*/
  for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
  {
    delay(durationEraseSector);
    if (!isBusy()) break;
    if (retry == MAX_RETRY)return false;
  }

  return true;
}

bool FlashSst26::eraseAll()
{
  uint8_t cmd[1];

  cmd[0] = ERASE_ALL;

  enableWrite();

  _comDriverSpi.writeSpi(cmd, sizeof(cmd));

  /*retry until device not busy anymore*/
  for (uint8_t retry = 0; retry < MAX_RETRY; retry++)
  {
    delay(durationEraseAll);
    if (!isBusy()) break;
    if (retry == MAX_RETRY)return false;
  }

  return true;
}

uint8_t FlashSst26::readSecurityData(uint32_t addressStart)
{
  //User Programmable 0008H to 07FFH
  if (addressStart < 0x08 || addressStart > 0x07FF) addressStart = 0x08;

  uint8_t cmd[3];
  //buffer security data
  uint8_t securityData[1] = {0xff};

  cmd[0] = READ_SECURITY_DATA;
  cmd[1] = (addressStart) >> 8 & 0xff;
  cmd[2] = (addressStart) & 0xff;

  _comDriverSpi.writeSpi(cmd, sizeof(cmd), ComDriverSpi::transferStart);
  _comDriverSpi.readSpi(securityData, sizeof(securityData), ComDriverSpi::transferEnd);

  return securityData[0];
}

bool FlashSst26::writeSecurityData()
{
  uint32_t address = 8;
  uint8_t cmd[3];
  /*2040 bytes of security data available*/
  uint16_t const lenSecureData = 100;
  /*buffer security data*/
  uint8_t secureData[lenSecureData] = { 0 };
  /*initalize*/
  for (uint16_t i = 0; i < lenSecureData; i++) secureData[i] = 0xef;

  cmd[0] = WRITE_SECURITY_DATA;
  cmd[1] = address >> 8 & 0xff;
  cmd[2] = address & 0xff;

  enableWrite();

  _comDriverSpi.writeSpi(cmd, sizeof(cmd), ComDriverSpi::transferStart);
  _comDriverSpi.readSpi(secureData, sizeof(secureData), ComDriverSpi::transferEnd);

  return true;
}

bool FlashSst26::disableGlobalBlockProtection(void)
{
  uint8_t cmd[1];

  cmd[0] = DISABLE_GLOBAL_BP_REGISTER;

  enableWrite();

  _comDriverSpi.writeSpi(cmd, sizeof(cmd));

  return true;
}

bool FlashSst26::enableDeepPowerDown(void)
{
  uint8_t cmd[1];

  cmd[0] = ENABLE_DEEP_POWER_DOWN;

  _comDriverSpi.writeSpi(cmd, sizeof(cmd));

  return true;
}

bool FlashSst26::releaseDeepPowerDown(void)
{
  uint8_t cmd[4];

  cmd[0] = RELEASE_DEEP_POWER_DOWN;
  cmd[1] = 0xff;/*dummy*/
  cmd[2] = 0xff;/*dummy*/
  cmd[3] = 0xff;/*dummy*/

  _comDriverSpi.writeSpi(cmd, sizeof(cmd));

  return true;
}

void FlashSst26::reset(void)
{
  uint8_t cmd[1];

  cmd[0] = ENABLE_RESET;

  _comDriverSpi.writeSpi(cmd, sizeof(cmd));

  cmd[0] = RESET;

  _comDriverSpi.writeSpi(cmd, sizeof(cmd));

}

bool FlashSst26::isBusy(void)
{
  FlashSst26::readRegisterStatus();

  if (_registerStatus.busy1 == 1 ) return true;

  return false;
}

void FlashSst26::setFrequency(uint32_t frequency)
{
  if (frequency > 8000000) frequency = 8000000;
  _comDriverSpi.setFrequency(frequency);
}

uint32_t FlashSst26::getFrequency()
{
  return _comDriverSpi.getFrequency();
}

uint32_t FlashSst26::calculateCrc32(const void* data, uint32_t lenData, uint32_t previousCrc32)
{
  
  readData(_address, data, lenData);
  
  const uint32_t polynomial = 0xEDB88320;
  uint32_t crc = ~previousCrc32;
  uint8_t* current = (unsigned char*) data;

  while (lenData--)
  {
    crc ^= *current++;
    //all bits
    for (uint8_t j = 0; j < 8; j++)
    {
      //last bit is 1
      if (crc & 1)
        //shift and ^
        crc = (crc >> 1) ^ polynomial;
      //last bit is 0
      else
        //shift
        crc =  crc >> 1;
    }
  }
  return ~crc;
}
