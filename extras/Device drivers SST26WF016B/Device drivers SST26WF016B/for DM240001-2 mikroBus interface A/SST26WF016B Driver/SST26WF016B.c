 /*Software Driver

SST26WF016B 16 Mbit(2M x 8) Serial Quad I/O (SQI) Flash Memory

October 10, 2013, Rev. 1.0

ABOUT THE SOFTWARE
This application note provides software driver examples for SST26WF016B,
Serial Flash. Extensive comments are included in each routine to describe
the function of each routine.  The interface coding uses polling method
rather than the SPI protocol to interface with these serial devices.  The
functions are differentiated below in terms of the communication protocols
(uses Mode 0) and specific device operation instructions. 


ABOUT THE SST26WF016B

Companion product datasheets for the SST26WF016B should be reviewed in
conjunction with this application note for a complete understanding
of the device.


Device Communication Protocol(pinout related) functions:

Functions                    		Function
------------------------------------------------------------------
init					Initializes clock to set up mode 0.
Send_Byte				Sends one byte using SI pin to send and
					shift out 1-bit per clock rising edge
Get_Byte				Receives one byte using SO pin to receive and shift
					in 1-bit per clock falling edge

SendSQI_Byte		 Sends one byte using SI pin, SO pin, SIO2 pin and SIO3 pin to send and
					shift out 4-bit per clock rising edge

GetSQI_Byte			 Receives one byte using SI pin, SO pin, SIO2 pin and SIO3 pin to receive and shift
					in 4-bit per clock falling edge

Note:  The pin names of the SST26WF016B are used in this application note. The associated test code
will not compile unless these pinouts (SCK, SI, SO, SIO2, SIO3, CE) are pre-defined on your
software which should reflect your hardware interfaced.


Device Operation Instruction functions:

Functions                    		Function
------------------------------------------------------------------

NoOp				No Operation
RSTEN				Enables acceptance of the RST (Reset) operation command
RST					Resets the device in to normal operating Ready mode
EQIO				Enables Quad I/O operation
RSTQIO				Resets the device to 1-bit SPI protocol operation

Read					Reads one byte from the serial flash and returns byte(max of 33 MHz CLK frequency)
Read_Cont				Reads multiple bytes(max of 33 MHz CLK frequency)
HighSpeed_Read			Reads one byte from the serial flash and returns byte(max of 80 MHz CLK frequency)
HighSpeed_Read_Cont		Reads multiple bytes(max of 80 MHz CLK frequency)
SQOR                          SPI Quad Output Read
SQIOR                         SPI Quad I/O Read
SDOR                          SPI Dual output read
SDIOR                         SPI Dual I/O Read
Set_Burst                     Specifies the number of bytes (8,16,32 or 64 bytes) to output during a Read Burst command
Read_Burst                    Reads multiple bytes as specified by Set_Burst
RBSPI                         SPI Read Burst with Wrap
  
Jedec_ID_Read			Reads the Jedec ID using SPI protocol
Quad J-ID               	Reads the Jedec ID using Quad I/O protocal
SFDP                          Serial Flash Discoverable Parameter

Sector_Erase			Erases one sector (4 KB) of the serial flash
Block_Erase				Erases 32 KByte block memory of the serial flash
Chip_Erase				Erases entire serial flash

Page_Program			Programs 1 to 256 Data Bytes
SPI Quad PP                     SPI Quad Page Program
Write Suspend		   Suspends Program/Erase  operation
Write Resume		   Resumes Program/Erase operation
nVWLDR                    non-Volatile Write Lock-Down Register
ULBPR                     Global Block Protection Unlock
Read SID			   Read Security ID
Prog SID			   Program User Security ID area
Lock SID			   Lockout Security ID Programming

RDSR					Reads the status register of the serial flash
WRSR                                    Write to the status register and configuration register
RDCR                                    Read Configuration Register
WREN					Write enables the serial flash
WRDI					Write disables the serial flash

RBPR					Read Block Protection Register
WBPR					Write Block Protection Register
LBPR					Lock Block Protection Register

Wait_Busy				Polls status register and waits until busy bit is low



*/


//"C" LANGUAGE DRIVERS



// include files
#include <p24fxxxx.h>

// defines

// configuration bits
        _CONFIG1(JTAGEN_OFF & ICS_PGx2 & FWDTEN_OFF)
		_CONFIG2(OSCIOFNC_ON &  FNOSC_FRCDIV & POSCMOD_NONE)

/* Pin Function Prototypes */

void Portassign();
void SetSIO0_Output();
void SetSIO0_Input();
void SetSIO1_Output();
void SetSIO1_Input();
void SetSIO2_Output();
void SetSIO2_Input();
void SetSIO3_Output();
void SetSIO3_Input();
void SIO0_Low();
void SIO1_Low();
void SIO2_Low();
void SIO3_Low();
void SIO0_High();
void SIO1_High();
void SIO2_High();
void SIO3_High();
void SCK_High();
void SCK_Low();
void CE_High();
void CE_Low();
void Reset_Hold_Low();
void Reset_Hold_High();
void WP_Low();
void WP_High();

void DisplayLED(char Led_Stat);

  /* Function Prototypes */

void init();
void NoOp();
void Send_Byte(unsigned char out);
void Send_Double_Byte(unsigned char out);
void SendSQI_Byte(unsigned char out);
unsigned char Get_Byte();
unsigned char Get_Double_Byte();
unsigned char GetSQI_Nibble();
unsigned char GetSQI_Byte();
void ResetEn();
void Reset();
void En_QIO();
void Reset_QIO();
unsigned char Read(unsigned long Dst);
void Read_Cont(unsigned long Dst, unsigned long no_bytes);
unsigned char HighSpeed_Read(unsigned long Dst);
void HighSpeed_Read_Cont(unsigned long Dst, unsigned long no_bytes);
void Set_Burst(unsigned char byte);
void Read_Burst(unsigned long Dst, unsigned char burstlength);
void Read_PI(unsigned char Dst, unsigned char datalength);
void Read_Index(unsigned long Dst, unsigned char datalength);
void Read_BlockIndex(unsigned char Dst, unsigned char datalength);
void Jedec_ID_Read();
void QuadJ_ID_Read();
void SPI_Quad_IO_InMode_Read_Cont(unsigned long Dst, unsigned long no_bytes);
unsigned char SPI_Quad_IO_InMode_Read(unsigned long Dst);
unsigned char SPI_Quad_IO_NotInMode_Read(unsigned long Dst);
void SPI_Quad_IO_NotInMode_Read_Cont(unsigned long Dst, unsigned long no_bytes);
unsigned char SPI_Double_IO_InMode_Read(unsigned long Dst);
unsigned char SPI_Double_IO_NotInMode_Read(unsigned long Dst);
void SPI_Double_IO_NotInMode_Read_Cont(unsigned long Dst, unsigned long no_bytes);
void SPI_Double_IO_InMode_Read_Cont(unsigned long Dst, unsigned long no_bytes);
void HighSpeed_NotInMode_Read_Cont(unsigned long Dst, unsigned long no_bytes);
void HighSpeed_InMode_Read_Cont(unsigned long Dst, unsigned long no_bytes);
unsigned char HighSpeed_InMode_Read(unsigned long Dst);
unsigned char HighSpeed_NotInMode_Read(unsigned long Dst);
void Sector_Erase(unsigned long Dst);
void Block_Erase(unsigned long Dst);
void Chip_Erase();
void Page_Program(unsigned long Dst);
void Write_Suspend();
void Write_Resume();
void ReadSID(unsigned char *security_ID, unsigned long Dst, unsigned long security_length);
void ProgSID(unsigned char *security_ID, unsigned long Dst, unsigned long security_length);
void LockSID();
unsigned char Read_Status_Register();
void WREN();
void WRDI();
void ReadBlockProtection();
void WriteBlockProtection();
void LockBlockProtection();
void SPI_Global_Block_Protection_Unlock();
void Global_Block_Protection_Unlock();

void Wait_Busy();
void Wait_Busy_special();
void SPI_Wait_Busy_special();

unsigned char SPI_SFDP_Read(unsigned long Dst);

unsigned int data_256[256];	/* global array to store read data */
unsigned int block_protection_6[6];	/* global array to store block_protection data */
unsigned char   Manufacturer_Id, Device_Type, Device_Id; /* global array to store Manufacturer and Device id information */

char Sw;
char buffer[15];
unsigned long deviceaddress;


/************************************************************************/
/* PROCEDURE: Port Assign						*/
/*									*/
/* This procedure sets the Ports for SPI communicaiton and LED Display.	*/
/* LATA is for LED display.  LATF is for SPI communication.		*/
/************************************************************************/

void Portassign()
{
	LATA = 0x0000;		// set LAT A output latches low
	TRISA = 0x0000;		// set LAT A pins to be outputs

    LATG = 0xBC3F;
	TRISG =0xBC3F;  	//Set everything to be output.
	
    LATD = 0xFFFE;
	TRISD =0xFFFE;  	//Set everything to be output.

}


/************************************************************************/
/* PROCEDURE: SetSIO0_Output, SetSIO0_Input				*/
/*									*/
/* This procedure sets the Ports for SQI communicaiton          	*/
/************************************************************************/


void SetSIO0_Output()
{
	TRISG = TRISG & ~(0x0100);
}
void SetSIO0_Input()
{
	TRISG = TRISG | (0x100);
}
void SetSIO1_Output()
{
	TRISG = TRISG & ~(0x0080);
}
void SetSIO1_Input()
{
	TRISG = TRISG | (0x0080);
}
void SetSIO2_Output()
{
	TRISD = TRISD & ~(0x0001);
}
void SetSIO2_Input()
{
	TRISD = TRISD | (0x0001);
}
void SetSIO3_Output()
{
	TRISG = TRISG & ~(0x4000);
}
void SetSIO3_Input()
{
	TRISG = TRISG | (0x4000);
}


/************************************************************************/
/* PROCEDURE: Display LED						*/
/*                                                              	*/
/* This procedure is used to diplay a byte on 8 LEDs which are 		*/
/* connected to LATA							*/
/************************************************************************/
void DisplayLED(char Led_Stat)
{
	LATA=Led_Stat;
}



/************************************************************************/
/* PROCEDURE: SCK_High							*/
/*									*/
/* This procedure set SCK = High.					*/
/************************************************************************/
void SCK_High()
{
	LATG = LATG | (0x40);			/* set SCK high */
}

/************************************************************************/
/* PROCEDURE: SCK_Low							*/
/*                                                      		*/
/* This procedure drives the SCK of the device to low.  		*/
/************************************************************************/
void SCK_Low()
{
	LATG = LATG & ~(0x0040);		/* clear SCK low */
}




/************************************************************************/
/* PROCEDURE: CE_High							*/
/*									*/
/* This procedure set CE = High.					*/
/************************************************************************/
void CE_High()
{
	LATG = LATG | (0x0200);			/* set CE high */
}

/************************************************************************/
/* PROCEDURE: CE_Low							*/
/*									*/
/* This procedure drives the CE of the device to low.  			*/
/************************************************************************/
void CE_Low()
{
	LATG = LATG & ~(0x0200);		/* clear CE low */
}
/************************************************************************/
/* PROCEDURE: Reset_Hold_Low()						*/
/*									*/
/* This procedure clears the Reset_Hold pin to low.			*/
/************************************************************************/
void Reset_Hold_Low()
{
LATG = LATG & ~(0x4000);			/* clear Hold pin */
}

/************************************************************************/
/* PROCEDURE: Reset_Hold_High()						*/
/*									*/
/* This procedure sets the Reset_Hold pin to high.			*/
/************************************************************************/
void Reset_Hold_High()
{
LATG = LATG | (0x4000);				/* set Hold pin */
}

/************************************************************************/
/* PROCEDURE: WP_Low()							*/
/*									*/
/* This procedure clears the WP pin to low.				*/
/************************************************************************/
void WP_Low()
{
LATD = LATD & ~(0x0001);			/* clear WP pin */
}

/************************************************************************/
/* PROCEDURE: WP_High()							*/
/*									*/
/* This procedure sets the WP pin to high.				*/
/************************************************************************/
void WP_High()
{
LATD = LATD | (0x01);				/* set WP pin */
}


/************************************************************************/
/* PROCEDURE: SIO0_High							*/
/*									*/
/* This procedure set SIO0 = High.					*/
/************************************************************************/
void SIO0_High()
{
	LATG = LATG | (0x100);			/* set SIO0 high */
}

/************************************************************************/
/* PROCEDURE: SIO0_Low							*/
/*									*/
/* This procedure drives the SIO0 of the device to low. 		*/
/************************************************************************/
void SIO0_Low()
{
	LATG = LATG & ~(0x0100);		/* clear SIO0 low */
}



/************************************************************************/
/* PROCEDURE: SIO1_High							*/
/*									*/
/* This procedure set SIO1 = High.					*/
/************************************************************************/
void SIO1_High()
{
	LATG = LATG | (0x80);			/* set SIO1 high */
}

/************************************************************************/
/* PROCEDURE: SIO1_Low							*/
/*									*/
/* This procedure drives the SIO1 of the device to low.			*/
/************************************************************************/
void SIO1_Low()
{
	LATG = LATG & ~(0x0080);		/* clear SIO1 low */
}




/************************************************************************/
/* PROCEDURE: SIO2_High							*/
/*									*/
/* This procedure set SIO2 = High.					*/
/************************************************************************/
void SIO2_High()
{
            LATD = LATD | (0x001);		/* set SIO2 high */
}

/************************************************************************/
/* PROCEDURE: SIO2_Low							*/
/*									*/
/* This procedure drives the SIO2 of the device to low.			*/
/************************************************************************/
void SIO2_Low()
{
	LATD = LATD & ~(0x0001);		/* clear SIO2 low */
}


/************************************************************************/
/* PROCEDURE: SIO3_High							*/
/*									*/
/* This procedure set SIO3 = High.					*/
/************************************************************************/
void SIO3_High()
{
	LATG = LATG | (0x4000);			/* set SIO3 high */
}

/************************************************************************/
/* PROCEDURE: SIO3_Low							*/
/*									*/
/* This procedure drives the SIO3 of the device to low. 		*/
/************************************************************************/
void SIO3_Low()
{
	LATG = LATG & ~(0x4000);		/* clear SIO3 low */
}

/************************************************************************/
/* PROCEDURE: init							*/
/*									*/
/* This procedure initializes the SCK to low. Must be called prior to 	*/
/* setting up mode 0.							*/
/************************************************************************/
void init()
{
	SCK_Low();	/* set clock to low initial state */
}

/************************************************************************/
/* PROCEDURE: Send_Byte							*/
/*									*/
/* This procedure outputs a byte shifting out 1-bit per clock rising	*/
/* edge on the the SI pin (SIO0 pin) LSB 1st.				*/
/************************************************************************/
void Send_Byte(unsigned char out)
{

	unsigned char i = 0;
	SetSIO0_Output();

	for (i = 0; i < 8; i++)
	{

		if ((out & 0x80) == 0x80)	/* check if MSB is high */
			SIO0_High();
		else
			SIO0_Low();		/* if not, set to low */
		SCK_High();			/* toggle clock high */
		out = (out << 1);		/* shift 1 place for next bit */
		SCK_Low();			/* toggle clock low */
	}
}

/************************************************************************/
/* PROCEDURE: Send_Double_Byte						*/
/*									*/
/* This procedure outputs a byte shifting out 2-bit per clock rising	*/
/* edge on the the SI pin and SO pin (SIO0,SIO1) MSB 1st.		*/
/************************************************************************/
 void Send_Double_Byte(unsigned char out)
{

	SetSIO0_Output();
	SetSIO1_Output();

		if ((out & 0x80) ==0x80)
			{SIO1_High();}
		else
			{SIO1_Low();}

		if ((out & 0x40) ==0x40)
			{SIO0_High();}
		else
			{SIO0_Low();}

		SCK_High();			/* toggle clock high */

		SCK_Low();			/* toggle clock low */


		if ((out & 0x20) ==0x20)
			{SIO1_High();}
		else
			{SIO1_Low();}

		if ((out & 0x10) ==0x10)
			{SIO0_High();}
		else
			{SIO0_Low();}

		SCK_High();			/* toggle clock high */

		SCK_Low();			/* toggle clock low */


		if ((out & 0x08) ==0x08)
			{SIO1_High();}
		else
			{SIO1_Low();}

		if ((out & 0x04) ==0x04)
			{SIO0_High();}
		else
			{SIO0_Low();}

		SCK_High();			/* toggle clock high */

		SCK_Low();			/* toggle clock low */


		if ((out & 0x02) ==0x02)
			{SIO1_High();}
		else
			{SIO1_Low();}

		if ((out & 0x01) ==0x01)
			{SIO0_High();}
		else
			{SIO0_Low();}

		SCK_High();			/* toggle clock high */

		SIO0_High();  //Set them as Inputs
		SIO1_High();

		SCK_Low();			/* toggle clock low */


}

/************************************************************************/
/* PROCEDURE: SendSQI_Nibble						*/
/*									*/
/* This procedure outputs a byte shifting out 1-bit per clock rising	*/
/* edge on the the SI0, SIO1, SIO2, SIO2 pin (LSB 1st).			*/
/************************************************************************/
void SendSQI_Byte(unsigned char out)
{

	SetSIO0_Output();
	SetSIO1_Output();
	SetSIO2_Output();
	SetSIO3_Output();

	if ((out & 0x80) == 0x80)	/* check if MSB is high */
			{SIO3_High();}
		else
			{SIO3_Low();}


		if ((out & 0x40) ==0x40)
			{SIO2_High();}
		else
			{SIO2_Low();}

		if ((out & 0x20) ==0x20)
			{SIO1_High();}
		else
			{SIO1_Low();}

		if ((out & 0x10) ==0x10)
			{SIO0_High();}
		else
			{SIO0_Low();}

		SCK_High();			/* toggle clock high */

		SCK_Low();			/* toggle clock low */


	if ((out & 0x08) == 0x08)	/* check if MSB is high */
			{SIO3_High();}
		else
			{SIO3_Low();}

		if ((out & 0x04) ==0x04)
			{SIO2_High();}
		else
			{SIO2_Low();}

		if ((out & 0x02) ==0x02)
			{SIO1_High();}
		else
			{SIO1_Low();}

		if ((out & 0x01) ==0x01)
			{SIO0_High();}
		else
			{SIO0_Low();}

		SCK_High();			/* toggle clock high */

		SIO0_High();  //Set them as Inputs
		SIO1_High();
		SIO2_High();
		SIO3_High();
		SetSIO0_Input();
		SetSIO1_Input();
		SetSIO2_Input();
		SetSIO3_Input();


		SCK_Low();			/* toggle clock low */


}


/************************************************************************/
/* PROCEDURE: Get_Byte							*/
/*									*/
/* This procedure inputs a byte shifting in 1-bit per clock falling	*/
/* edge on the SIO1 pin(LSB 1st).					*/
/************************************************************************/
unsigned char Get_Byte()
{
	unsigned char i = 0, in = 0, temp = 0;

	SetSIO1_Input();

	for (i = 0; i < 8; i++)
	{
		in = (in << 1);		/* shift 1 place to the left or shift in 0 */
	temp = ((PORTG & 0x80)>>7);		/* save input */
			SCK_High();		/* toggle clock high */
	if (temp == 1)			/* check to see if bit is high */
		in = in | 0x01;		/* if high, make bit high */

		SCK_Low();		/* toggle clock low */

	}
	return in;
}

/************************************************************************/
/* PROCEDURE: Get_Double_Byte						*/
/*									*/
/* This procedure inputs a byte shifting in 2-bit per clock falling	*/
/* edge on the SIO1 pin and SIO0 pin(MSB 1st).				*/
/************************************************************************/
unsigned char Get_Double_Byte()
{
	unsigned char i = 0, in = 0, temp = 0, temp1=0;
	SetSIO0_Input();
	SetSIO1_Input();

	for (i = 0; i < 4; i++)
	{
		in = (in << 1);			/* shift 1 place to the left or shift in 0 */
		temp = ((PORTG & 0x80)>>7) ;	/* save input */
		temp1 = ((PORTG & 0x100)>>8);	/* save input */
			SCK_High();			/* toggle clock high */

		if (temp == 1)			/* check to see if bit is high */
		{in = in | 0x01;}		/* if high, make bit high */

		in=(in << 1);

		if (temp1 == 1)
		{in = in | 0x01;}

		SCK_Low();			/* toggle clock low */

	}
	return in;
}


/************************************************************************/
/* PROCEDURE: GetSQI_Nibble						*/
/*									*/
/* This procedure inputs a byte shifting in 1-bit per clock falling	*/
/* edge on the SIO0 pin, SIO1 pin, SIO2 pin and SIO3 pin.		*/
/************************************************************************/
unsigned char GetSQI_Nibble()
{
	unsigned char in = 0, temp3 = 0, temp2 =0, temp1 = 0, temp0=0;

	SetSIO0_Input();
	SetSIO1_Input();
	SetSIO2_Input();
	SetSIO3_Input();

temp3=((PORTG & 0x4000)>>14);
	temp2=((PORTD & 0x01));
	temp1=((PORTG & 0x80)>>7);
	temp0=((PORTG & 0x100)>>8);
	SCK_High();

	if (temp3==1)
	{in=1;}
	in = (in<<1);
	if (temp2==1)
	{in=in|0x01;}
	in = (in<<1);
	if (temp1==1)
	{in = in|0x01;}
	in = (in<<1);
	if (temp0==1)
	{in = in|0x01;}

	SCK_Low();		/* toggle clock low */

	return in;
}

/************************************************************************/
/* PROCEDURE: GetSQI_Byte						*/
/*									*/
/* This procedure call GetSQI_Nibble function twice to get 1 byte of data*/
/************************************************************************/
unsigned char GetSQI_Byte()
{
	unsigned char temp, in = 0;

	in=GetSQI_Nibble();
	in=(in<<4);
	temp=GetSQI_Nibble();
	in=in|temp;

	return in;

}

/************************************************************************/
/* PROCEDURE: Read_Status_Register					*/
/*									*/
/* This procedure reads the status register and returns the byte.	*/
/************************************************************************/
unsigned char Read_Status_Register()
{
	unsigned char byte = 0;
	CE_Low();			/* enable device */
	SendSQI_Byte(0x05);		/* send RDSR command */
	SendSQI_Byte(0xff);		/* send RDSR command */

	byte = GetSQI_Byte();		/* receive byte */
	CE_High();			/* disable device */
	return byte;
}

unsigned char SPI_Read_Status_Register()
{
	unsigned char byte = 0;
	CE_Low();			/* enable device */
	Send_Byte(0x05);		/* send RDSR command */
	byte = Get_Byte();		/* receive byte */
	CE_High();			/* disable device */
	return byte;
}

/************************************************************************/
/* PROCEDURE: Read_Configuration_Register				*/
/*									*/
/* This procedure reads the configuration register and returns the byte.*/
/************************************************************************/
unsigned char SPI_Read_Configuration_Register()
{
	unsigned char byte = 0;
	CE_Low();			/* enable device */
	Send_Byte(0x35);		/* send RDSR command */
	byte = Get_Byte();		/* receive byte */
	CE_High();			/* disable device */
	return byte;
}
unsigned char Read_Configuration_Register()
{
	unsigned char byte = 0;
	CE_Low();			/* enable device */
	SendSQI_Byte(0x35);		/* send RDSR command */
	SendSQI_Byte(0xff);		/* send Dummy */
	byte = GetSQI_Byte();		/* receive byte */
	CE_High();			/* disable device */
	return byte;
}


/************************************************************************/
/* PROCEDURE: WREN							*/
/*									*/
/* This procedure enables the Write Enable Latch.               	*/
/************************************************************************/
void WREN()
{
	CE_Low();			/* enable device */
	SendSQI_Byte(0x06);		/* send WREN command */
	CE_High();			/* disable device */
}

void SPI_WREN()
{
	CE_Low();			/* enable device */
	Send_Byte(0x06);		/* send WREN command */
	CE_High();			/* disable device */
}

/************************************************************************/
/* PROCEDURE: WRDI							*/
/*									*/
/* This procedure disables the Write Enable Latch.			*/
/************************************************************************/
void WRDI()
{
	CE_Low();			/* enable device */
	SendSQI_Byte(0x04);		/* send WRDI command */
	CE_High();			/* disable device */
}
void SPI_WRDI()
{
	CE_Low();			/* enable device */
	Send_Byte(0x04);		/* send WRDI command */
	CE_High();			/* disable device */
}


/************************************************************************/
/* PROCEDURE: QuadJ_ID							*/
/*									*/
/* This procedure Reads the manufacturer's ID, device Type and device ID.  It will 	*/
/* use AFh as the command to read the ID.                               */
/* Returns:								*/
/*	ID1(Manufacture's ID = BFh, Device Type =26h , Device ID = 02h)	*/
/*									*/
/************************************************************************/

void QuadJ_ID_Read()
{

	CE_Low();                           /* enable device */
	SendSQI_Byte(0xAF);                 /* send read ID command (90h or ABh) */
	SendSQI_Byte(0xFF);
   	Manufacturer_Id = GetSQI_Byte();    /* receive byte */
  	Device_Type = GetSQI_Byte();        /* receive byte */
  	Device_Id = GetSQI_Byte();          /* receive byte */

	CE_High();                          /* disable device */

}
void Jedec_ID_Read()
{


	CE_Low();                            /* enable device */
	Send_Byte(0x9F);                    /* send JEDEC ID command (9Fh) */
   	Manufacturer_Id = Get_Byte();       /* receive byte */
  	Device_Type = Get_Byte();           /* receive byte */
  	Device_Id = Get_Byte();             /* receive byte */

	CE_High();                          /* disable device */
}


/************************************************************************/
/* PROCEDURE:	Read							*/
/*									*/
/* This procedure reads one address of the device.  It will return the 	*/
/* byte read in variable byte.						*/
/* Input:								*/
/*		Dst:	Destination Address 000000H - 7FFFFFH		*/
/************************************************************************/
unsigned char Read(unsigned long Dst)
{
	unsigned char byte = 0;

	CE_Low();                                /* enable device */
	Send_Byte(0x03);                        /* read command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	byte = Get_Byte();
	CE_High();                              /* disable device */
	return byte;                            /* return one byte read */
}


/************************************************************************/
/* PROCEDURE:	Read_Cont						*/
/*									*/
/* This procedure reads multiple addresses of the device and stores	*/
/* data into 256 byte buffer. Maximum number of bytes read is limited 256 bytes*/
/*									*/
/* Input:								*/
/*		Dst:		Destination Address 000000H - 7FFFFFH	*/
/*      	no_bytes	Number of bytes to read	(max = 256)	*/
/************************************************************************/
void Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i = 0;
	CE_Low();				/* enable device */
	Send_Byte(0x03); 			/* read command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	if (no_bytes>256)
	{no_bytes=256;}
	for (i = 0; i < no_bytes; i++)		/* read until no_bytes is reached */
	{
		data_256[i] = Get_Byte();
	}
	CE_High();				/* disable device */

}

/************************************************************************/
/* PROCEDURE:	HighSpeed_Read						*/
/*									*/
/* This procedure reads one address of the device.  It will return the 	*/
/* byte read in variable byte.						*/
/* Input:								*/
/*		Dst:	Destination Address 000000H - 7FFFFFH		*/
/************************************************************************/
unsigned char SPI_HighSpeed_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	CE_Low();                               /* enable device */
	Send_Byte(0x0B);                        /* read command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	Send_Byte(0xFF);                        /*dummy byte*/
	byte = Get_Byte();
	CE_High();                              /* disable device */
	return byte;                            /* return one byte read */
}

unsigned char HighSpeed_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	CE_Low();                               /* enable device */
	SendSQI_Byte(0x0B);                     /* read command */
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	SendSQI_Byte(0xAF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	byte = GetSQI_Byte();
	CE_High();                              /* disable device */
	return byte;                            /* return one byte read */
}

unsigned char HighSpeed_InMode_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	CE_Low();                           	/* enable device */
	SendSQI_Byte(0x0B);
        SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	SendSQI_Byte(0xAF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	byte = GetSQI_Byte();
	CE_High();                      	/* disable device */
	return byte;                    	/* return one byte read */
}
unsigned char HighSpeed_NotInMode_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	CE_Low();                       	/* enable device */
	SendSQI_Byte(0x0B); 
        SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	SendSQI_Byte(0xCF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	byte = GetSQI_Byte();
	CE_High();                              /* disable device */
	return byte;                            /* return one byte read */
}

/************************************************************************/
/* PROCEDURE:	HighSpeed_Read_Cont					*/
/*									*/
/* This procedure reads multiple addresses of the device and stores	*/
/* data into 256 byte buffer. Maximum number of bytes read is limited to 256 bytes*/
/*									*/
/* Input:								*/
/*		Dst:		Destination Address 000000H - 7FFFFFH	*/
/*      	no_bytes	Number of bytes to read	(max = 256)	*/
/************************************************************************/
void SPI_HighSpeed_Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i = 0;
	CE_Low();				/* enable device */
	Send_Byte(0x0B); 			/* read command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	Send_Byte(0xFF);                	/*dummy byte*/
	if (no_bytes>256)
	{no_bytes=256;}

	for (i = 0; i < no_bytes; i++)		/* read until no_bytes is reached */
	{
		data_256[i] = Get_Byte();
	}
	CE_High();				/* disable device */
}

void HighSpeed_Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i = 0;
	CE_Low();				/* enable device */
	SendSQI_Byte(0x0B); 			/* read command */
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	SendSQI_Byte(0xAF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	if (no_bytes>256)
	{no_bytes=256;}

	for (i = 0; i < no_bytes; i++)		/* read until no_bytes is reached */
	{
		data_256[i] = GetSQI_Byte();
	}
	CE_High();				/* disable device */
}

void HighSpeed_InMode_Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i = 0;
	CE_Low();				/* enable device */
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	SendSQI_Byte(0xAF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	if (no_bytes>256)
	{no_bytes=256;}

	for (i = 0; i < no_bytes; i++)		/* read until no_bytes is reached */
	{
		data_256[i] = GetSQI_Byte();
	}
	CE_High();				/* disable device */
}
void HighSpeed_NotInMode_Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i = 0;
	CE_Low();				/* enable device */
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	SendSQI_Byte(0xCF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	if (no_bytes>256)
	{no_bytes=256;}

	for (i = 0; i < no_bytes; i++)		/* read until no_bytes is reached */
	{
		data_256[i] = GetSQI_Byte();
	}
	CE_High();				/* disable device */
}



/************************************************************************/
/* PROCEDURE:	SPI_Quad_Output_Read					*/
/*									*/
/* This procedure reads one address of the device.  It will return the 	*/
/* byte read in variable byte.						*/
/* Input:								*/
/*		Dst:	Destination Address 000000H - 7FFFFFH		*/
/************************************************************************/
unsigned char SPI_Quad_Output_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	CE_Low();                               /* enable device */
	Send_Byte(0x6B);                        /* read command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	Send_Byte(0xFF);                        /*dummy byte*/
	byte = GetSQI_Byte();
	CE_High();                              /* disable device */
	return byte;                            /* return one byte read */
}



/************************************************************************/
/* PROCEDURE:	SPI_Quad_Output_Read_Cont				*/
/*									*/
/* This procedure reads multiple addresses of the device and stores	*/
/* data into 256 byte buffer. Maximum number of bytes read is limited to 256 bytes*/
/*									*/
/* Input:								*/
/*		Dst:		Destination Address 000000H - 7FFFFFH	*/
/*      	no_bytes	Number of bytes to read	(max = 256)	*/
/************************************************************************/
void SPI_Quad_Output_Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i = 0;
	CE_Low();				/* enable device */
	Send_Byte(0x6B); 			/* read command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	Send_Byte(0xFF);                        /*dummy byte*/

	if (no_bytes>256)
	{no_bytes=256;}

	for (i = 0; i < no_bytes; i++)		/* read until no_bytes is reached */
	{
		data_256[i] = GetSQI_Byte();
	}
	CE_High();				/* disable device */
}

/************************************************************************/
/* PROCEDURE:	SPI_Quad_IO_Read					*/
/*									*/
/* This procedure reads one address of the device.  It will return the 	*/
/* byte read in variable byte.						*/
/*									*/
/* Input:								*/
/*		Dst:	Destination Address 000000H - 7FFFFFH		*/
/************************************************************************/
unsigned char SPI_Quad_IO_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	CE_Low();                               /* enable device */
	Send_Byte(0xEB);                        /* read command */
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	SendSQI_Byte(0xAF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	byte = GetSQI_Byte();
	CE_High();                              /* disable device */
	return byte;                            /* return one byte read */
}
unsigned char SPI_Quad_IO_InMode_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	CE_Low();                       	/* enable device */
        Send_Byte(0xEB);
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	SendSQI_Byte(0xAF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	byte = GetSQI_Byte();
	CE_High();                              /* disable device */
	return byte;                            /* return one byte read */
}
unsigned char SPI_Quad_IO_NotInMode_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	CE_Low();                       	/* enable device */
        Send_Byte(0xEB);
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	byte = GetSQI_Byte();
	CE_High();                              /* disable device */
	return byte;                            /* return one byte read */
}


/************************************************************************/
/* PROCEDURE:	SPI_Quad_IO_Read_Cont					*/
/*									*/
/* This procedure reads multiple addresses of the device and stores	*/
/* data into 256 byte buffer. Maximum number of bytes read is limited to 256 bytes*/
/*									*/
/* Input:								*/
/*		Dst:		Destination Address 000000H - 7FFFFFH	*/
/*      	no_bytes	Number of bytes to read	(max = 256)	*/
/************************************************************************/
void SPI_Quad_IO_Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i = 0;
	CE_Low();				/* enable device */
	Send_Byte(0xEB);                        /* read command */
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	SendSQI_Byte(0xAF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/

	if (no_bytes>256)
	{no_bytes=256;}

	for (i = 0; i < no_bytes; i++)		/* read until no_bytes is reached */
	{
		data_256[i] = GetSQI_Byte();
	}
	CE_High();				/* disable device */
}
void SPI_Quad_IO_InMode_Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i = 0;
	CE_Low();				/* enable device */
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	SendSQI_Byte(0xAF);		/*dummy byte*/
	SendSQI_Byte(0xFF);		/*dummy byte*/
	SendSQI_Byte(0xFF);		/*dummy byte*/

	if (no_bytes>256)
	{no_bytes=256;}

	for (i = 0; i < no_bytes; i++)		/* read until no_bytes is reached */
	{
		data_256[i] = GetSQI_Byte();
	}
	CE_High();				/* disable device */
}
void SPI_Quad_IO_NotInMode_Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i = 0;
	CE_Low();				/* enable device */
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/
	SendSQI_Byte(0xFF);                     /*dummy byte*/

	if (no_bytes>256)
	{no_bytes=256;}

	for (i = 0; i < no_bytes; i++)		/* read until no_bytes is reached */
	{
		data_256[i] = GetSQI_Byte();
	}
	CE_High();				/* disable device */
}
/************************************************************************/
/* PROCEDURE:	SPI_Double_Output_Read					*/
/*									*/
/* This procedure reads one address of the device.  It will return the 	*/
/* byte read in variable byte.						*/
/* Input:								*/
/*		Dst:	Destination Address 000000H - 7FFFFFH		*/
/************************************************************************/
unsigned char SPI_Double_Output_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	CE_Low();			/* enable device */
	Send_Byte(0x3B); 		/* read command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	Send_Byte(0xFF);		/*dummy byte*/
	byte = Get_Double_Byte();
	CE_High();			/* disable device */
	return byte;			/* return one byte read */
}



/************************************************************************/
/* PROCEDURE:	SPI_Double_Output_Read_Cont				*/
/*									*/
/* This procedure reads multiple addresses of the device and stores	*/
/* data into 256 byte buffer. Maximum number of bytes read is limited to 256 bytes*/
/*									*/
/* Input:								*/
/*		Dst:		Destination Address 000000H - 7FFFFFH	*/
/*      	no_bytes	Number of bytes to read	(max = 256)	*/
/*									*/
/* Returns:								*/
/*		Nothing							*/
/*									*/
/************************************************************************/
void SPI_Double_Output_Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i = 0;
	CE_Low();				/* enable device */
	Send_Byte(0x3B); 			/* read command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	Send_Byte(0xFF);                	/*dummy byte*/

	if (no_bytes>256)
	{no_bytes=256;}

	for (i = 0; i < no_bytes; i++)		/* read until no_bytes is reached */
	{
		data_256[i] = Get_Double_Byte();
	}
	CE_High();				/* disable device */
}

/************************************************************************/
/* PROCEDURE:	SPI_Double_IO_Read					*/
/*									*/
/* This procedure reads one address of the device.  It will return the 	*/
/* byte read in variable byte.						*/
/* Input:								*/
/*		Dst:	Destination Address 000000H - 7FFFFFH		*/
/************************************************************************/
unsigned char SPI_Double_IO_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	CE_Low();			/* enable device */
	Send_Byte(0xBB); 		/* read command */
	Send_Double_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Double_Byte(((Dst & 0xFFFF) >> 8));
	Send_Double_Byte(Dst & 0xFF);
	Send_Double_Byte(0xAF);		/*dummy byte*/
	byte = Get_Double_Byte();
	CE_High();			/* disable device */
	return byte;			/* return one byte read */
}

unsigned char SPI_Double_IO_InMode_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	CE_Low();			/* enable device */
	 Send_Byte(0xBB); 		/* read command */
	Send_Double_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Double_Byte(((Dst & 0xFFFF) >> 8));
	Send_Double_Byte(Dst & 0xFF);
	Send_Double_Byte(0xAF);		/*dummy byte*/
	byte = Get_Double_Byte();
	CE_High();			/* disable device */
	return byte;			/* return one byte read */
}

unsigned char SPI_Double_IO_NotInMode_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	CE_Low();			/* enable device */
	Send_Byte(0xBB); 		/* read command */
	Send_Double_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Double_Byte(((Dst & 0xFFFF) >> 8));
	Send_Double_Byte(Dst & 0xFF);
	Send_Double_Byte(0xFF);		/*dummy byte*/
	byte = Get_Double_Byte();
	CE_High();			/* disable device */
	return byte;			/* return one byte read */
}



/************************************************************************/
/* PROCEDURE:	SPI_Double_IO_Read_Cont					*/
/*									*/
/* This procedure reads multiple addresses of the device and stores	*/
/* data into 256 byte buffer. Maximum number of bytes read is limited to 256 bytes*/
/*									*/
/* Input:								*/
/*		Dst:		Destination Address 000000H - 7FFFFFH	*/
/*      	no_bytes	Number of bytes to read	(max = 256)	*/
/************************************************************************/
void SPI_Double_IO_Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i=0;
	CE_Low();                                       /* enable device */
	Send_Byte(0xBB);                                /* read command */
	Send_Double_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Double_Byte(((Dst & 0xFFFF) >> 8));
	Send_Double_Byte(Dst & 0xFF);
	Send_Double_Byte(0xAF);                         /*dummy byte*/

	if (no_bytes>256)
	{no_bytes=256;}

	for ( i = 0; i < no_bytes; i++)                 /* read until no_bytes is reached */
	{
		data_256[i] = Get_Double_Byte();
	}
	CE_High();                                      /* disable device */
}
void SPI_Double_IO_InMode_Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i=0;
	CE_Low();                                       /* enable device */
                                                        /* read command */
	Send_Double_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Double_Byte(((Dst & 0xFFFF) >> 8));
	Send_Double_Byte(Dst & 0xFF);
	Send_Double_Byte(0xAF);                         /*dummy byte*/

	if (no_bytes>256)
	{no_bytes=256;}

        for ( i = 0; i < no_bytes; i++)                 /* read until no_bytes is reached */
	{
		data_256[i] = Get_Double_Byte();
	}
	CE_High();                                      /* disable device */
}
void SPI_Double_IO_NotInMode_Read_Cont(unsigned long Dst, unsigned long no_bytes)
{
	unsigned long i=0;
	CE_Low();                               	/* enable device */
                                                        /* read command */
	Send_Double_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Double_Byte(((Dst & 0xFFFF) >> 8));
	Send_Double_Byte(Dst & 0xFF);
	Send_Double_Byte(0xFF);                         /*dummy byte*/

	if (no_bytes>256)
	{no_bytes=256;}

	for ( i = 0; i < no_bytes; i++)                 /* read until no_bytes is reached */
	{
		data_256[i] = Get_Double_Byte();
	}
	CE_High();                                      /* disable device */
}


/************************************************************************/
/* PROCEDURE:	Set_Burst						*/
/*									*/
/* This procedure sets the burst length to either 8bytes or 16bytes or 32bytes or 64bytes.			*/
/* Input:								*/
/*		byte:	00h,01h,02h or 03h for setting burst length	*/
/************************************************************************/
void Set_Burst(unsigned char byte)
{
	CE_Low();				/* enable device */
	SendSQI_Byte(0xC0); 			/* send Byte Program command */
	SendSQI_Byte(byte);			/* send byte to be programmed */
	CE_High();				/* disable device */
}

void SPI_Set_Burst(unsigned char byte)
{
	CE_Low();				/* enable device */
	Send_Byte(0xC0); 			/* send Byte Program command */
	Send_Byte(byte);			/* send byte to be programmed */
	CE_High();				/* disable device */
}


/************************************************************************/
/* PROCEDURE:	Read_Burst                                          	*/
/*									*/
/* This procedure reads multiple (burst) address of the device.  The data is stored in an array.*/
/* Input:								*/
/*		Dst:	Destination Address 000000H - 7FFFFFH		*/
/************************************************************************/
void Read_Burst(unsigned long Dst, unsigned char burstlength)
{
	unsigned int i;
	i=0;

	CE_Low();                                   /* enable device */
	SendSQI_Byte(0x0C);                         /* read command */
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));     /* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
        SendSQI_Byte(Dst & 0xFF);                   //Dummy cycle
	SendSQI_Byte(Dst & 0xFF);                   //Dummy cycle
  	SendSQI_Byte(Dst & 0xFF);                   //Dummy cycle

	//if (burstlength>256)
	//{burstlength=256;}

	for (i=0;i<=(burstlength-1);i++)
	{
	data_256[i]=GetSQI_Byte();
	}

	CE_High();                                  /* disable device */

}
void SPI_Read_Burst(unsigned long Dst, unsigned char burstlength)
{
	unsigned int i;
	i=0;

	CE_Low();                                   /* enable device */
	Send_Byte(0xEC);                            /* read command */
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	SendSQI_Byte(Dst & 0xFF);                   //Dummy cycle
	SendSQI_Byte(Dst & 0xFF);                   //Dummy cycle
  	SendSQI_Byte(Dst & 0xFF);                   //Dummy cycle

	//if (burstlength>256)
//	{burstlength=256;}

	for (i=0;i<(burstlength);i++)
	{
	data_256[i]=GetSQI_Byte();
	}

	CE_High();                                  /* disable device */

}

/************************************************************************/
/* PROCEDURE:	Page_Program						*/
/*									*/
/* This procedure does page programming.  The destination               */
/* address should be provided.                                  	*/
/* The data array of 256 bytes contains the data to be programmed.      */
/* Since the size of the data array is 256 bytes rather than 256 bytes, this page program*/
/* procedure programs only 256 bytes                                    */
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*		block protected.					*/
/* Input:								*/
/*		Dst:		Destination Address 000000H - 7FFFFFH	*/
/*		data_256[256] containing 256 bytes of data will be programmed using this function */
/************************************************************************/
void Page_Program(unsigned long Dst)
{
	unsigned int i;
	i=0;

	CE_Low();				/* enable device */
	SendSQI_Byte(0x02); 			/* send Byte Program command */
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	for (i=0;i<=255;i++)
	{	SendSQI_Byte(data_256[i]);	/* send byte to be programmed */
	}
	CE_High();				/* disable device */
}
void SPI_Page_Program(unsigned long Dst)
{
	unsigned int i;
	i=0;

	CE_Low();				/* enable device */
	Send_Byte(0x02); 			/* send Byte Program command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	for (i=0;i<256;i++)
	{	Send_Byte(data_256[i]);		/* send byte to be programmed */
	}
	CE_High();				/* disable device */
}

/************************************************************************/
/* PROCEDURE:	SPI_Quad_Page_Program					*/
/*									*/
/* This procedure does page programming.  The destination               */
/* address should be provided.                                          */
/* The data array of 256 bytes contains the data to be programmed.      */
/* Since the size of the data array is 256 bytes rather than 256 bytes, this page program*/
/* procedure programs only 256 bytes                                    */
/* Assumption:  Address being programmed is already erased and is NOT	*/
/*		block protected.					*/
/* Input:								*/
/*		Dst:		Destination Address 000000H - 7FFFFFH	*/
/*		data_256[256] containing 256 bytes of data will be programmed using this function */
/************************************************************************/
void SPI_Quad_Page_Program(unsigned long Dst)
{
	unsigned int i;
	i=0;

	CE_Low();				/* enable device */
	Send_Byte(0x32); 			/* send Byte Program command */
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	for (i=0;i<=255;i++)
	{	SendSQI_Byte(data_256[i]);	/* send byte to be programmed */
	}
	CE_High();				/* disable device */
}


/************************************************************************/
/* PROCEDURE: Chip_Erase						*/
/*									*/
/* This procedure erases the entire Chip.				*/
/************************************************************************/
void Chip_Erase()
{
	CE_Low();				/* enable device */
	SendSQI_Byte(0xC7);			/* send Chip Erase command (C7h) */
	CE_High();				/* disable device */
}

void SPI_Chip_Erase()
{
	CE_Low();				/* enable device */
	Send_Byte(0xC7);			/* send Chip Erase command (C7h) */
	CE_High();				/* disable device */
}

/************************************************************************/
/* PROCEDURE: Sector_Erase						*/
/*									*/
/* This procedure Sector Erases the Chip.				*/
/* Input:								*/
/*		Dst:		Destination Address 000000H - 7FFFFFH	*/
/************************************************************************/
void Sector_Erase(unsigned long Dst)
{


	CE_Low();				/* enable device */
	SendSQI_Byte(0x20);			/* send Sector Erase command */
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	CE_High();				/* disable device */
}

void SPI_Sector_Erase(unsigned long Dst)
{


	CE_Low();				/* enable device */
	Send_Byte(0x20);			/* send Sector Erase command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	CE_High();				/* disable device */
}

/************************************************************************/
/* PROCEDURE: Block_Erase						*/
/*									*/
/* This procedure Block Erases 8Kbyte, 32 KByte or 64 KByte of the Chip.*/
/*									*/
/* Input:								*/
/*		Dst:		Destination Address 000000H - 7FFFFFH	*/
/************************************************************************/
void Block_Erase(unsigned long Dst)
{
	CE_Low();				/* enable device */
	SendSQI_Byte(0xD8);			/* send Block Erase command */
	SendSQI_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	SendSQI_Byte(((Dst & 0xFFFF) >> 8));
	SendSQI_Byte(Dst & 0xFF);
	CE_High();				/* disable device */
}
void SPI_Block_Erase(unsigned long Dst)
{
	CE_Low();				/* enable device */
	Send_Byte(0xD8);			/* send Block Erase command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16)); 	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	CE_High();				/* disable device */
}


/************************************************************************/
/* PROCEDURE: NoOp                                              	*/
/*									*/
/* No operation is performed.                                           */
/************************************************************************/
void NoOp()
{
	CE_Low();				/* enable device */
	SendSQI_Byte(0x00);
	CE_High();				/* disable device */
}
void SPI_NoOp()
{
	CE_Low();				/* enable device */
	Send_Byte(0x00);
	CE_High();				/* disable device */
}



/************************************************************************/
/* PROCEDURE: ResetEn                                                   */
/*									*/
/* This procedure Enables acceptance of the RST (Reset) operation.	*/
/************************************************************************/
void ResetEn()
{
	CE_Low();				/* enable device */
	SendSQI_Byte(0x66);
	CE_High();				/* disable device */
}

void SPI_ResetEn()
{
	CE_Low();				/* enable device */
	Send_Byte(0x66);
	CE_High();				/* disable device */
}




/************************************************************************/
/* PROCEDURE: Reset                                     		*/
/*									*/
/* This procedure resets the device in to normal operating Ready mode.	*/
/*									*/
/************************************************************************/
void Reset()
{
	CE_Low();				/* enable device */
	SendSQI_Byte(0x99);
	CE_High();				/* disable device */
}

void SPI_Reset()
{
	CE_Low();				/* enable device */
	Send_Byte(0x99);
	CE_High();				/* disable device */
}


/************************************************************************/
/* PROCEDURE: En_QIO                                    		*/
/*									*/
/* This procedure enables quad I/O operation.           		*/
/************************************************************************/
void En_QIO()
{
	CE_Low();				/* enable device */
	Send_Byte(0x38);
	CE_High();				/* disable device */
}


/************************************************************************/
/* PROCEDURE: Reset_QIO                                 		*/
/*									*/
/* This procedure resets the device to 1-bit SPI protocol operation.    */
/************************************************************************/
void Reset_QIO()
{
	CE_Low();				/* enable device */
	SendSQI_Byte(0xff);
	CE_High();				/* disable device */
}

void SPI_Reset_QIO()
{
	CE_Low();				/* enable device */
	Send_Byte(0xff);
	CE_High();				/* disable device */
}




/************************************************************************/
/* PROCEDURE: Write_Suspend						*/
/*									*/
/* This procedure suspends Program/Erase operation.			*/
/************************************************************************/
void Write_Suspend()
{
	CE_Low();				/* enable device */
	SendSQI_Byte(0xb0);
	CE_High();				/* disable device */
}
void SPI_Write_Suspend()
{
	CE_Low();				/* enable device */
	Send_Byte(0xb0);
	CE_High();				/* disable device */
}



/************************************************************************/
/* PROCEDURE: Write_Resume						*/
/*									*/
/* This procedure resumes Program/Erase operation.			*/
/************************************************************************/
void Write_Resume()
{
	CE_Low();				/* enable device */
	SendSQI_Byte(0x30);
	CE_High();				/* disable device */
}
void SPI_Write_Resume()
{
	CE_Low();				/* enable device */
	Send_Byte(0x30);
	CE_High();				/* disable device */
}



/************************************************************************/
/* PROCEDURE: Write_Status_Register					*/
/*									*/
/* This procedure resumes Program/Erase operation.			*/
/************************************************************************/
void Write_Status_Register(unsigned int data1, unsigned char datalen)
{	   //For data1 - top 8 bits are status reg bits , lower 8 bits are configuration reg bits
	CE_Low();				/* enable device */
	SendSQI_Byte(0x01);
	SendSQI_Byte((data1>>8)&0xff);
	if (datalen==2)
	{
		SendSQI_Byte((data1)&0xff);
	}

	CE_High();				/* disable device */
}
void SPI_Write_Status_Register(unsigned int data1, unsigned char datalen)
{	  //For data1 - top 8 bits are status reg bits , lower 8 bits are configuration reg bits
	CE_Low();				/* enable device */
	Send_Byte(0x01);
	Send_Byte((data1>>8)&0xff);
	if (datalen==2)
	{
		Send_Byte((data1)&0xff);
	}

	CE_High();				/* disable device */
}


 /************************************************************************/
/* PROCEDURE:	ReadSID	(Read Security ID)				*/
/*									*/
/* This procedure reads the security ID					*/
/************************************************************************/
void ReadSID(unsigned char *security_ID, unsigned long Dst, unsigned long security_length)
{

	unsigned long i;
	i=0;
	 	if (security_length>2048)
	{ security_length=2048;}

	CE_Low();                               /* enable device */
	SendSQI_Byte(0x88);
	SendSQI_Byte((Dst>>8) & 0xFF);
	SendSQI_Byte(Dst & 0xFF);
	SendSQI_Byte(Dst & 0xFF);              //dummy
	SendSQI_Byte(Dst & 0xFF);              //dummy
 	SendSQI_Byte(Dst & 0xFF);              //dummy

	for (i=0;i<security_length;i++)
	{
		*security_ID = GetSQI_Byte();
		++security_ID;
	}
	CE_High();                              /* disable device */
}

void SPI_ReadSID(unsigned char *security_ID, unsigned long Dst, unsigned long security_length)
{

	unsigned long i;
	i=0;
	 	if (security_length>2048)
	{ security_length=2048;}

	CE_Low();			/* enable device */
	Send_Byte(0x88);
	Send_Byte((Dst>>8) & 0xFF);
	Send_Byte(Dst & 0xFF);
	Send_Byte(Dst & 0xFF);  //dummy

	for (i=0;i<security_length;i++)
	{
		*security_ID = Get_Byte();
		security_ID++;
	}
	CE_High();			/* disable device */
}



/************************************************************************/
/* PROCEDURE:	ProgSID	(Program Security ID)                           */
/*									*/
/* This procedure programs the security ID				*/
/*									*/
/************************************************************************/
void ProgSID(unsigned char *security_ID, unsigned long Dst, unsigned long security_length)
{ 
	unsigned long i;

	i=0;

 	 	if (security_length>256)
	{ security_length=256;}

	CE_Low();			/* enable device */
	SendSQI_Byte(0xa5);
 	SendSQI_Byte((Dst>>8) & 0xFF);
	SendSQI_Byte(Dst & 0xFF);


	for (i=0;i<security_length;i++)
	{
	SendSQI_Byte(*security_ID);
	security_ID++;
	}




	CE_High();			/* disable device */
}

void SPI_ProgSID(unsigned char *security_ID, unsigned long Dst, unsigned long security_length)
{
	unsigned long i;

	i=0;

 	 	if (security_length>256)
	{ security_length=256;}

	CE_Low();			/* enable device */
	Send_Byte(0xa5);
 	Send_Byte((Dst>>8) & 0xFF);
	Send_Byte(Dst & 0xFF);


	for (i=0;i<security_length;i++)
	{
	Send_Byte(*security_ID);
	security_ID++;
	}


	CE_High();			/* disable device */
}




/************************************************************************/
/* PROCEDURE:	LockSID							*/
/*									*/
/* This procedure Locks the security ID setting				*/
/*									*/
/************************************************************************/
void LockSID()
{

	CE_Low();			/* enable device */
	SendSQI_Byte(0x85);
	CE_High();			/* disable device */
}
void SPI_LockSID()
{

	CE_Low();			/* enable device */
	Send_Byte(0x85);
	CE_High();			/* disable device */
}




  /************************************************************************/
/* PROCEDURE:	ReadBlockProtection			  		*/
/*									*/
/* This procedure reads block protection register			*/
/*									*/
/************************************************************************/
void ReadBlockProtection()
{
	
 	unsigned int i;
	i=0;

	CE_Low();			/* enable device */
	SendSQI_Byte(0x72);
	 SendSQI_Byte(0xff);
	for (i=6;i>0;i--)
	{	block_protection_6[i-1] = GetSQI_Byte();
	}
	CE_High();			/* disable device */
}
void SPI_ReadBlockProtection()
{
	
 	unsigned char i;
	i=0;

	CE_Low();			/* enable device */
	Send_Byte(0x72);

	for (i=6;i>0;i--)
	{	block_protection_6[i-1] = Get_Byte();
	}
	CE_High();			/* disable device */
}



/************************************************************************/
/* PROCEDURE:	WriteBlockProtection					*/
/*									*/
/* This procedure writes to block protection register			*/
/*									*/
/************************************************************************/
void WriteBlockProtection()
{
	
   	unsigned char i;
	i=0;

	CE_Low();			/* enable device */
	SendSQI_Byte(0x42); 		/* read command */

	for (i=6;i>0;i--)
	{
		SendSQI_Byte(block_protection_6[i-1]);
	}
	CE_High();			/* disable device */
}

void SPI_WriteBlockProtection()
{

   	unsigned char i;
	i=0;

	CE_Low();			/* enable device */
	Send_Byte(0x42); 		/* read command */

	for (i=6;i>0;i--)
	{
		Send_Byte(block_protection_6[i-1]);
	}
	CE_High();			/* disable device */
}
/************************************************************************/
/* PROCEDURE:	Global Block Protection Unlock				*/
/*									*/
/* This procedure clears all block protection				*/
/************************************************************************/
void SPI_Global_Block_Protection_Unlock()
{

	CE_Low();			/* enable device */
	Send_Byte(0x98); 		/* read command */
	CE_High();			/* disable device */
}

void Global_Block_Protection_Unlock()
{

	CE_Low();			/* enable device */
	SendSQI_Byte(0x98); 		/* read command */
	CE_High();			/* disable device */
}
/************************************************************************/
/* PROCEDURE:	LockBlockProtection					*/
/*									*/
/* This procedure locks the block protection register			*/
/************************************************************************/

void LockBlockProtection()
{

	CE_Low();			/* enable device */
	SendSQI_Byte(0x8d); 		/* read command */
	CE_High();			/* disable device */
}

void SPI_LockBlockProtection()
{

	CE_Low();			/* enable device */
	Send_Byte(0x8d); 		/* read command */
	CE_High();			/* disable device */
}





/************************************************************************/
/* PROCEDURE:	Non Volatile Write Lock Protection			*/
/*									*/
/* This procedure writes to block protection register			*/
/*									*/
/************************************************************************/
void NonVolWriteLockProtection()
{
	
   	unsigned char i;
	i=0;

	CE_Low();			/* enable device */
	SendSQI_Byte(0xE8); 		/* read command */

	for (i=6;i>0;i--)
	{
		SendSQI_Byte(block_protection_6[i-1]);
	}
	CE_High();			/* disable device */
}
void SPI_NonVolWriteLockProtection()
{

   	unsigned char i;
	i=0;

	CE_Low();			/* enable device */
	Send_Byte(0xE8); 		/* read command */

	for (i=6;i>0;i--)
	{
		Send_Byte(block_protection_6[i-1]);
	}
	CE_High();			/* disable device */
}


/************************************************************************/
/* PROCEDURE: Wait_Busy							*/
/*									*/
/* This procedure waits until device is no longer busy (can be used by	*/
/* Byte-Program, Page-Program, Sector-Erase, Block-Erase and Chip-Erase).*/
/************************************************************************/

void Wait_Busy()
{char Read_byte = 0x81;
	while (((Read_byte & 0x81) == 0x81) || ((Read_byte & 0x81) == 0x80) || ((Read_byte & 0x81) == 0x01))	// waste time until not busy
		Read_byte = Read_Status_Register();
}

void SPI_Wait_Busy()
{
	while ((SPI_Read_Status_Register()& 0x80) == 0x80)	// waste time until not busy
		SPI_Read_Status_Register();
}

/************************************************************************/
/* PROCEDURE:	SPI_SFDP_Read						*/
/*									*/
/* This procedure reads SFDP Table.					*/
/*									*/
/************************************************************************/
unsigned char SPI_SFDP_Read(unsigned long Dst)
{
	unsigned char byte = 0;

	CE_Low();                               /* enable device */
	Send_Byte(0x5A);                        /* read command */
	Send_Byte(((Dst & 0xFFFFFF) >> 16));	/* send 3 address bytes */
	Send_Byte(((Dst & 0xFFFF) >> 8));
	Send_Byte(Dst & 0xFF);
	Send_Byte(0xFF);                	/*dummy byte*/
	byte = Get_Byte();
	CE_High();                      	/* disable device */
	return byte;                    	/* return one byte read */
}


 /****************************************************/
 /* Main Function*/
 /*****************************************************/

int main()
{

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

int n;
n=0;
   i=0;
 j=0;
 Led_Stat=0x00;
// Read_Stat_Reg=0x00;
 status=1;  //1 means memory/code works and 0 means fault has occured.
 check=0;  //keeps track of code progress.
 tempcheck=1;
//highest_address=0xffffff;
highest_address=0x1FFFF;
deviceaddress=0;
devicedata=0;
Sw=0;


AD1PCFG = AD1PCFG | 0x01; //To enable SIO3 - makes RB0 a digital pin

 Portassign();
CE_High();
WP_High();
Reset_Hold_High();

 init();


 	i=0;
while (i<=0xFFFF)
{
 DisplayLED(0xFF);
	i++;
}



SPI_WREN();
	 tempdatalong=SPI_Read_Status_Register();
	 tempdatalong = tempdatalong<<8;
  tempdatalong = tempdatalong |(0x02);
	// tempdatalong = tempdatalong & ~(0x02);

SPI_Write_Status_Register(tempdatalong, 2);

       tempdata=SPI_Read_Configuration_Register();

// Test Jedec ID
      
/************* 1a. Test Jedec ID *********/
 
Jedec_ID_Read();

 if ((Manufacturer_Id == 0xbf)&& (Device_Type==0x26) && (Device_Id==0x51)&&(status==1))
{check=(check + 1);}
else
{status=0;}

 DisplayLED(check);
 					
 
 		
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

 SPI_WriteBlockProtection();
  SPI_Wait_Busy();
  SPI_WREN();
 	
SPI_Chip_Erase();	//Erase the chip


SPI_Wait_Busy();
 i=0;
SPI_WREN();
		

 while(i<highest_address)
 {	SPI_WREN();
DisplayLED(5);
SPI_Page_Program(i);
	SPI_Wait_Busy();
	i=i+256;
}

	  	SPI_WREN();


  j=0;
 while(j<highest_address)
 {
	
	   SPI_HighSpeed_Read_Cont(j, 64);
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


	DisplayLED(check);


/************* 3a. Do Sector Erase and verify that the sector is erased *********/

 SPI_WREN();
	SPI_Sector_Erase(0);	//Do Sector Erase
	SPI_Wait_Busy();

        j=0;
 	while (j<(4096))
	{
    	SPI_WREN();
  		SPI_Set_Burst(0x03);
		SPI_Read_Burst(j, 64);
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
  		SPI_Set_Burst(0x03);
		SPI_Read_Burst(j, 64);
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


	DisplayLED(check);

/************* 4a. Block Erase and verify that the Block is erased *********/

	SPI_WREN();
	SPI_Block_Erase(0);	//Do Sector Erase
	SPI_Wait_Busy();

        j=0;
 	while (j<(0x2000))
	{
    	SPI_WREN();
  		SPI_Set_Burst(0x03);
		SPI_Read_Burst(j, 64);
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
  		SPI_Set_Burst(0x03);
		SPI_Read_Burst(j, 64);
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
		{status=0;
		check|=0x44;}



	DisplayLED(check);

/************* 5a. Chip Erase and Verify Chip is erased*********/

	SPI_WREN();
	SPI_Chip_Erase();	//Do Sector Erase
	SPI_Wait_Busy();

        j=0;
 	while (j<highest_address)
	{
    	SPI_WREN();
  		SPI_Set_Burst(0x03);
		SPI_Read_Burst(j, 64);
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
		{check=(check+1);
		status=status&1;}
		else
		{status=0;}


// Test Quad J-ID

	DisplayLED(check);
        
/************* 1b. Test Quad ID *********/

Manufacturer_Id=0x00;
Device_Type=0x00;
Device_Id=0x00;	 		 

En_QIO();	 	//Serial Quad IO is now enabled
  WREN();	  
QuadJ_ID_Read();

 if ((Manufacturer_Id == 0xbf)&& (Device_Type==0x26) && (Device_Id==0x51)&&(status==1))
	{check=(check+1);
		status=status&1;}
		else
		{status=0;}

DisplayLED(check);

	
   

	DisplayLED(check);
/****** 2b.  Page program whole chip using SQI protocol and verify its OK *****/

 	i=0;
while (i<=255)
{
 data_256[i]=170;
	i++;
}

WREN();

block_protection_6[0]=0x00;
block_protection_6[1]=0x00;
block_protection_6[2]=0x00;
block_protection_6[3]=0x00;
block_protection_6[4]=0x00;
block_protection_6[5]=0x00;

 WriteBlockProtection();
  Wait_Busy();
  WREN();

Chip_Erase();	//Erase the chip


Wait_Busy();

WREN();

 i=0;
 while(i<highest_address)
 {	WREN();
Page_Program(i);
	Wait_Busy();
	i=i+256;
}

	  	WREN();


  j=0;
 while(j<highest_address)
 {
		   Set_Burst(0x03);
		Read_Burst(j, 64); 			//verify that it got programmed.
		 	Wait_Busy();

		 for (i=0;i<64;i++)
		 {
		 	if (data_256[i]==170)
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
DisplayLED(check);

/************* 3b.  Sector Erase and Verify sector is erased*********/

WREN();
	Sector_Erase(0);	//Do Sector Erase
	Wait_Busy();

        j=0;
 	while (j<(4096))
	{
    	WREN();
  		Set_Burst(0x03);
		Read_Burst(j, 64);
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
    	WREN();
  		Set_Burst(0x03);
		Read_Burst(j, 64);
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
		{status=0;
		check|=0x44;}

DisplayLED(check);

/************* 4b. Block Erase and verify that the Block is erased*********/

	WREN();
	Block_Erase(0);	//Do Sector Erase
	Wait_Busy();

        j=0;

 	while (j<(0x2000))
	{
    	WREN();
  		Set_Burst(0x03);
		Read_Burst(j, 64);
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
 	while (j<((0x3000)))
	{
    	WREN();
  		Set_Burst(0x03);
		Read_Burst(j, 64);
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
		{status=0;
		check|=0x44;}

 DisplayLED(check);
/************* 5b. Chip Erase and verify chip is erased *********/

	WREN();
	Chip_Erase();	//Do Sector Erase
	Wait_Busy();

        j=0;
 	while (j<highest_address)
	{
    	WREN();
  		Set_Burst(0x03);
		Read_Burst(j, 64);
	    for (k=0;k<63;k++)
		 {
		 	if (data_256[k]==0xff)			  // Verify that the values are correct
			{tempcheck&=1;}
			  else
			{ tempcheck=0;}
   		  }
   		  j=j+64;
	}

	  	if ((tempcheck == 1)&&(status==1))
		{check=(check+3);
		status=status&1;}
		else
		{status=0;}
DisplayLED(check);

ResetEn();
Reset();
 /***************** End of checking ******/
        Reset_QIO();

  Led_Stat=check;
  if (status==0) //means a failure has occured
  {
   	Led_Stat|=0x80;
  }

 while(1)


{
	DisplayLED(Led_Stat);
}

return 0;
}