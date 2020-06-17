//include guard
#ifndef PRINT_SERIAL_FLASH_SST26_H
#define PRINT_SERIAL_FLASH_SST26_H

//Print serial functions for Flash Memory SST26
//Version 0.3.0
//09.06.2020
//by IGB

//Class for Flash Memory SST26
#include "FlashSst26.h"

class PrintSerialFlashSst26
{
  public:
        
    //Flash specific print functions
    //Print id
    void printId(FlashSst26::id_t id);
    //Print register status
    void printRegisterStatus(FlashSst26::registerStatus_t registerStatus);
    //Print register configuration
    void printRegisterConfiguration(FlashSst26::registerConfiguration_t registerConfiguration);
    //Print register block protection
    void printRegisterBlockProtection(FlashSst26::registerBlockProtection_t registerBlockProtection);
    //Print unique id
    void printUniqueId(FlashSst26::uniqueId_t uniqueId);
    
    //Generic print functions
    //Print hex string
    void printHexStr(uint8_t str[], uint32_t len);
    //Print address
    void printAddress(uint32_t address);
    //Print lenData
    void printLenData(uint32_t lenData);
    //Print byte
    void printByte(uint8_t data);
    //Print page data
    void printData(uint8_t data[], uint32_t lenData, uint8_t bytesPerLine = 16);
    //Print Error message
    void printError(int error = 0);
    //Print message with uint32_t
    void printMessage(char message, uint32_t data, bool hexFormat = false);

};

#endif //PRINT_SERIAL_FLASH_SST26_H
