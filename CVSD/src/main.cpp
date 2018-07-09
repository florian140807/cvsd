/*
 * main.cpp
 *
 *  Created on: 30.03.2018
 *      Author: Florian
 *      20180409: move to git
 *      20180409: even more moved to online git
 */



#include "cvsd.h"

extern volatile uint8_t enc_out_state;
extern volatile uint8_t bit_ready;
extern volatile uint8_t byte_ready;
extern volatile uint8_t packet_ready;

int main(void){
	PRR0 &= ~(1<<PRSPI);
	DDRC = 0x80;		// Pin PC7 als Ausgang (LED) initialisieren
	DDRB = 0x46;		// Pin PB6 als Ausgang initialisieren
	DDRD = 0x40;		// Pin PD6 als Ausgang initialisieren
	uint16_t freesize = 0;
	uint8_t mac_addr[] = {0x90,0xA2,0xDA,0x11,0x34,0x30};
	uint8_t ip_addr[] = {192,168,2,144};
	uint8_t remote_ip[] = {192,168,2,114};
	uint8_t sub_mask[] = {255,255,255,0};
	uint8_t gtw_addr[] = {192,168,2,1};
	uint16_t sPort = 50000;
	uint16_t dstPort = 50001;
	serial myUART;
	iena myIENA;
	clock myClock(16000);
	W5500Class myW5500;
	myW5500.init();
	myW5500.writeMR(MR::RST);
	myW5500.writeGAR(gtw_addr);
	myW5500.writeSHAR(mac_addr);
	myW5500.writeSIPR(ip_addr);
	myW5500.writeSUBR(sub_mask);



	while(myW5500.readSnSR(0)!=SnSR::UDP){
		myW5500.writeSnMR(0,SnMR::UDP);
		myW5500.writeSnPORT(0,sPort);
		myW5500.writeSnCR(0,Sock_OPEN);
	}
	//myW5500.writeSnCR(0,Sock_CLOSE);

	freesize = myW5500.getTXFreeSize(0);
	while(freesize < sizeof(myIENA.header)) freesize = myW5500.readSnTX_FSR(0);
	myW5500.writeSnDIPR(0,remote_ip);
	myW5500.writeSnDPORT(0,dstPort);

	sei();


	while(1){
		if(bit_ready){
			TOGGLE_LED;
		}
		if(byte_ready){
			//copy byte to next free tx buffer ptr
			byte_ready = 0;
			//inc tx buffer ptr
		}
		if(packet_ready){
			//determine header time; Achtung: Zeit muss korrigiert werden auf den ersten Sample im Packet
			//myW5500.writeSnCR(0,Sock_SEND);
			packet_ready = 0;
			//reset tx buffer ptr
		}
		//uint16_t dst_ptr = myW5500.readSnTX_WR(0);
		myUART.usart_send_int(freesize);
		myUART.usart_send_int(myW5500.readSnTX_WR(0));
		//myW5500.send_data_processing(0,(uint8_t *) ip_addr,sizeof(ip_addr));
		//myW5500.send_data_processing(0,(uint8_t *) &myIENA.header,sizeof(myIENA.header));
		//myW5500.writeSnCR(0,Sock_SEND);
		_delay_ms(100);
		//myIENA.header.hdr_sequence++;
		//myIENA.header.hdr_time++;
		//if(myW5500.readSnIR(0)==SnIR::SEND_OK) myW5500.writeSnCR(0,Sock_CLOSE);
		myUART.usart_send_int(myW5500.readSnTX_RD(0));
		//myUART.usart_send_int((uint16_t) enc_out_state);
	}
	return(0);
}


