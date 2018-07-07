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

	uint16_t freesize = 0;
	uint16_t data1 = 0xAAAA;
	uint8_t data2 = 0xBB;
	uint16_t *data1_ptr = &data1;
	uint16_t len1 = sizeof(data1);
	uint8_t *data2_ptr = &data2;
	uint16_t len2 = sizeof(data2);
	uint8_t mac_addr[] = {0x90,0xA2,0xDA,0x11,0x34,0x30};
	uint8_t ip_addr[] = {192,168,2,144};
	uint8_t remote_ip[] = {192,168,2,114};
	uint8_t sub_mask[] = {255,255,255,0};
	uint8_t gtw_addr[] = {192,168,2,1};
	uint16_t sPort = 50000;
	uint16_t dstPort = 50001;
	clock myClock(16000);
	W5500Class myW5500;
	myW5500.init();
	MR myModeregister;
	SnSR mySocketStatusRegister;
	SnMR mySocketModeRegister;
	SnIR myInterruptRegister;
	myW5500.writeMR(myModeregister.RST);
	myW5500.writeGAR(gtw_addr);
	myW5500.writeSHAR(mac_addr);
	myW5500.writeSIPR(ip_addr);
	myW5500.writeSUBR(sub_mask);


	while(myW5500.readSnSR(0)!=mySocketStatusRegister.UDP){
		myW5500.writeSnMR(0,mySocketModeRegister.UDP);
		myW5500.writeSnPORT(0,sPort);
		myW5500.writeSnCR(0,Sock_OPEN);
	}
	//myW5500.writeSnCR(0,Sock_CLOSE);

	//freesize = myW5500.readSnTX_FSR(0);
	freesize = myW5500.getTXFreeSize(0);
	while(freesize < len1) freesize = myW5500.readSnTX_FSR(0);
	myW5500.writeSnDIPR(0,remote_ip);
	myW5500.writeSnDPORT(0,dstPort);


	uint16_t txlen = 0;
	//START DEBUGGING PART
	char t[10];
	uint16_t tmp = 0;
	serial myUART;
	//tmp = myClock.getrate();
	tmp = freesize;
	itoa(tmp,t,10);
	//DEBUGGING END
	sei();

	while(1){
		//uint16_t dst_ptr = myW5500.readSnTX_WR(0);
		myUART.usart_send_string(t);
		myW5500.send_data_processing(0,&data2,len2);
		//myW5500.send_data_processing(0,&data2,len2);
		myW5500.writeSnCR(0,Sock_SEND);
		_delay_ms(10);
		myUART.usart_send_char(len2);
		if(myW5500.readSnIR(0)==myInterruptRegister.SEND_OK) myW5500.writeSnCR(0,Sock_CLOSE);
			//*shiftReg |= (1<<7);
			//*shiftReg = (*shiftReg>>1);
	}
	return(0);
}


