/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using MPLAB(c) Code Configurator

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  MPLAB(c) Code Configurator - pic24-dspic-pic32mm : v1.25
        Device            :  PIC24FJ128GA010
        Driver Version    :  2.00
    The generated drivers are tested against the following:
        Compiler          :  XC16 1.26
        MPLAB             :  MPLAB X 3.45
*/

/*
    (c) 2016 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#include "SST26WF016B_functions.h"

/*
                         Main application
 */
int main(void)
{
    // initialize the device
   
unsigned char Read_byte;
unsigned long Dest_address, tempdata1;
unsigned long m,i,j,k,highest_address, tempdatalong;
int check,tempcheck,status;
int tempdata;
unsigned char Read_Stat_Reg,devicedata ;
unsigned char Led_Stat, tempbyte1, tempbyte2;
unsigned char sec_id[2048];
unsigned char *pntrsec_id;
unsigned long counter;
unsigned int data_256[256];
unsigned int block_protection_6[6];

int n;
n=0;
   i=0;
 j=0;
 Led_Stat=0x00;
// Read_Stat_Reg=0x00;
 status=1;  //1 means memory/code works and 0 means fault has occured.
 check=0;  //keeps track of code progress.
 tempcheck=1;
//highest_address=0x3ffffff;
highest_address=0x1FFFF;
devicedata=0;

   
   int Manufacturer_Id=0x00;
    int Device_Id=0x00;
    int Device_Type=0x00;
      
    SYSTEM_Initialize();
    WP_SetHigh();
    Hold_SetHigh();
    
    /************* 1. Test Jedec ID *********/
 

SPI_Jedec_ID_Read(&Manufacturer_Id, &Device_Type, &Device_Id); 
 if ((Manufacturer_Id == 0xbf)&& (Device_Type==0x26) && (Device_Id==0x51)&&(status==1))
{check=(check + 1);}
else
{check=0;
status=0;}

LATA = check;

 		
/************* 2a. Page program whole chip using SPI protocol and verify its OK. *********/

 	i=0;
while (i<=255)
{
 data_256[i]=170;
	i++;
}
 	
SPI_WREN();

block_protection_6[0]=0x00;
block_protection_6[1]=0x00;
block_protection_6[2]=0x00;
block_protection_6[3]=0x00;
block_protection_6[4]=0x00;
block_protection_6[5]=0x00;

 SPI_WriteBlockProtection(&block_protection_6[0]);
  SPI_Wait_Busy();
  SPI_WREN();
 	
SPI_Chip_Erase();	//Erase the chip


SPI_Wait_Busy();
 i=0;
SPI_WREN();
		

 while(i<highest_address)
 {	SPI_WREN();
SPI_Page_Program(i, &data_256[0]);
	SPI_Wait_Busy();
	i=i+256;
}

	  	SPI_WREN();


  j=0;
 while(j<highest_address)
 {
	//	   SPI_Set_Burst(0x03);
	//	SPI_Read_Burst(j, 64); 			//verify that it got programmed.
	//	 	SPI_Wait_Busy();

	   SPI_HighSpeed_Read_Cont(j, 64, &data_256[0]);
		 for (i=0;i<64;i++)
		 {
		 	if (data_256[i]==170)
			{tempcheck&=1;
			}
			  else
			{ tempcheck=0;
			}
		  }

	j=j+64;
}


	  	if ((tempcheck == 1)&&(status==1))
		{check=(check+1);
		status=status&1;}
		else
		{status=0;}



LATA = check;

/************* 3a. Do Sector Erase and verify that the sector is erased *********/


	SPI_WREN();
	SPI_Sector_Erase(0);	//Do Sector Erase
	SPI_Wait_Busy();

        j=0;
 	while (j<(4096))
	{
    	SPI_WREN();
  		  SPI_HighSpeed_Read_Cont(j, 64, &data_256[0]);
	 for (k=0;k<63;k++)
		 {
		 	if (data_256[k]==0xff)			  // Verify that the values are correct
			{tempcheck&=1;}
			  else
			{ tempcheck=0;}
   		  }
   		  j=j+64;
	}

        j=4096;
 	while (j<(4096*2))
	{
    	SPI_WREN();
  	  SPI_HighSpeed_Read_Cont(j, 64, &data_256[0]);
	    for (k=0;k<63;k++)
		 {
		 	if (data_256[k]==0xAA)			  // Verify that the values are correct
			{tempcheck&=1;}
			  else
			{ tempcheck=0;}
   		  }
   		  j=j+64;
	}


	  	if ((tempcheck == 1)&&(status==1))
		{check=(check+1);
		status=status&1;}
		else
		{status=0;}


LATA = check;
/************* 4a. Block Erase and verify that the Block is erased *********/

	SPI_WREN();
	SPI_Block_Erase(0);	//Do Sector Erase
	SPI_Wait_Busy();

        j=0;
 	while (j<(0x2000))
	{
    	SPI_WREN();
  	  SPI_HighSpeed_Read_Cont(j, 64, &data_256[0]);
	   for (k=0;k<63;k++)
		 {
		 	if (data_256[k]==0xff)			  // Verify that the values are correct
			{tempcheck&=1;}
			  else
			{ tempcheck=0;}
   		  }
   		  j=j+64;
	}

        j=0x2000;
 	while (j<(0x3000))
	{
    	SPI_WREN();
    SPI_HighSpeed_Read_Cont(j, 64, &data_256[0]);
	    for (k=0;k<63;k++)
		 {
		 	if (data_256[k]==0xAA)			  // Verify that the values are correct
			{tempcheck&=1;}
			  else
			{ tempcheck=0;}
   		  }
   		  j=j+64;
	}


	  	if ((tempcheck == 1)&&(status==1))
		{check=(check+1);
		status=status&1;}
		else
		{status=0;}



LATA = check;
/************* 5a. Chip Erase and Verify Chip is erased*********/

	SPI_WREN();
	SPI_Chip_Erase();	//Do Sector Erase
	SPI_Wait_Busy();

        j=0;
 	while (j<highest_address)
	{
    	SPI_WREN();
  		  SPI_HighSpeed_Read_Cont(j, 64, &data_256[0]);
	 for (k=0;k<63;k++)
		 {
		 	if (data_256[k]==0xFF)			  // Verify that the values are correct
			{tempcheck&=1;}
			  else
			{ tempcheck=0;}
   		  }
   		  j=j+64;
	}

	  	if ((tempcheck == 1)&&(status==1))
		{check=(check+2);
		status=status&1;}
		else
		{status=0;}


LATA = check;
// Test Quad J-ID


        
if (status==0)
{check |= 0x80;}

    
    while (1)
    {
        // Add your application code
        LATA = check;
    }

    return -1;
}
/**
 End of File
*/