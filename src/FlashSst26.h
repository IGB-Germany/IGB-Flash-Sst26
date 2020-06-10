//Include guard
#ifndef FLASH_SST26_H
#define FLASH_SST26_H

//Class for Flash Memory SST26
//Version 0.3.0
//06.09.2020
//Flash: 2234 Bytes
//RAM:   290 Bytes
//by IGB

//SPI communication layer
#include "ComDriverSpi.h"

class FlashSst26
{
    /*
      to do:
      New: return int errorCode for all functions
      New: printErrorCode
      Changed: writeData, readData accepts big array and chrashes

      Tested circuits: SST26WF016B

      Pining:

      PIN 1 CE#   Chip Enable
      PIN 2 SO    Serial Data Output To transfer data serially out of the device.
      PIN 3 WP#   Write Protect The Write Protect (WP#) pin is used to enable/disable BPL bit in the status register.
      PIN 4 VSS   Ground
      PIN 5 SI    Serial Data Input  To transfer commands, addresses, or data serially into the device.
      PIN 6 SCK   Serial Clock    To provide the timing of the serial interface.
      PIN 7 HOLD# Hold To temporarily stop serial communication with SPI flash memory without resetting the device.
      PIN 8 VDD   Power Supply

      SPI Mode: 0 (0,0), 3 (1,1)

      Read Speed: 40MHz
      Read High Speed: 104MHz
      Max Speed Arduino: 8MHz

      Supply Voltage: 1.65V - 1.95V

      Address: 0x000000 - 0x1FFFFF
      4 KByte erasable sectors

    */
  public:

    /*type id_t*/
    struct id_t
    {
      uint32_t jedecId;      /*0xBF2651*/
      uint8_t manufacturerId;/*0xBF*/
      uint8_t deviceType;   /*0x26*/
      uint8_t deviceId;     /*0x51*/
    };

    /*type uniqueId_t*/
    struct uniqueId_t
    {
      uint32_t uniqueIdUpper;//upper 64 bit
      uint32_t uniqueIdLower;//lower 64 bit
    };

    /*type registerStatus_t*/
    struct registerStatus_t
    {
      uint8_t busy1           : 1; /*read only*/
      uint8_t writeEnableLatch: 1; /*read only*/
      uint8_t suspendErase    : 1; /*read only*/
      uint8_t suspendProgram  : 1; /*read only*/
      uint8_t writeProtection : 1; /*read only*/
      uint8_t securityId      : 1; /*read only*/
      uint8_t reserved1       : 1; /*read only*/
      uint8_t busy2           : 1; /*read only*/
    };

    /*type registerConfiguration_t*/
    struct registerConfiguration_t
    {
      uint8_t reserved1                 : 1;/*read only*/
      uint8_t ioConfiguration           : 1;/*R/W*/
      uint8_t reserved2                 : 1;/*read only*/
      uint8_t blockProtectionVolatility : 1;/*read only*/ /*Default at power up 1*/
      uint8_t reserved3                 : 1;/*read only*/
      uint8_t reserved4                 : 1;/*read only*/
      uint8_t reserved5                 : 1;/*read only*/
      uint8_t writeProtectionPin        : 1;/*R/W non-volatile*/
    };

    //The default state after a power-on reset is write-protected BPR[47:0] = 5555 FFFF FFFF
    struct registerBlockProtection_t
    {
      uint8_t adressRange0;/*8 bit 0x010000 - 0x08FFFF*/
      uint8_t adressRange1;/*8 bit 0x090000 -*/
      uint8_t adressRange2;/*8 bit*/
      uint8_t adressRange3;/*8 bit*/
      uint8_t adressRange4;/*8 bit*/
      uint8_t adressRange5;/*8 bit*/
    };

    FlashSst26();
    FlashSst26(uint8_t slaveSelectPin);
    FlashSst26(uint8_t slaveSelectPin, uint32_t frequency);

    //Enable write
    bool enableWrite(void);
    //Disable write
    bool disableWrite(void);
    /*Read id*/
    id_t readId();
    /*Read unique id*/
    uniqueId_t readUniqueId();
    /*Read register status*/
    registerStatus_t readRegisterStatus();
    /*Read register configuration*/
    registerConfiguration_t readRegisterConfiguration();
    /*Read register block protection */
    registerBlockProtection_t readRegisterBlockProtection();
    
    /*Write register configuration*/
    bool writeRegisterConfiguration(registerConfiguration_t registerConfiguration);
    /*Write register block protection*/
    bool writeRegisterBlockProtection(registerBlockProtection_t registerBlockProtection);
    /*Disable Global Block Protection*/
    bool disableGlobalBlockProtection(void);
    /*Read security data*/
    uint8_t readSecurityData(uint32_t addressStart);
    /*Write security data*/
    bool writeSecurityData();
    /*Erase 4kBytes = 0x1000*/
    bool erase4kByte(uint32_t addressStart);
    /*
        Sector 4kByte
        Address bits
        [AMS:A12] determine the sector address (SAX)
        (AMS = Most Significant Address)
        Blocks are 64 KByte, 32 KByte, or 8KByte, depending on location
        AMS - A13 for 8 KByte
        AMS - A15 for 32 KByte
        AMS - A16 for 64 KByte
        Remaining addresses are dont care, but must be set to VIL or VIH
    */
    /*Erase 8kBytes = 0x2000*/
    bool erase8kByte(uint32_t addressStart);
    /*Erase 32kBytes = 0x8000*/
    bool erase32kByte(uint32_t addressStart);
    /*Erase 64kBytes = 0xFFFF*/
    bool erase64kByte(uint32_t addressStart);
    /*Erase all*/
    bool eraseAll(void);

    //Write
    bool writeByte(uint32_t adressStart, uint8_t data[]);
    bool writePage(uint32_t addressStart, uint8_t page[]);
    /*Write data pagewise*/
    bool writeData(uint32_t addressStart, uint8_t data[], uint32_t lenData);
    
    //Read data
    void readData(uint32_t adressStart, uint8_t data[], uint32_t lenData);
    void readPage(uint32_t adressStart, uint8_t page[]);
    void readBytes(uint32_t adressStart, uint8_t bytes[], uint16_t numBytes);

    uint32_t calculateCrc32(const void* data, uint32_t lenData, uint32_t previousCrc32);
    
    //Enable deep power down
    bool enableDeepPowerDown(void);
    //Release deep power down
    bool releaseDeepPowerDown(void);

    //Reset device
    void reset(void);

    /*Test if device is busy*/
    bool isBusy(void);

    //Set SPI frequency
    void setFrequency(uint32_t frequency);
    //Get SPI frequency
    uint32_t getFrequency();

  private:

    /*SPI communication driver class*/
    ComDriverSpi _comDriverSpi;

    //address we are working on
    uint32_t _address;
    
    //Size of buffer we are working on
    enum SIZE_PAGE {SIZE_PAGE = 0x100};
    
    //Max numbers of retry when chip is busy
    enum MAX_RETRY {MAX_RETRY = 10};

    //ids
    id_t                      _id;
    uniqueId_t                _uniqueId;
    
    //registers
    registerStatus_t          _registerStatus;
    registerConfiguration_t   _registerConfiguration;
    registerBlockProtection_t _registerBlockProtection;
    
    //security data
    uint8_t                   _securityData;

    //Durations in ms
    const uint8_t durationWritePage             = 2;
    const uint8_t durationWriteStatusRegister   = 10;

    const uint8_t durationEraseSector           = 18;
    const uint8_t durationEraseAll              = 35;

    const uint8_t durationWriteSecurityId       = 2;
    const uint8_t durationWriteSuspend          = 1;
    const uint8_t durationEnableWriteProtection = 25;

    //TR(o) Reset to Read (non-data operation) 20 ns
    //TR(p) Reset Recovery from Program or Suspend 100 μs
    //TR(e) Reset Recovery from Erase 1 ms

    /*Commands*/
    /*Configuration*/
    const uint8_t NO_OPERATION          = 0x00;
    const uint8_t DISABLE_WRITE         = 0x04;
    const uint8_t ENABLE_WRITE          = 0x06;

    const uint8_t READ_STATUS_REGISTER  = 0x05;
    const uint8_t WRITE_STATUS_REGISTER = 0x01;
    const uint8_t READ_CONFIGURATION_REGISTER   = 0x35;
    const uint8_t WRITE_CONFIGURATION_REGISTER  = 0x01;
    /*Identification*/
    const uint8_t READ_JEDEC_ID         = 0x9F;
    const uint8_t READ_JEDEC_ID_QUAD    = 0xAF;
    const uint8_t READ_SFDP             = 0x5A;
    /*Read*/
    const uint8_t READ_DATA             = 0x03;
    const uint8_t READ_DATA_FAST        = 0x0B;
    const uint8_t READ_DATA_QUAD        = 0x6B;
    const uint8_t READ_I_O_QUAD         = 0xEB;
    const uint8_t READ_DATA_DUAL        = 0x3B;
    const uint8_t READ_I_O_DUAL         = 0xBB;
    const uint8_t SET_BURST_LENGTH      = 0xC0;
    const uint8_t READ_BURST_QUAD       = 0x0C;
    const uint8_t READ_BURST            = 0xEC;
    /*Write*/
    const uint8_t WRITE_DATA            = 0x02;
    const uint8_t WRITE_DATA_PAGE_QUAD  = 0x32;
    /*Interrupt and resume erase or program operation*/
    const uint8_t WRITE_SUSPEND         = 0xB0;
    const uint8_t WRITE_RESUME          = 0x30;
    /*Erase*/
    const uint8_t ERASE_4KB             = 0x20;
    const uint8_t ERASE_8KB             = 0xD8;
    const uint8_t ERASE_32KB            = 0xD8;
    const uint8_t ERASE_64KB            = 0xD8;
    const uint8_t ERASE_ALL             = 0xC7;
    /*Protection*/
    const uint8_t READ_BP_REGISTER      = 0x72;
    const uint8_t WRITE_BP_REGISTER     = 0x42;
    const uint8_t LOCK_BP_REGISTER      = 0x8D;
    const uint8_t ENABLE_NON_VOLATILE_BP_REGISTER = 0xE8;
    const uint8_t DISABLE_GLOBAL_BP_REGISTER = 0x98;

    const uint8_t READ_SECURITY_DATA    = 0x88;
    const uint8_t WRITE_SECURITY_DATA   = 0xA5;
    const uint8_t LOCK_SECURITY_DATA    = 0x85;
    /*Power Saving*/
    const uint8_t ENABLE_DEEP_POWER_DOWN  = 0xB9;
    const uint8_t RELEASE_DEEP_POWER_DOWN = 0xAB;
    /*QPI*/
    const uint8_t ENTER_QPI             = 0x38;
    const uint8_t EXIT_QPI              = 0xFF;
    /*Reset*/
    const uint8_t ENABLE_RESET          = 0x66;
    const uint8_t RESET                 = 0x99;

};

#endif //FLASH_SST26_H
