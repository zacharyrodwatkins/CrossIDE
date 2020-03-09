#include <C8051F38X.h>

//  ~C51~

void longdelay (void)
{
	unsigned int i, j;
	for(j=0; j<3; j++)
		for(i=0; i<0x8000; i++);
}

void main (void)
{
    PCA0MD&=(~0x40) ; // DISABLE WDT: clear Watchdog Enable bit

    //Enable the Port I/O Crossbar
    P1SKIP|=0x04;  //skip LED pin in crossbar assignments
    XBR1=0x40;     //enable Crossbar
    P1MDOUT|=0x08; //make LED pin output push-pull
    P1MDIN|=0x08;  //make LED pin input mode digital
        
	while(1)
	{
		P1_3=1;        //Led on
		longdelay();
		P1_3=0;        //Led off
		longdelay();
	}
}
