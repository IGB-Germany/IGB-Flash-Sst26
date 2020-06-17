//use of sprintf
#include "Arduino.h"

#include "PrintSerialFlashSst26.h"

void PrintSerialFlashSst26::printId(FlashSst26::id_t id)
{
  Serial.println(F("Flash Ids"));
  Serial.print(F("Jedec Id:\t"));
  Serial.println(id.jedecId, HEX);
  Serial.print(F("Manufacturer Id:"));
  Serial.println(id.manufacturerId, HEX);
  Serial.print(F("Device Type:\t"));
  Serial.println(id.deviceType, HEX);
  Serial.print(F("Device Id:\t"));
  Serial.println(id.deviceId, HEX);
  Serial.println();
}

void PrintSerialFlashSst26::printRegisterStatus(FlashSst26::registerStatus_t registerStatus)
{
  Serial.println(F("Register Status"));
  Serial.print(F("Busy:\t\t"));
  Serial.println(registerStatus.busy1);
  Serial.print(F("Write Enable:\t"));
  Serial.println(registerStatus.writeEnableLatch);
  Serial.print(F("Suspend Erase:\t"));
  Serial.println(registerStatus.suspendErase);
  Serial.print(F("Suspend Program:"));
  Serial.println(registerStatus.suspendProgram);
  Serial.print(F("Protection Lock:"));
  Serial.println(registerStatus.writeProtection);
  Serial.print(F("Sec. Id Lock:\t"));
  Serial.println(registerStatus.securityId);
  Serial.print(F("Reserved:\t"));
  Serial.println(registerStatus.reserved1);
  Serial.print(F("Busy2:\t\t"));
  Serial.println(registerStatus.busy2);
  Serial.println();
}

void PrintSerialFlashSst26::printRegisterConfiguration(FlashSst26::registerConfiguration_t registerConfiguration)
{
  Serial.println(F("Register Configuration"));
  Serial.print(F("Res1:\t\t"));
  Serial.println(registerConfiguration.reserved1);
  Serial.print(F("IO Conf:\t"));
  Serial.println(registerConfiguration.ioConfiguration);
  Serial.print(F("Res2:\t\t"));
  Serial.println(registerConfiguration.reserved2);
  Serial.print(F("BP Volat.:\t"));
  Serial.println(registerConfiguration.blockProtectionVolatility);
  Serial.print(F("Res3:\t\t"));
  Serial.println(registerConfiguration.reserved3);
  Serial.print(F("Res4:\t\t"));
  Serial.println(registerConfiguration.reserved4);
  Serial.print(F("Res5\t\t"));
  Serial.println(registerConfiguration.reserved5);
  Serial.print(F("#WP Enable nV:\t"));
  Serial.println(registerConfiguration.writeProtectionPin);
  Serial.println();
}

void PrintSerialFlashSst26::printRegisterBlockProtection(FlashSst26::registerBlockProtection_t registerBlockProtection)
{
  Serial.println(F("Register Block Protection"));
  Serial.print(F("Range 0: "));
  Serial.println(registerBlockProtection.adressRange0, BIN);
  Serial.print(F("Range 1: "));
  Serial.println(registerBlockProtection.adressRange1, BIN);
  Serial.print(F("Range 2: "));
  Serial.println(registerBlockProtection.adressRange2, BIN);
  Serial.print(F("Range 3: "));
  Serial.println(registerBlockProtection.adressRange3, BIN);
  Serial.print(F("Range 4: "));
  Serial.println(registerBlockProtection.adressRange4, BIN);
  Serial.print(F("Range 5: "));
  Serial.println(registerBlockProtection.adressRange5, BIN);
  Serial.println();
}

void PrintSerialFlashSst26::printUniqueId(FlashSst26::uniqueId_t uniqueId)
{
  Serial.print(F("Unique Id:\t0x"));
  Serial.print(uniqueId.uniqueIdUpper, HEX);
  Serial.println(uniqueId.uniqueIdLower, HEX);
  Serial.println();
}

void PrintSerialFlashSst26::printHexStr(uint8_t buf[], uint32_t len)
{
  char string[16] = {0};
  if (len == 0) return;

  for (unsigned int i = 0; i < len; i++)
  {
    sprintf(string, "0x%02x ", buf[i]);
    Serial.print(string);
  }
  Serial.println();

}

void PrintSerialFlashSst26::printByte(uint8_t data)
{
  Serial.print(F("0x"));
  Serial.println(data, HEX);
}

void PrintSerialFlashSst26::printAddress(uint32_t address)
{
  Serial.println();
  Serial.print("Address: ");
  Serial.print(F("0x"));
  Serial.print(address, HEX);
}

void PrintSerialFlashSst26::printLenData(uint32_t lenData)
{
  Serial.println();
  Serial.print("Length of data: ");
  Serial.println(lenData);
  Serial.println();
}

void PrintSerialFlashSst26::printData(uint8_t data[], uint32_t lenData, uint8_t bytesPerLine)
{
  char string[4];
  uint8_t b = 0;
  unsigned short p = 0;

  for (uint32_t a = 0; a < lenData; a++)
  {
    snprintf(string, 4, "%02X ", data[a]);
    Serial.print(string);

    b++;
    p++;

    //Every bytes per line
    if (b == bytesPerLine)
    {
      Serial.println();
      b = 0;
    }
    //Every page
    if (p == 0x100)
    {
      Serial.println();
      p = 0;
    }
  }
  Serial.println();
  Serial.println();
}

void PrintSerialFlashSst26::printError(int error)
{
  Serial.print(F("Flash Error: "));
  Serial.println(error);
}

//Print message with uint32_t
void PrintSerialFlashSst26::printMessage(char message, uint32_t data, bool hexFormat)
{
  Serial.print(message);
  Serial.print(F("\t"));
  if (hexFormat)
  { Serial.print(F("0x"));
    Serial.print(data, HEX);
  }
  else
    Serial.print(data);
  Serial.println();
}
