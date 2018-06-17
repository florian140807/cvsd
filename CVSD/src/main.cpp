/*
 * main.cpp
 *
 *  Created on: 30.03.2018
 *      Author: Florian
 *      20180409: move to git
 *      20180409: even more moved to online git
 */

#include "cvsd.h"

int main(void){
	DDRC = 0xff;		// Port C als Ausgang initialisieren
	DDRB = 0x10;		// Pin PB4 als Ausgang initialisieren
	DDRD = 0x40;		// Pin PD6 als Ausgang initialisieren
	clock myClock(64000);
	w5500 myW5500;
	serial myUART;
	myW5500.SetSHAR(0x90, 0xA2, 0xDA, 0x11, 0x34, 0x30); // Init W5500 MAC
	myW5500.SetSIPR(192, 168, 2, 144);
	myW5500.SetGAR(192,168,2,1);
	myW5500.SetSUBR(255,255,255,0);
	myW5500.SetPORT(0xC3, 0x50);
	myW5500.SetDstPORT(0xC3,0x51);
	unsigned char readback;
	sei();

	while(1){
		//readback = myW5500.transmitChar(myW5500.ip_addr[0]);
		//myUART.serial_send_int(readback);
		//readback = myW5500.transmitChar(myW5500.ip_addr[0]);
		myUART.serial_send_byte(myClock.getrate());
	}
	return(0);
}


