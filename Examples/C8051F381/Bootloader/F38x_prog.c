/////////////////////////////////////////////////////////////////////////////
//
//  F38x_prog.c:  Serial flash loader for the C8051F38x family of microcontrollers.
// 
// Copyright (C) 2013-2016  Jesus Calvino-Fraga, jesusc (at) ece.ubc.ca
// 
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the
// Free Software Foundation; either version 2, or (at your option) any
// later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
//
/////////////////////////////////////////////////////////////////////////////
//
// Compile using Visual C:
// cl F38x_prog.c
// 

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define EQ(X,Y)  (_stricmp(X, Y)==0)
#define NEQ(X,Y) (_stricmp(X, Y)!=0)

clock_t startm, stopm;
#define START if ( (startm = clock()) == -1) {printf("Error calling clock");}
#define STOP if ( (stopm = clock()) == -1) {printf("Error calling clock");}
#define PRINTTIME printf( "%.1f seconds.", ((double)stopm-startm)/CLOCKS_PER_SEC);

// For 64k devices:
// 512*2 bytes from 0xfc00 to 0xffff are reserved,
// 512 bytes are used as lock bits from 0xfa00 to
// 0xfbff, and 512 bytes from 0xf800 to 0xf9ff are
// used by the bootloader:
#define C8051F38x_64k_MEMSIZE (0x10000-0x400-0x200)
// For the other devices just the size of the bootloader is needed
#define C8051F38x_32k_MEMSIZE ((0x10000/2)-0x200)
#define C8051F38x_16k_MEMSIZE ((0x10000/4)-0x200)

unsigned char FlashBuff[C8051F38x_64k_MEMSIZE];
HANDLE hComm=INVALID_HANDLE_VALUE;
char m_FileName[MAX_PATH]="";
int SerialPort=1;
char m_idstr[4]="";
char m_Serial[0x100]="";
int m_memsize=0;
int m_timeout=15;
BOOL m_gotU=FALSE;

int OpenSerialPort (int Port, DWORD baud, BYTE parity, BYTE bits, BYTE stop)
{
	char sPort[16];
	DCB dcb;
	COMMTIMEOUTS Timeouts;

	sprintf(sPort, "\\\\.\\COM%d", Port);
	
	hComm = CreateFile(sPort, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (hComm == INVALID_HANDLE_VALUE)
	{
		return -1;
	}
	
	if (!GetCommState(hComm, &dcb))
	{
		printf("Failed in call to GetCommState()\n");
		fflush(stdout);
		return -1;
	}

	dcb.fAbortOnError=FALSE;
	dcb.BaudRate = baud; 
	dcb.Parity = parity;
	dcb.ByteSize = bits;
	dcb.StopBits = stop;
	dcb.fDsrSensitivity = FALSE;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;

	//Now that we have all the settings in place, make the changes
	if (!SetCommState(hComm, &dcb))
	{
		printf("Failed in call to SetCommState()\n");
		fflush(stdout);
		return -1;
	}	

	ZeroMemory(&Timeouts, sizeof(COMMTIMEOUTS));
	Timeouts.ReadIntervalTimeout = 250;
	Timeouts.ReadTotalTimeoutMultiplier = 10;
	Timeouts.ReadTotalTimeoutConstant = 250;
	Timeouts.WriteTotalTimeoutMultiplier = 10;
	Timeouts.WriteTotalTimeoutConstant = 250;
	if (!SetCommTimeouts(hComm, &Timeouts))
	{
		printf("Failed in call to SetCommTimeouts\n");
		fflush(stdout);
		return -1;
	}

	return 0;
}

int CloseSerialPort (void)
{
	BOOL bSuccess;
	bSuccess = CloseHandle(hComm);
    hComm = INVALID_HANDLE_VALUE;
    if (!bSuccess)
    {
		printf("Failed to close serial port, GetLastError:%d\n", GetLastError());
		fflush(stdout);
		return -1;
	}
	return 0;
}

// Functions to read write hex/bin files
int hex2dec (char hex_digit)
{
   int j;
   j=toupper(hex_digit)-'0';
   if (j>9) j -= 7;
   return j;
}

unsigned char GetByte(char * buffer)
{
	return hex2dec(buffer[0])*0x10+hex2dec(buffer[1]);
}

unsigned short GetWord(char * buffer)
{
	return	hex2dec(buffer[0])*0x1000+
			hex2dec(buffer[1])*0x100+
			hex2dec(buffer[2])*0x10+
			hex2dec(buffer[3]);
}

long filesize(FILE *stream)
{
   long curpos, length;

   curpos = ftell(stream);
   fseek(stream, 0L, SEEK_END);
   length = ftell(stream);
   fseek(stream, curpos, SEEK_SET);
   return length;
}

int ReadHexFile(char * filename)
{
	char buffer[1024];
	FILE * filein;
	int j, numbytes;
	unsigned char linesize, recordtype, rchksum, value;
	unsigned short address;
	int MaxAddress=0;
	int chksum;
	int line_counter=0;
	int numread=0;
	int LoadedBytes=0;

	//Set the buffer to its default value
	for(j=0; j<C8051F38x_64k_MEMSIZE; j++) FlashBuff[j]=0xff;

    if ( (filein=fopen(filename, "r")) == NULL )
    {
       printf("Error: Can't open file `%s`.\r\n", filename);
       fflush(stdout);
       return -1;
    }
    
	numbytes=filesize(filein);

    while(fgets(buffer, sizeof(buffer), filein)!=NULL)
    {
    	numread+=(strlen(buffer)+1);

    	line_counter++;
    	if(buffer[0]==':')
    	{
			linesize = GetByte(&buffer[1]);
			address = GetWord(&buffer[3]);
			recordtype = GetByte(&buffer[7]);
			rchksum = GetByte(&buffer[9]+(linesize*2));
			chksum=linesize+(address/0x100)+(address%0x100)+recordtype+rchksum;

			if (recordtype==1) break; /*End of record*/

			for(j=0; j<linesize; j++)
			{
				value=GetByte(&buffer[9]+(j*2));
				chksum+=value;
				if((address+j)<C8051F38x_64k_MEMSIZE)
				{
					FlashBuff[address+j]=value;
					LoadedBytes++;
				}
			}
			if(MaxAddress<(address+linesize-1)) MaxAddress=(address+linesize-1);

			if((chksum%0x100)!=0)
			{
				printf("ERROR: Bad checksum in file '%' at line %d\r\n", filename, line_counter);
				fflush(stdout);
				return -1;
			}
		}
    }
    fclose(filein);

	if(FlashBuff[0]!=0x02)
	{
		printf("ERROR: User program doesn't start with a 'ljmp' instruction.\r\n",
		        filename, line_counter);
		fflush(stdout);
		return -1;
	}
	
	printf("%s: loaded %d bytes\n", filename, LoadedBytes); 

    return MaxAddress;
}

BOOL PortWrRd(char x, DWORD delay)
{
	DWORD j;
    char s=0;
    WriteFile(hComm, &x, 1, &j, NULL);
    Sleep(delay+1);
    ReadFile(hComm, &s, 1, &j, NULL);

	return (s==x)?TRUE:FALSE;
}

BOOL PortWrStr(char * x, int sleeptime, int timeout)
{
	DWORD j;
    time_t ltime1, ltime2;
	char val[]="000";
	int baud=115200; // Fixed for this bootloader...
    char c='$';
	
	FlushFileBuffers(hComm);
	if (!WriteFile(hComm, x, strlen(x), &j, NULL))
	{
		printf("Failed in call to WriteFile()\n");
		fflush(stdout);
		return -1;
	}
	Sleep(sleeptime);

    time(&ltime2);
    ltime1=ltime2+(timeout?timeout:6);

    while((c!='.') && (ltime2<ltime1) )
    {
		if (!ReadFile(hComm, &c, 1, &j, NULL))
		{
			printf("Failed in call to ReadFile()\n");
			fflush(stdout);
			return -1;
		}

        if(j==1)
		{
			if(c!='.')
			{
				val[0]=val[1];
				val[1]=val[2];
				val[2]=c;
			}
		}
        
        time(&ltime2);
    }
    
	strcpy(m_idstr, val);
    return (c=='.')?TRUE:FALSE;
}

BOOL PortWrStr2(char * x, int sleeptime)
{
	return PortWrStr(x, sleeptime, 0);
}

BOOL PortWrStr1(char * x)
{
	return PortWrStr2(x, 0);
}

BOOL PrepareIntelLine(char * x, int address, int len) 
{
	int j;
	unsigned char chk_sum;
	char buff[0x300];
	BOOL toret=0;

	sprintf(x, ":%02X%04X00", len, address);
	chk_sum= (unsigned char) (len + (address%0x100) + (address/0x100));

	for (j=0; j<len; j++)
	{
		sprintf(buff, "%02X", FlashBuff[address+j]);
		chk_sum += (unsigned char) FlashBuff[address+j];
		strcat(x, buff);
		if (FlashBuff[address+j]!=0xff) toret=1; //Don't send empty lines
	}
	sprintf(buff,"%02X\r\n", (unsigned char)(0x100-chk_sum));
	strcat(x, buff);
	return toret;
}

// Scans all available serial ports looking for an activated bootloader
void FindPort(void)
{
	int portn;
	
   	printf("Checking serial ports");
   	fflush(stdout);
   	for(portn=255; portn>0; portn--)
   	{
	    if(OpenSerialPort(portn, 115200, NOPARITY, 8, ONESTOPBIT)==0)
	    {
	    	printf(".", portn); fflush(stdout);
        	if(PortWrRd('U', 0))
        	{
        		printf("\nUsing COM%d\n", portn);
        		fflush(stdout);
        		sprintf(m_Serial, "COM%d", portn);
        		m_gotU=TRUE;
        		CloseSerialPort();
        		return;
        	}
	    	CloseSerialPort();    
	    }
    }
    printf("\nERROR: Couldn't get a response from any serial port.\n", portn);
    fflush(stdout);
    exit(2);
}

void Flash(void) 
{
    int portn, baud, GoodU=0, Utries=0;
    time_t ltime1, ltime2;
    DWORD delay;
    MSG msg;
	char buff[0x300];
	char feedback[0x30];
	int j, hashcnt;
	//The bootloader can receive and store up to 64 bytes.
	#define LINESIZE 64

	if(ReadHexFile(m_FileName)<0)
    {
        printf("\nERROR: Could not load hex file '%s'.\n", m_FileName);
        fflush(stdout);
        return;
    }
    
	portn=atoi(&m_Serial[3]);
    baud=115200;
    delay=14000/baud;
    
    if(OpenSerialPort(portn, baud, NOPARITY, 8, ONESTOPBIT)!=0)
    {
        printf("ERROR: Could not open serial port '%s'.\n", m_Serial);
        fflush(stdout);
        return;
    }

	if(m_gotU==FALSE)
	{
	   	printf("Please activate boot loader...\n");
	   	fflush(stdout);
	}

    time(&ltime2);
    ltime1=ltime2+m_timeout;

    while(1)
    {
		if (ltime1<ltime2)
		{
			printf("ERROR: boot loader not activated after %d seconds. Aborting.\n", m_timeout);
			fflush(stdout);
			goto The_end;
		}
        if(PortWrRd('U', delay)) GoodU++;
        else GoodU=0;
        if(GoodU==20) break; //Assume we got the C8051F38x/EFM8UB2 bootloader running      
        time(&ltime2);
    }
    
	START; // Measure the time it takes to program the microcontroller
	
	//Identify the microcontroller
	if(!PortWrStr2(":00000003FD", 100 /*milliseconsds*/))
	{
		printf("ERROR: Part identification command failed.\n");
		fflush(stdout);
		goto The_end;
	}

	     if (strcmp(m_idstr, "380")==0) m_memsize=C8051F38x_64k_MEMSIZE;
	else if (strcmp(m_idstr, "381")==0)	m_memsize=C8051F38x_64k_MEMSIZE;
	else if (strcmp(m_idstr, "B64")==0) m_memsize=C8051F38x_64k_MEMSIZE;
	else if (strcmp(m_idstr, "382")==0) m_memsize=C8051F38x_32k_MEMSIZE;
	else if (strcmp(m_idstr, "B32")==0) m_memsize=C8051F38x_32k_MEMSIZE;
	else if (strcmp(m_idstr, "383")==0) m_memsize=C8051F38x_32k_MEMSIZE;
	else if (strcmp(m_idstr, "384")==0) m_memsize=C8051F38x_64k_MEMSIZE;
	else if (strcmp(m_idstr, "385")==0) m_memsize=C8051F38x_64k_MEMSIZE;
	else if (strcmp(m_idstr, "386")==0) m_memsize=C8051F38x_32k_MEMSIZE;
	else if (strcmp(m_idstr, "387")==0) m_memsize=C8051F38x_32k_MEMSIZE;
	else if (strcmp(m_idstr, "38C")==0) m_memsize=C8051F38x_16k_MEMSIZE;
	else m_memsize=0;

	if(m_memsize>0)
	{
		if(m_idstr[0]=='B')
		{
			printf("EFM8UB20F%sG detected.\n", &m_idstr[1]);
			fflush(stdout);
		}
		else
		{
			printf("C8051F%s detected.\n", m_idstr);
			fflush(stdout);
		}
	}
	else
	{
		printf("ERROR: Not a supported C8051F38x/EFM8UB2 with serial boot loader.\n");
		printf("This is the id received: `%s`.\n", m_idstr);
		fflush(stdout);
		goto The_end;
	}

	printf("Erasing flash memory... "); fflush(stdout);

	//Send erase flash command
	if(!PortWrStr(":00000004FC", 0, 5 /*seconds*/)) // 5 seconds should be more than enough...
	{
		printf("\nERROR: Flash erase command failed.\n");
		fflush(stdout);
		goto The_end;
	}

	printf("Done.\nWriting flash memory...\n"); fflush(stdout);
	for(j=0, hashcnt=0; j<m_memsize; j+=LINESIZE)
    {
		if(PrepareIntelLine(buff, j, LINESIZE))
		{
        	printf("#"); fflush(stdout);
        	hashcnt++;
        	if(hashcnt==60)
        	{
        		hashcnt=0;
        		printf("\n"); fflush(stdout);
        	}
			if(!PortWrStr2(buff, 0))
			{
                printf("ERROR: Flash program command failed.\n");
                fflush(stdout);
                goto The_end;
			}
		}
	}

	//Send the end record
	if(!PortWrStr1(":00000001FF"))
	{
		printf("\nERROR: Flash end failed.\n");
		fflush(stdout);
		goto The_end;
	}

    printf(" Done.\nActions completed in ");
    STOP;
	PRINTTIME;
	printf("\n");
	fflush(stdout);
	    
	sprintf(buff,"echo COM%d>COMPORT.inc", portn);
	system(buff);

The_end:
    CloseSerialPort();
}

void print_help (char * prn)
{
	printf("Usage example:\n"
	       "%s -COM3 somefile.hex (load flash memory with file 'somefile.hex' via COM3)\n"
	       "Options available:\n"
	       "   -COM[1 to 255] (use this serial port)\n"
	       "   -txx (boot loader activation timeout is xx seconds)\n"
	       "   -h (this help)\n"
	       , prn);
	fflush(stdout);
}

int main(int argc, char **argv)
{
	int j;

    printf("Serial flash programmer for the C8051F38x. (C) Jesus Calvino-Fraga (2012-2016)\n");
    fflush(stdout);
	
    for(j=1; j<argc; j++)
    {
    		 if(EQ("-h", argv[j])) {print_help(argv[0]); return 0;}
		else if(strnicmp("-com", argv[j], 4)==0) sprintf(m_Serial, "%s", &argv[j][1]);
		else if(strnicmp("-t", argv[j], 2)==0) m_timeout=atoi(&argv[j][2]);
    	else strcpy(m_FileName, argv[j]);
    }
    
    if(strlen(m_FileName)==0) {print_help(argv[0]); return 1;}
    if(strlen(m_Serial)==0) FindPort();
    Flash();
    return 0;
}
