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
	PRR0 &= ~(1<<PRSPI);
	DDRC = 0x80;		// Pin PC7 als Ausgang (LED) initialisieren
	DDRB = 0x46;		// Pin PB6 als Ausgang initialisieren
	DDRD = 0x40;		// Pin PD6 als Ausgang initialisieren
	uint8_t mac_addr[] = {0x90,0xA2,0xDA,0x11,0x34,0x30};
	uint8_t ip_addr[] = {192,168,2,144};
	uint8_t sub_mask[] = {255,255,255,0};
	uint8_t gtw_addr[] = {192,168,2,1};
	uint8_t sprt[] = {195, 80};
	uint8_t dprt[] = {195, 81};
	char s[7];
	uint8_t tmp = 0;
	clock myClock(16000);
	//w5500 myW5500;
	serial myUART;
	sei();
	// Setting the Wiznet W5100 Mode Register: 0x0000
//	myW5500.transmitWord(MR,0x80);            // MR = 0b10000000;
//	// Setting the Wiznet W5100 Gateway Address (GAR): 0x0001 to 0x0004
//	myW5500.transmitWord(GAR + 0,gtw_addr[0]);
//	myW5500.transmitWord(GAR + 1,gtw_addr[1]);
//	myW5500.transmitWord(GAR + 2,gtw_addr[2]);
//	myW5500.transmitWord(GAR + 3,gtw_addr[3]);
//
//	// Setting the Wiznet W5100 Source Address Register (SAR): 0x0009 to 0x000E
//	myW5500.transmitWord(SHAR + 0,mac_addr[0]);
//	myW5500.transmitWord(SHAR + 1,mac_addr[1]);
//	myW5500.transmitWord(SHAR + 2,mac_addr[2]);
//	myW5500.transmitWord(SHAR + 3,mac_addr[3]);
//	myW5500.transmitWord(SHAR + 4,mac_addr[4]);
//	myW5500.transmitWord(SHAR + 5,mac_addr[5]);
//
//	// Setting the Wiznet W5100 Sub Mask Address (SUBR): 0x0005 to 0x0008
//	myW5500.transmitWord(SUBR + 0,sub_mask[0]);
//	myW5500.transmitWord(SUBR + 1,sub_mask[1]);
//	myW5500.transmitWord(SUBR + 2,sub_mask[2]);
//	myW5500.transmitWord(SUBR + 3,sub_mask[3]);
//
//	// Setting the Wiznet W5100 IP Address (SIPR): 0x000F to 0x0012
//	myW5500.transmitWord(SIPR + 0,ip_addr[0]);
//	myW5500.transmitWord(SIPR + 1,ip_addr[1]);
//	myW5500.transmitWord(SIPR + 2,ip_addr[2]);
//	myW5500.transmitWord(SIPR + 3,ip_addr[3]);

	while(1){
//		W5500_CS;
//		myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
//		myW5500.transmitChar(0x0A); 					//Address Phase bit 7-0
//		myW5500.transmitChar(0x00);					//Control Phase
//		tmp = myW5500.receive();
//		W5500_CDS;
//		myUART.serial_putstring(itoa(tmp,s,10));
		TOGGLE_LED;
		_delay_ms(500);
	}
	return(0);
}


