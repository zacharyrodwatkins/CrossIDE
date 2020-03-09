// clon.c: This program copies the entire flash memory from one C8051F38C to another
//
// (c) 2008-2014, Jesus Calvino-Fraga
//
// Pin connections (LQFP32 packages):
//    Source C8051F38C:    Connects to:
//    P1.0 (26)        ->  C2CK (9) of target C8051F38C
//    P1.1 (25)        ->  C2D (10) of target C8051F38C
//    P1_2 (24)        ->  The go push-button.  Press to start clonning!
//    P1_3 (23)        ->  To 330 ohms + LED + base of pnp.  Emmiter to 5V, collector to REGIN (7) of target C8051F38C
//    P1_4 (22)        ->  Green LED + 330 ohms to 5V
//    P1_5 (21)        ->  Red LED + 330 ohms to 5V
//    REGIN (7)        ->  5V from voltage regulator + 0.1uF + 1.0uF in parallel
//    DGND  (3)        ->  GND (3) target C8051F38C
//    P0.4 (30)        ->  The TX pin connects to pin 11 of MAX232 + 1k ohm + Push-button to GND
//    P0.5 (29)        ->  The RX pin connects to pin 12 of MAX232
//    RST*  (9)        ->  Push-button to DGND

// Debug adapter header for the source C8051F38C (top view):
//          +---+---+
//       NC | 1 | 2 | NC
//          +---+---+
//       NC | 3 | 4 | C2D (10)
//          +---+---+
//       NC | 5 | 6 | NC
//          +---+---+
// C2CK (9) | 7 | 8 | NC
//          +---+---+
//  GND (3) | 9 | 10| USB power (5V) not used, but can power the source C8051F38C (pin 7)
//          +---+---+
   
//
// The next line clears the "C51 command line options:" field when compiling with CrossIDE
//  ~C51~  
  
#include <C8051F38x.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SYSCLK      48000000L  // SYSCLK frequency in Hz
#define BAUDRATE      115200L  // Baud rate of UART in bps

// FLASH and device information
#define  FLASH_SIZE        (0x10000L/4L)     // FLASH size
#define  NUM_PAGES         FLASH_SIZE/0x200L // Number of 512-byte FLASH pages
#define  BLOCK_SIZE        64                // The size of the read and write buffers in idata
#define  NUM_BLOCKS        (FLASH_SIZE/BLOCK_SIZE)
// Device ID should be 0x28 for C8051F38x
#define C8051F38x_ID       0x28

// C2 status return codes
#define  INVALID_COMMAND   0x00
#define  COMMAND_FAILED    0x02
#define  COMMAND_OK        0x0D

// C2 interface commands
#define  BLOCK_READ        0x06
#define  BLOCK_WRITE       0x07
#define  PAGE_ERASE        0x08
#define  DEVICE_ERASE      0x03

// C2 Registers
#define  FPDAT             0xAD
#define  FPCTL             0x02
#define  DEVICEID          0x00
#define  REVID             0x01

// C2 Signals
#define C2CK  P1_0
#define C2D   P1_1
#define FGO   P1_2 // Go push button
#define PWR   P1_3 // Power on/off for target controller 0:on
#define GLED  P1_4
#define YLED  P2_0
#define RLED  P1_5

// Misc constants
#define  LOW               0
#define  HIGH              1
#define  LEDON			   0
#define  LEDOFF            1
#define  PWRON             0
#define  PWROFF            1

// Program MACROS
#define  Poll_OutReady     while(!(C2_ReadAR()&0x01)) 
#define  Poll_InBusy       while((C2_ReadAR()&0x02))
#define  StrobeC2CK        C2CK = LOW; C2CK = HIGH
#define  C2D_DriverOn      P1MDOUT|=0x02; // Configures C2D pin as push-pull output
#define  C2D_DriverOff     P1MDOUT &= ~(0x02);P1 |= 0x02  // Configures C2D pin as open-drain input

unsigned char NUM_BYTES;
unsigned int  FLASH_ADDR;
unsigned char idata * C2_PTR;
unsigned char idata R_BUF[BLOCK_SIZE];
unsigned char idata W_BUF[BLOCK_SIZE];

// FLASH programming functions
void C2_Init(void);
unsigned char C2_GetDevID(void);
unsigned char C2_GetRevID(void);
char C2_BlockRead(void);
char C2_BlockWrite(void);
char C2_PageErase(void);
char C2_DeviceErase(void);

// Primitive C2 functions
void C2_Reset(void);
void C2_WriteAR(unsigned char);
unsigned char C2_ReadAR(void);
void C2_WriteDR(unsigned char);
unsigned char C2_ReadDR(void);

// Utility functions
void Timer3us(unsigned char);
void waitms(unsigned int);

char _c51_external_startup (void)
{
	PCA0MD&=(~0x40) ; // DISABLE WDT: clear Watchdog Enable bit
	VDM0CN=0x80;      // enable VDD monitor
	RSTSRC=0x02|0x04; // Enable reset on missing clock detector and VDD
	
	P0MDOUT|=0x10; // Enable Uart TX as push-pull output
	P1MDOUT|=0x31; // Initialize C2CK, RLED, and GLED as push-pull outputs
	P2MDOUT|=0x01; // Initialize GLED2 as push-pull outputs
	XBR0=0x01;     // Enable UART on P0.4(TX) and P0.5(RX)                     
	XBR1=0x40;     // Enable crossbar and weak pull-ups

	// CLKSEL&=0b_1111_1000; // Not needed because CLKSEL==0 after reset
	#if (SYSCLK == 12000000L)
		//CLKSEL|=0b_0000_0000;  // SYSCLK derived from the Internal High-Frequency Oscillator / 4 
	#elif (SYSCLK == 24000000L)
		CLKSEL|=0b_0000_0010; // SYSCLK derived from the Internal High-Frequency Oscillator / 2.
	#elif (SYSCLK == 48000000L)
		CLKSEL|=0b_0000_0011; // SYSCLK derived from the Internal High-Frequency Oscillator / 1.
	#else
		#error SYSCLK must be either 12000000L, 24000000L, or 48000000L
	#endif
	OSCICN |= 0x03;   // Configure internal oscillator for its maximum frequency

	// Configure serial port and baud rate
	#if (SYSCLK/BAUDRATE/2L/256L < 1)
		TH1 = 0x10000-((SYSCLK/BAUDRATE)/2L);
		CKCON &= ~0x0B;                  // T1M = 1; SCA1:0 = xx
		CKCON |=  0x08;
	#elif (SYSCLK/BAUDRATE/2L/256L < 4)
		TH1 = 0x10000-(SYSCLK/BAUDRATE/2L/4L);
		CKCON &= ~0x0B; // T1M = 0; SCA1:0 = 01                  
		CKCON |=  0x01;
	#elif (SYSCLK/BAUDRATE/2L/256L < 12)
		TH1 = 0x10000-(SYSCLK/BAUDRATE/2L/12L);
		CKCON &= ~0x0B; // T1M = 0; SCA1:0 = 00
	#else
		TH1 = -(SYSCLK/BAUDRATE/2/48);
		CKCON &= ~0x0B; // T1M = 0; SCA1:0 = 10
		CKCON |=  0x02;
	#endif
	TL1 = TH1;      // Init Timer1
	TMOD &= ~0xf0;  // TMOD: timer 1 in 8-bit autoreload
	TMOD |=  0x20;                       
	TR1 = 1; // Start Timer1
	SCON0 = 0x52;
	
	return 0;
}

void main (void)
{
	unsigned int i, j; // Misc. counters

	printf("\x1b[2JC8051F38C Clonner.\n"
	       "Based on Cygnal application note AN027 and Silicon Labs application note AN127\n"
		   "By Jesus Calvino-Fraga (2008-2014)\n\n");
	
	while(1)
	{
		RLED=LEDOFF;
		GLED=LEDOFF;
		YLED=LEDOFF;
		C2D_DriverOn;
		C2CK=LOW;
		C2D=LOW;
		PWR=PWROFF; // Power-off device
		
		while(FGO==1) // Blinking Green LED indicates new device can be inserted
		{
			GLED=(!GLED);
			YLED=(!YLED);
			waitms(300);
		}
		GLED=LEDON;
		YLED=LEDON;
		PWR=PWRON; // Power-on device
		waitms(300);
		C2D_DriverOff;
		C2CK=HIGH;
		while(FGO==0);
		GLED=LEDOFF;
		YLED=LEDOFF;
		
		// Read Device ID
		C2_Reset();        // Reset target
		j = C2_GetDevID(); 
		  
		printf("Checking for C8051F38C microcontroller...");
		if (j != C8051F38x_ID)
		{
			printf("\nERROR: C8051F38C device not present!\n");
			RLED=LEDON;
			goto the_end;
		}
		printf(" Done.\n");
		
		// Initiate C2 FLASH Programming
		C2_Reset();  // Start with a target device reset
		C2_Init();   // Enable FLASH programming via C2
		
		printf("Erasing the flash memory...");
		C2_DeviceErase(); // Erase entire code space
		printf(" Done.\n");
		
		printf("Verifying that the flash memory is blank...");
		// Read back entire FLASH memory (should be all '1's)
		for (i=0; i<NUM_BLOCKS; i++) // Perform block reads (0x0000 to 0xFBFF)
		{
			FLASH_ADDR = i*BLOCK_SIZE;    // Set target addresss
			NUM_BYTES = BLOCK_SIZE;       // Set number of bytes to read
			C2_PTR = R_BUF;               // Initialize C2 pointer to the read buffer
			C2_BlockRead();               // Initiate FLASH read            
			for (j=0; j<BLOCK_SIZE; j++)  // Check read data
			{
				if (R_BUF[j] != 0xFF)
				{
					printf("\nERROR: flash memory is not blank. @%04x=%02x\n", FLASH_ADDR+j, R_BUF[j]);
					RLED=LEDON;
					goto the_end;
				}
			}
		}
		printf(" Done.\n");

		printf("Copying from source to target...", FLASH_ADDR, FLASH_ADDR+BLOCK_SIZE-2);
		for (i=0; i<NUM_BLOCKS; i++) // Perform block write/reads
		{
			// Write FLASH block
			FLASH_ADDR = i*BLOCK_SIZE;
			NUM_BYTES = BLOCK_SIZE;
			memcpy(W_BUF, (code unsigned char *)FLASH_ADDR, BLOCK_SIZE);
			// Is the page to write full of 0xff?
			for (j=0; j<BLOCK_SIZE; j++)
			{
				if (W_BUF[j] != 0xFF) break;
			}
			if(j!=BLOCK_SIZE) // At least one byte is not 0xff, so write the block.
			{
				C2_PTR = W_BUF;
				C2_BlockWrite();
			
				// Read back FLASH block
				FLASH_ADDR = i*BLOCK_SIZE;
				NUM_BYTES = BLOCK_SIZE;
				C2_PTR = R_BUF;
				C2_BlockRead();
				
				if (memcmp(R_BUF, W_BUF, BLOCK_SIZE) != 0) // Verify written bytes
				{
					printf("\nERROR: Memory flash failed.\n");
					RLED=LEDON;
					goto the_end;
				}
			}
		}
	
		printf(" Done.\n");
		GLED=LEDON;
		YLED=LEDON;
		C2_Reset();
		printf("The YELLOW LED connected to the target C8051F38C should be blinking.\n\n");
				
		the_end:
		
		//Display the result of the flashing proccess until button pressed
		while(FGO==1);
		waitms(100); //Debounce...
		while(FGO==0);
		waitms(100); //Debounce...
	}
}   

// FLASH Programming Routines (High Level):
//
// These high-level routines perform the FLASH Programming Interface (FPI)
// command sequences.

void C2_WriteSFR (unsigned char sfraddress, unsigned char sfrdata)
{
   C2_WriteAR (sfraddress);
   C2_WriteDR (sfrdata);
   Poll_InBusy; // Wait for input acknowledge
}

// C2_Init: Initializes the C2 Interface for FLASH programming
void C2_Init(void)
{
   C2_Reset();    // Reset the target device
   Timer3us(2);   // Delay for at least 2us
 
   // FPCTL: Flash Programming Control Register.
   // This register is used to enable Flash programming via the C2 interface. To enable C2
   // Flash programming, the following codes must be written in order: 0x02, 0x01. Note
   // that once C2 Flash programming is enabled, a system reset must be issued to
   // resume normal operation.
   
   C2_WriteAR(FPCTL); // Target the C2 FLASH Programming Control register (FPCTL)
   C2_WriteDR(0x02);  // Write the first key code to enable C2 FLASH programming
   C2_WriteDR(0x01);  // Write the second key code to enable C2 FLASH programming
   waitms(20);        // Delay for at least 20ms to ensure the target is ready for C2 FLASH programming
   
   // C8051F38x Device-Specific Programming Sequences.  This comes from
   // Silabs' Application Note AN127:
   C2_WriteSFR(0xB6, 0x90);
   C2_WriteSFR(0xFF, 0x80);
   C2_WriteSFR(0xEF, 0x02);
   C2_WriteSFR(0xB2, 0x83);
}

// C2_GetDevID:  Reads the target Device ID register
unsigned char C2_GetDevID(void)
{
   C2_WriteAR(DEVICEID); // Select DeviceID register for C2 Data register accesses
   return C2_ReadDR();   // Read and return the DeviceID register
}

// C2_GetRevID: Reads Revision ID register
unsigned char C2_GetRevID(void)
{
   C2_WriteAR(REVID);   // Select REVID regsiter for C2 Data register accesses
   return C2_ReadDR();  // Read and return the DeviceID register
}

// C2_BlockRead:
// - Reads a block of FLASH memory starting at <FLASH_ADDR>
// - The size of the block is defined by <NUM_BYTES>
// - Stores the read data at the location targeted by the pointer <C2_PTR>
// - Assumes that FLASH accesses via C2 have been enabled prior to the function call
// - Function call returns a '1' if successful; returns a '0' if unsuccessful
//
char C2_BlockRead(void)
{
   unsigned char i;        // Counter
   unsigned char status;   // FPI status information holder

   C2_WriteAR(FPDAT);      // Select the FLASH Programming Data register for C2 Data register accesses
   C2_WriteDR(BLOCK_READ); // Send FLASH block read command
   Poll_InBusy;            // Wait for input acknowledge

   // Check status before starting FLASH access sequence
   Poll_OutReady;                      // Wait for status information
   status = C2_ReadDR();               // Read FLASH programming interface status
   if (status != COMMAND_OK) return 0; // Exit and indicate error
   
   C2_WriteDR(FLASH_ADDR >> 8);        // Send address high byte to FPDAT
   Poll_InBusy;                        // Wait for input acknowledge
   C2_WriteDR(FLASH_ADDR & 0x00FF);    // Send address low byte to FPDAT
   Poll_InBusy;                        // Wait for input acknowledge
   C2_WriteDR(NUM_BYTES);              // Send block size
   Poll_InBusy;                        // Wait for input acknowledge

   // Check status before reading FLASH block
   Poll_OutReady;                      // Wait for status information
   status = C2_ReadDR();               // Read FLASH programming interface status
   if (status != COMMAND_OK)
      return 0;                        // Exit and indicate error
   
   // Read FLASH block
   for (i=0;i<NUM_BYTES;i++)
   {
      Poll_OutReady;                   // Wait for data ready indicator
      *C2_PTR++ = C2_ReadDR();         // Read data from the FPDAT register
   }
   return 1;                           // Exit and indicate success
}

// C2_BlockWrite:
// - Writes a block of FLASH memory starting at <FLASH_ADDR>
// - The size of the block is defined by <NUM_BYTES>
// - Writes the block stored at the location targetted by <C2_PTR>
// - Assumes that FLASH accesses via C2 have been enabled prior to the function call
// - Function call returns a '1' if successful; returns a '0' if unsuccessful
//
char C2_BlockWrite(void)
{
   unsigned char i;                    // Counter
   unsigned char status;               // FPI status information holder

   C2_WriteAR(FPDAT);                  // Select the FLASH Programming Data register 
                                       // for C2 Data register accesses
   C2_WriteDR(BLOCK_WRITE);            // Send FLASH block write command
   Poll_InBusy;                        // Wait for input acknowledge

   // Check status before starting FLASH access sequence
   Poll_OutReady;                      // Wait for status information
   status = C2_ReadDR();               // Read FLASH programming interface status
   if (status != COMMAND_OK)
      return 0;                        // Exit and indicate error

   C2_WriteDR(FLASH_ADDR >> 8);        // Send address high byte to FPDAT
   Poll_InBusy;                        // Wait for input acknowledge
   C2_WriteDR(FLASH_ADDR & 0x00FF);    // Send address low byte to FPDAT
   Poll_InBusy;                        // Wait for input acknowledge
   C2_WriteDR(NUM_BYTES);              // Send block size
   Poll_InBusy;                        // Wait for input acknolwedge

   // Check status before writing FLASH block
   Poll_OutReady;                      // Wait for status information
   status = C2_ReadDR();               // Read FLASH programming interface status
   if (status != COMMAND_OK)
      return 0;                        // Exit and indicate error

   // Write FLASH block
   for (i=0;i<NUM_BYTES;i++)
   {
      C2_WriteDR(*C2_PTR++);           // Write data to the FPDAT register
      Poll_InBusy;                     // Wait for input acknowledge
   }   

   Poll_OutReady;                      // Wait for last FLASH write to complete
   return 1;                           // Exit and indicate success
}

// C2_PageErase:
// - Erases a 512-byte FLASH page
// - Targets the FLASH page containing the address <FLASH_ADDR>
// - Assumes that FLASH accesses via C2 have been enabled prior to the function call
// - Function call returns a '1' if successful; returns a '0' if unsuccessful
char C2_PageErase(void)
{
   unsigned char page;                 // Target FLASH page
   unsigned char status;               // FPI status information holder

   page=(unsigned char)(FLASH_ADDR>>9);// <page> is the 512-byte sector containing the target <FLASH_ADDR>.

   if (page >= (NUM_PAGES-2))          // Check that target page is within range (NUM_PAGES minus 2 for reserved area)
      return 0;                        // Indicate error if out of range
   C2_WriteAR(FPDAT);                  // Select the FLASH Programming Data register for C2 Data register accesses
   C2_WriteDR(PAGE_ERASE);             // Send FLASH page erase command Wait for input acknowledge

   // Check status before starting FLASH access sequence
   Poll_OutReady;                      // Wait for status information
   status = C2_ReadDR();               // Read FLASH programming interface status
   if (status != COMMAND_OK)
      return 0;                        // Exit and indicate error
   
   C2_WriteDR(page);                   // Send FLASH page number
   Poll_InBusy;                        // Wait for input acknowledge

   Poll_OutReady;                      // Wait for ready indicator
   status = C2_ReadDR();               // Read FLASH programming interface status
   if (status != COMMAND_OK)
      return 0;                        // Exit and indicate error
   
   C2_WriteDR(0x00);                   // Dummy write to initiate erase
   Poll_InBusy;                        // Wait for input acknowledge

   Poll_OutReady;                      // Wait for erase operation to complete
   return 1;                           // Exit and indicate success
}

// C2_Device_Erase:
// - Erases the entire FLASH memory space
// - Assumes that FLASH accesses via C2 have been enabled prior to the function call
// - Function call returns a '1' if successful; returns a '0' if unsuccessful
char C2_DeviceErase(void)
{
   unsigned char status;       // FPI status information holder

   C2_WriteAR(FPDAT);          // Select the FLASH Programming Data register for C2 Data register accesses
   C2_WriteDR(DEVICE_ERASE);   // Send Device Erase command
   Poll_InBusy;                // Wait for input acknowledge

   // Check status before starting FLASH access sequence
   Poll_OutReady;               // Wait for status information
   status = C2_ReadDR();        // Read FLASH programming interface status
   if (status != COMMAND_OK)
      return 0;                 // Exit and indicate error

   // Send a three-byte arming sequence to enable the device erase. If the sequence
   // is not received correctly, the command will be ignored.
   // Sequence: 0xDE, 0xAD, 0xA5.
   C2_WriteDR(0xDE);  // Arming sequence command 1
   Poll_InBusy;       // Wait for input acknowledge

   C2_WriteDR(0xAD);  // Arming sequence command 2
   Poll_InBusy;       // Wait for input acknowledge

   C2_WriteDR(0xA5);  // Arming sequence command 3
   Poll_InBusy;       // Wait for input acknowledge

   Poll_OutReady;     // Wait for erase operation to complete

   return 1;          // Exit and indicate success
}

// Performs a C2 Address register read and returns the 8-bit register content
unsigned char C2_ReadAR(void)
{
   unsigned char i;
   unsigned char addr;

   // START field
   StrobeC2CK; // Strobe C2CK with C2D driver disabled
   
   // INS field (10b, LSB first)
   C2D = LOW;                       
   C2D_DriverOn; // Enable C2D driver (output)
   StrobeC2CK;
   C2D = HIGH;
   StrobeC2CK;

   C2D_DriverOff; // Disable C2D driver (input)

   // ADDRESS field
   addr = 0;
   for (i=0;i<8;i++) // Shift in 8 bit ADDRESS field LSB-first
   {
      addr >>= 1;                   
      StrobeC2CK;     
      if (C2D)
         addr |= 0x80;
   }              
   
   // STOP field
   StrobeC2CK; // Strobe C2CK with C2D driver disabled
   
   return addr; // Return Address register read value
}

// Performs a C2 Address register write (writes the <addr> input to Address register)
void C2_WriteAR(unsigned char addr)
{
   unsigned char i;
   
   // START field
   StrobeC2CK; // Strobe C2CK with C2D driver disabled

   // INS field (11b, LSB first)
   C2D = HIGH;             
   C2D_DriverOn;
   StrobeC2CK; 
   C2D = HIGH;
   StrobeC2CK;
   
   // Shift out 8-bit ADDRESS field
   for(i=0;i<8;i++)
   {
      C2D = (addr & 0x01);
      StrobeC2CK;
      addr >>= 1;
   }

   // STOP field
   C2D_DriverOff;
   StrobeC2CK;

   return;
}

// Performs a C2 Data register read and returns the 8-bit register content
unsigned char C2_ReadDR(void)
{
   unsigned char i;
   unsigned char dat; // Data register read content

   // START field
   StrobeC2CK; // Strobe C2CK with C2D driver disabled

   // INS field (00b, LSB first)
   C2D = LOW;
   C2D_DriverOn;
   StrobeC2CK;
   C2D = LOW;
   StrobeC2CK;

   // LENGTH field (00b -> 1 byte)
   C2D = LOW;
   StrobeC2CK;
   C2D = LOW;
   StrobeC2CK;

   // WAIT field
   C2D_DriverOff;
   do
   {
      StrobeC2CK;
   }
   while (!C2D); // Strobe C2CK until target transmits a '1'

   // DATA field
   dat = 0;
   for (i=0;i<8;i++) // Shift in 8-bit DATA field LSB-first
   {
      dat >>= 1;
      StrobeC2CK;
      if (C2D)
         dat  |= 0x80;
   }

   // STOP field
   StrobeC2CK;
   
   return dat;
}

// Performs a C2 Data register write (writes <dat> input to data register)
void C2_WriteDR(unsigned char dat)
{
   unsigned char i;
   
   // START field
   StrobeC2CK; // Strobe C2CK with C2D driver disabled

   // INS field (01b, LSB first)
   C2D = HIGH;
   C2D_DriverOn;
   StrobeC2CK;
   C2D = LOW;
   StrobeC2CK;
   
   // LENGTH field (00b -> 1 byte)
   C2D = LOW;
   StrobeC2CK;
   C2D = LOW;
   StrobeC2CK;
   
   // DATA field
   for (i=0;i<8;i++) // Shift out 8-bit DATA field LSB-first
   {
      C2D = (dat & 0x01);
      StrobeC2CK;
      dat >>= 1;
   }

   // WAIT field
   C2D_DriverOff; // Disable C2D driver for input
   do
   {
      StrobeC2CK; // Strobe C2CK until target transmits a '1'
   }
   while (!C2D);

   // STOP field
   StrobeC2CK; // Strobe C2CK with C2D driver disabled
   
   return;
}                    
                  
// Performs a target device reset by pulling the C2CK pin low for >20us
void C2_Reset(void)
{
   C2CK = LOW;   // Put target device in reset state by pulling
   Timer3us(20); // C2CK low for >20us
   C2CK = HIGH;  // Release target device from reset
}

// Uses Timer3 to delay <us> micro-seconds. 
void Timer3us(unsigned char us)
{
	unsigned char i;               // usec counter
	
	// The input for Timer 3 is selected as SYSCLK by setting T3ML (bit 6) of CKCON:
	CKCON|=0b_0100_0000;
	
	TMR3RL = (-(SYSCLK)/1000000L); // Set Timer3 to overflow in 1us.
	TMR3 = TMR3RL;                 // Initialize Timer3 for first overflow
	
	TMR3CN = 0x04;                 // Sart Timer3 and clear overflow flag
	for (i = 0; i < us; i++)       // Count <us> overflows
	{
		while (!(TMR3CN & 0x80));  // Wait for overflow
		TMR3CN &= ~(0x80);         // Clear overflow indicator
	}
	TMR3CN = 0 ;                   // Stop Timer3 and clear overflow flag
}

void waitms (unsigned int ms)
{
	unsigned int j;
	unsigned char k;
	for(j=0; j<ms; j++)
		for (k=0; k<4; k++) Timer3us(250);
}
