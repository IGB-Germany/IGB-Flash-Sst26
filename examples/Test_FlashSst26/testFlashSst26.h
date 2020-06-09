#ifndef TEST_FLASH_SST26_H
#define TEST_FLASH_SST26_H

/*Forward Declaration*/
//class FlashSst26;

/*Use of uint8_t*/
#include "Arduino.h"

void test_sequence();

void test_readIds();
void test_powerDownUp();
void test_reset();

void test_readRegisterStatus();
void test_readRegisterConfiguration();
void test_readRegisterBlockProtection();

void test_writeRegisterConfiguration();
void test_writeRegisterBlockProtection();

void test_disableGlobalBlockProtection();
void test_erase(uint32_t address);

void test_readPage(uint32_t address);
void test_readPages(uint32_t address, uint32_t number);

void test_writePage(uint32_t address);
void test_writePages(uint32_t address, uint32_t number);

void test_readDataSecurity(uint8_t lenDataSec, uint32_t address);
void test_writeDataSecurity(uint8_t lenDataSec, uint16_t address = 0x08);

void test_readData(uint32_t lenData, uint32_t address);
void test_writeData(uint32_t lenData, uint32_t address);

void test_writeBytes(uint8_t lenData, uint32_t address);

#endif /*TEST_FLASH_SST26_H*/
