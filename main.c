////////////////////////////////////////////////////////////
///	INCLUDES
////////////////////////////////////////////////////////////
#include <stdio.h>
#include <wiringPi.h>
#include "qlearning.h"

/*
	-- Raspberry Pi B+ Pinout table
	Link: https://it.pinout.xyz/pinout/pin17_alimentazione_a_33v
	
	*Left type*			*BCM pin*	*WiringPi pin*	*Right type*

	Alimentazione 3.3V		1,2			_,_			Alimentazione 5V
	BCM 2 (SDA)				3,4			8,_			Alimentazione 5V
	BCM 3 (SCL)				5,6			9,_			Massa
	BCM 4 (GPCLK0)			7,8			7,15		BCM 14 (TXD)
	Massa					9,10		_,16		BCM 15 (RXD)
	BCM 17					11,12		0,1			BCM 18 (PCM_C)
	BCM 27 (PCM_D)			13,14		2,_			Massa
	BCM 22					15,16		3,4			BCM 23
	Alimentazione 3.3V		17,18		_,5			BCM 24
	BCM 10 (MOSI)			19,20		12,_		Massa
	BCM 9 (MISO)			21,22		13,6		BCM 25
	BCM 11 (SCLK)			23,24		14,10		BCM 8 (CE0)
	Massa					25,26		_,11		BCM 7 (CE1)
	
	BCM 0 (ID_SD)			27,28		30,31		BCM 1 (ID_SC)
	BCM 5					29,30		21,_		Massa
	BCM 6					31,32		22,26		BCM 12
	BCM 13					33,34		23,_		Massa
	BCM 19 (MISO)			35,36		24,27		BCM 16
	BCM 26					37,38		25,28		BCM 20 (MOSI)
	Massa					39,40		_,29		BCM 21 (SCLK)
*/

int main(int argc, const char *argv[])
{
	printf("Hello World\n");

	wiringPiSetup();
	pinMode(27, OUTPUT);
	
	int wait_time = 1000;
	
	for (;;)
	{
		wait_time -= 10;
		if (wait_time <= 100) wait_time = 1000; 
		printf("%d\n", wait_time);
		digitalWrite(27, HIGH);
		delay(wait_time);
		digitalWrite(27, LOW);
		delay(wait_time);
	}

	return 0;
}
