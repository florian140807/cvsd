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

	extern uint8_t enc_out_state;
//	uint8_t *shiftReg, tempReg=0;				/**< Hilfsregister */
//	shiftReg = &tempReg;						/**< Definition Schieberegister */
//	*shiftReg = 0;								/**< Initialisierung Schieberegister */


	uint8_t mac_addr[] = {0x90,0xA2,0xDA,0x11,0x34,0x30};
	uint8_t ip_addr[] = {192,168,2,144};
	uint8_t sub_mask[] = {255,255,255,0};
	uint8_t gtw_addr[] = {192,168,2,1};
	uint8_t sprt[] = {195, 80};
	uint8_t dprt[] = {195, 81};
	clock myClock(16000);
	W5500Class myW5500;
	myW5500.init();
	myW5500.writeMR(0x80);
	myW5500.writeGAR(gtw_addr);
	myW5500.writeSHAR(mac_addr);
	myW5500.writeSIPR(ip_addr);
	myW5500.writeSUBR(sub_mask);
	//START DEBUGGING PART
	char t[10];
	uint16_t tmp = 0;
	serial myUART;
	tmp = myClock.getrate();
	itoa(tmp,t,10);
	//DEBUGGING END
	sei();

	while(1){
		//myUART.usart_send_string(t);
		myUART.usart_send_char(enc_out_state);
			//*shiftReg |= (1<<7);
			//*shiftReg = (*shiftReg>>1);
	}
	return(0);
}


