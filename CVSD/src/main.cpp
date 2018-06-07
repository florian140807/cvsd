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
	sei();

	while(1){

		myUART.serial_send_int(myClock.getrate());
	}
	return(0);
}

