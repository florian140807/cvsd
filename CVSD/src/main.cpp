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
	clock myClock(16000);
	w5500 myW5500;
	serial myUART;
	uint8_t mac[] = {144, 162, 218, 17, 52, 48};
	uint8_t ip[] = {192, 168, 2, 144};
	uint8_t gw[] = {192,168,2,1};
	uint8_t snmsk[] = {255,255,255.0};
	uint8_t sprt[] = {195, 80};
	uint8_t dprt[] = {195, 81};
	char* s;
	uint8_t tmp = 0;
	sei();
	// W5500 Rst
	W5500_CS;
	myW5500.transmitChar(0x00);
	myW5500.transmitChar(0x00);
	myW5500.transmitChar(0x04);
	myW5500.transmitChar(0x80);
	W5500_CDS;
	// W5500 Enables Ping request
	W5500_CS;
	myW5500.transmitChar(0x00);
	myW5500.transmitChar(0x00);
	myW5500.transmitChar(0x04);
	myW5500.transmitChar(0x32);
	W5500_CDS;
	// W5500 Set MAC
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x09); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0x90);	//Data Phase
	W5500_CDS;
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x0A); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0xA2);	//Data Phase
	W5500_CDS;
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x0B); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0xDA);	//Data Phase
	W5500_CDS;
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x0C); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0x11);	//Data Phase
	W5500_CDS;
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x0D); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0x34);	//Data Phase
	W5500_CDS;
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x0E); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0x30);	//Data Phase
	W5500_CDS;
	// W5500 Set GW
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x01); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0xC0);	//Data Phase
	W5500_CDS;
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x02); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0xA8);	//Data Phase
	W5500_CDS;
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x03); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0x02);	//Data Phase
	W5500_CDS;
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x04); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0x01);	//Data Phase
	W5500_CDS;
	// W5500 Set Subnetmask
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x05); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0xFF);	//Data Phase
	W5500_CDS;
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x06); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0xFF);	//Data Phase
	W5500_CDS;
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x07); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0xFF);	//Data Phase
	W5500_CDS;
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x08); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0x00);	//Data Phase
	W5500_CDS;
	// W5500 Set IP
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x0F); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0xC0);	//Data Phase
	W5500_CDS;
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x10); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0xA8);	//Data Phase
	W5500_CDS;
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x11); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0x02);	//Data Phase
	W5500_CDS;
	W5500_CS;
	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
	myW5500.transmitChar(0x12); 					//Address Phase bit 7-0
	myW5500.transmitChar(0x04);					//Control Phase
	myW5500.transmitChar(0x90);	//Data Phase
	W5500_CDS;

	while(1){
		W5500_CS;
		myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
		myW5500.transmitChar(0x10); 					//Address Phase bit 7-0
		myW5500.transmitChar(0x00);					//Control Phase
		tmp = myW5500.receive();
		W5500_CDS;
		myUART.serial_putstring(itoa(tmp,s,10));
	}
	return(0);
}


