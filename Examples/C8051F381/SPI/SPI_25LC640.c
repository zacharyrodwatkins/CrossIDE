#include <stdio.h>
#include <stdlib.h>
#include <c8051f38x.h>

#define SYSCLK 24000000L    // Internal oscillator frequency in Hz
#define BAUDRATE 115200L
#define F_SCK_MAX 2000000L  // Max SCK freq (Hz)

// Microchip 25LC640 Slave EEPROM Parameters
#define  EEPROM_CAPACITY   8192

// Pins used:
// 	Pin 4: SCK
// 	Pin 3: MISO
// 	Pin 2: MOSI
// 	Pin 1: P0.3 to EEPROM chip enable
	
// EEPROM Instruction Set
#define  EEPROM_CMD_READ   0x03        // Read Command
#define  EEPROM_CMD_WRITE  0x02        // Write Command
#define  EEPROM_CMD_WRDI   0x04        // Reset Write Enable Latch Command
#define  EEPROM_CMD_WREN   0x06        // Set Write Enable Latch Command
#define  EEPROM_CMD_RDSR   0x05        // Read Status Register Command
#define  EEPROM_CMD_WRSR   0x01        // Write Status Register Command

char _c51_external_startup (void)
{
	PCA0MD&=(~0x40) ;    // DISABLE WDT: clear Watchdog Enable bit
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
	OSCICN |= 0x03; // Configure internal oscillator for its maximum frequency
	
	VDM0CN=0x80;       // enable VDD monitor
	RSTSRC=0x02|0x04;  // Enable reset on missing clock detector and VDD
	OSCICN|=0x03;      // Configure internal oscillator for its maximum frequency

	P0MDOUT=0b_00011101;//SCK, MOSI, P0.3, TX0 are puspull, all others open-drain
	XBR0=0b_00000011;//SPI0E=1, URT0E=1
	XBR1=0b_01000000;//XBARE=1
	
	// Configure the serial port
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
		TH1 = 0x10000-(SYSCLK/BAUDRATE/2/48);
		CKCON &= ~0x0B; // T1M = 0; SCA1:0 = 10
		CKCON |=  0x02;
	#endif
	
	TL1 = TH1;     // Init timer 1
	TMOD &= 0x0f;  // TMOD: timer 1 in 8-bit autoreload
	TMOD |= 0x20;                       
	TR1 = 1;       // Start timer1
	SCON = 0x52;

	// SPI inititialization
	SPI0CFG = 0b_01000000; //SPI in master mode
	SPI0CN  = 0b_00000001; //SPI enabled and in three wire mode
	SPI0CKR = (SYSCLK/(2*F_SCK_MAX))-1;
	
	return 0;
}

void Send_SPI_Byte (unsigned char x)
{
   SPI0DAT=x;
   while(!SPIF);
   SPIF=0;
}

void Delay (void)
{
	unsigned char j;
	for(j=0; j<10; j++);
}

void EEPROM_Write_Page (unsigned int address, unsigned char * buff, unsigned char n)
{
	int j;
   
	// Step1: Set the Write Enable Latch to 1
	P0_3= 0;
	Send_SPI_Byte(EEPROM_CMD_WREN);
	P0_3= 1;
	Delay();
	
	// Step2: Send the WRITE command
	P0_3=0;
	Send_SPI_Byte(EEPROM_CMD_WRITE);
	
	// Step3: Send the EEPROM destination address (MSB first)
	Send_SPI_Byte(address/0x100);
	Send_SPI_Byte(address%0x100);
	
	// Step4: Send the 32-byte buffer to write
	for(j=0; j<n; j++) Send_SPI_Byte(buff[j]);
	P0_3=1;
	Delay();
	
	// Step5: Poll on the Write In Progress (WIP) bit in Read Status Register
	do
	{
	  P0_3=0; // Activate Slave Select
	  Send_SPI_Byte(EEPROM_CMD_RDSR); // Send the Read Status Register command
	  Send_SPI_Byte(0); // Dummy write to output serial clock
	  P0_3=1; // Deactivate Slave Select after read
	  Delay();
	} while( (SPI0DAT & 0x01) == 0x01 );
}

unsigned char EEPROM_Read (unsigned int address)
{
   // Reading a byte from the EEPROM is a three-step operation.
   
   // Step1: Send the READ command
   P0_3=0;  // Activate Slave Select
   Send_SPI_Byte(EEPROM_CMD_READ);
   
   // Step3: Send the EEPROM destination address (MSB first)
   Send_SPI_Byte(address/0x100);
   Send_SPI_Byte(address%0x100);
   
   // Step3: Read the value returned
   Send_SPI_Byte(0);// Dummy write to output serial clock
   P0_3=1; // Deactivate Slave Select
   Delay();
   
   return SPI0DAT;
}

void main (void)
{
   unsigned int address;
   unsigned char test_byte;
   idata unsigned char buff[32];
   unsigned char j;
   
   puts("\r\nSPI EEPROM test program\r");
   puts("File: " __FILE__ "\r\nBuilt: " __DATE__ ", " __TIME__ "\r\n" ); 
   puts("                     0%  10%  20%  30%  40%  50%  60%  70%  80%  90%  100%\r");
   puts("                     !....!....!....!....!....!....!....!....!....!....!\r");
   printf_small("Filling with 0xFF's: ");

   for (address=0, j=0; address < EEPROM_CAPACITY; address++)
   {
      buff[j]=0xff;
      j++;
      if(j==32)
      {
         EEPROM_Write_Page (address-31, buff, 32);
         j=0;
      }

      if ((address % (EEPROM_CAPACITY/50)) == 0) putchar('*');
   }
   printf_small(" Done!\r\n");

   printf_small("          Verifying: ");
   for (address=0; address < EEPROM_CAPACITY; address++)
   {
      test_byte = EEPROM_Read (address);

      if ((address % (EEPROM_CAPACITY/50)) == 0) putchar('*');

      if (test_byte != 0xFF)
      {
         printf_small("  ERROR at %d\r\n", address);
         while (1);
      }
   }
   printf_small(" Done!\r\n");

   // Fill EEPROM with LSB of EEPROM addresses
   printf_small("   Filling sequence: ");
   for (address=0, j=0; address < EEPROM_CAPACITY; address++)
   {
      buff[j]= address & 0xFF;
      j++;
      if(j==32)
      {
         EEPROM_Write_Page (address-31, buff, 32);
         j=0;
      }

      if ((address % (EEPROM_CAPACITY/50)) == 0) putchar('*');
   }
   printf_small(" Done!\r\n");

   // Verify EEPROM with LSB of EEPROM addresses
   printf_small("          Verifying: ");
   for (address = 0; address < EEPROM_CAPACITY; address++)
   {
      test_byte = EEPROM_Read (address);

      if ((address % (EEPROM_CAPACITY/50)) == 0) putchar('*');

      if (test_byte != (address & 0xFF))
      {
         printf_small("Error at 0%d\r\n", address);
         while (1);
      }
   }

   printf_small(" Done!\r\n");
}


