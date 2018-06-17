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
	//DDRC = 0xff;		// Port C als Ausgang initialisieren
	DDRB = 0x50;		// Pin PB4 und PB6 als Ausgang initialisieren
	DDRD = 0x40;		// Pin PD6 als Ausgang initialisieren
	clock myClock(16000);
	w5500 myW5500;
	serial myUART;
	uint8_t mac[] = {144, 162, 218, 17, 52, 48};
	myW5500.SetSHAR(mac[5], mac[4], mac[3], mac[2], mac[1], mac[0]); // Init W5500 MAC
	uint8_t ip[] = {192, 168, 2, 144};
	myW5500.SetSIPR(ip[3], ip[2],ip[1], ip[0]);
	uint8_t gw[] = {192,168,2,1};
	myW5500.SetGAR(gw[3],gw[2],gw[1],gw[0]);
	uint8_t snmsk[] = {255,255,255.0};
	myW5500.SetSUBR(snmsk[3],snmsk[2],snmsk[1],snmsk[0]);
	uint8_t sprt[] = {195, 80};
	myW5500.SetPORT(sprt[1], sprt[0]);
	uint8_t dprt[] = {195, 81};
	myW5500.SetDstPORT(dprt[1],dprt[0]);
	char s[7];
	uint8_t tmp = 0;
	sei();
//	// W5500 Rst
//	W5500_CS;
//	myW5500.transmitChar(0x00);
//	myW5500.transmitChar(0x00);
//	myW5500.transmitChar(0x06);
//	myW5500.transmitChar(0x80);
//	W5500_CDS;
//	// W5500 Enables Ping request
//	W5500_CS;
//	myW5500.transmitChar(0x00);
//	myW5500.transmitChar(0x00);
//	myW5500.transmitChar(0x06);
//	myW5500.transmitChar(0x12);
//		W5500_CDS;
//	// W5500 Set MAC
//	W5500_CS;
//	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
//	myW5500.transmitChar(0x09); 					//Address Phase bit 7-0
//	myW5500.transmitChar(0x04);					//Control Phase
//	myW5500.transmitChar(myW5500.GetSHAR(0));	//Data Phase
//	myW5500.transmitChar(myW5500.GetSHAR(1));	//Data Phase
//	myW5500.transmitChar(myW5500.GetSHAR(2));	//Data Phase
//	myW5500.transmitChar(myW5500.GetSHAR(3));	//Data Phase
//	myW5500.transmitChar(myW5500.GetSHAR(4));	//Data Phase
//	myW5500.transmitChar(myW5500.GetSHAR(5));	//Data Phase
//	W5500_CDS;
//	// W5500 Set GW
//	W5500_CS;
//	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
//	myW5500.transmitChar(0x01); 					//Address Phase bit 7-0
//	myW5500.transmitChar(0x07);					//Control Phase
//	myW5500.transmitChar(myW5500.GetGAR(0));		//Data Phase
//	myW5500.transmitChar(myW5500.GetGAR(1));		//Data Phase
//	myW5500.transmitChar(myW5500.GetGAR(2));		//Data Phase
//	myW5500.transmitChar(myW5500.GetGAR(3));		//Data Phase
//	W5500_CDS;
//	// W5500 Set Subnetmask
//	W5500_CS;
//	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
//	myW5500.transmitChar(0x05); 					//Address Phase bit 7-0
//	myW5500.transmitChar(0x07);					//Control Phase
//	myW5500.transmitChar(myW5500.GetSUBR(0));		//Data Phase
//	myW5500.transmitChar(myW5500.GetSUBR(1));		//Data Phase
//	myW5500.transmitChar(myW5500.GetSUBR(2));		//Data Phase
//	myW5500.transmitChar(myW5500.GetSUBR(3));		//Data Phase
//	W5500_CDS;
//	// W5500 Set IP
//	W5500_CS;
//	myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
//	myW5500.transmitChar(0x0F); 					//Address Phase bit 7-0
//	myW5500.transmitChar(0x07);					//Control Phase
//	myW5500.transmitChar(myW5500.GetSIPR(0));		//Data Phase
//	myW5500.transmitChar(myW5500.GetSIPR(1));		//Data Phase
//	myW5500.transmitChar(myW5500.GetSIPR(2));		//Data Phase
//	myW5500.transmitChar(myW5500.GetSIPR(3));		//Data Phase
//	W5500_CDS;

	while(1){
//		W5500_CS;
//		myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
//		myW5500.transmitChar(0x0F); 					//Address Phase bit 7-0
//		myW5500.transmitChar(0x00);					//Control Phase
//		tmp = SPDR;
//		myUART.serial_putstring(itoa(tmp,s,10));
//		myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
//		myW5500.transmitChar(0x10); 					//Address Phase bit 7-0
//		myW5500.transmitChar(0x00);					//Control Phase
//		tmp = SPDR;
//		myUART.serial_putstring(itoa(tmp,s,10));
//		myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
//		myW5500.transmitChar(0x11); 					//Address Phase bit 7-0
//		myW5500.transmitChar(0x00);					//Control Phase
//		tmp = SPDR;
//		myUART.serial_putstring(itoa(tmp,s,10));
//		myW5500.transmitChar(0x00); 					//Address Phase bit 15-8
//		myW5500.transmitChar(0x12); 					//Address Phase bit 7-0
//		myW5500.transmitChar(0x00);					//Control Phase
//		tmp = SPDR;
//		myUART.serial_putstring(itoa(tmp,s,10));
//		W5500_CDS;
//		myUART.serial_putstring(itoa(myW5500.GetSIPR(0),s,10));
//		myUART.serial_putstring(itoa(myW5500.GetSIPR(1),s,10));
//		myUART.serial_putstring(itoa(myW5500.GetSIPR(2),s,10));
//		myUART.serial_putstring(itoa(myW5500.GetSIPR(3),s,10));
		// W5500 Reads PHYCFGR
//		W5500_CS;
//		myW5500.transmitChar(0x00);
//		myW5500.transmitChar(0x01);
//		myW5500.transmitChar(0x00);
//		W5500_CDS;
//		tmp = SPDR;
//		myUART.serial_putstring(itoa(tmp,s,10));
		W5500_CS;
		_delay_ms(2);
		W5500_CDS;
	}
	return(0);
}


