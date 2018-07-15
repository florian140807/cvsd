/*
 * main.cpp
 *
 *  Created on: 30.03.2018
 *      Author: Florian
 *      20180409: move to git
 *      20180409: even more moved to online git
 */



#include "cvsd.h"

//extern volatile bool bit_ready;
//extern volatile bool byte_ready;
//extern volatile bool packet_ready;
extern volatile uint8_t ready_state;


int main(void){
	PRR0 &= ~(1<<PRSPI);
	DDRC = 0xC0;		// Pin PC7 und PC6 als Ausgang (LED) initialisieren
	DDRB = 0x46;		// Pin PB6 als Ausgang initialisieren
	DDRD = 0xC0;		// Pin PD7 und PD6 als Ausgang initialisieren
	DDRE = 0x40;		// Pin PE6 als Ausgang initialisieren
	bool enc_out_state =0;
	uint8_t enc_byte=0;
	uint16_t freesize = 0;
	uint16_t dst_ptr =PAYLOADSTARTPTR;
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

	//myUART.usart_send_int(myW5500.readSnTX_WR(0));



	while(1){
		//myW5500.send_data_processing(0,(uint8_t *) &myIENA.header,sizeof(myIENA.header));
		switch(ready_state){
		case 1:{
			TOGGLE1;
			FX_ENC_DCLK;
			enc_out_state = (PINB & (1 << PB7));
			enc_byte = enc_out_state << 1;
			//myUART.usart_send_int((uint16_t)enc_byte);
			//bit_ready=0;
			//myW5500.send_data_processing(0,(uint8_t *) myW5500.readSnTX_WR(0),sizeof(myW5500.readSnTX_WR(0)));
			//myW5500.writeSnCR(0,Sock_SEND);
			ready_state=0;
			break;
		}
		case 2:{
			TOGGLE2;
			//myW5500.send_data_processing_offset(0,dst_ptr,(uint8_t *) dstPort,sizeof(dstPort));
			//myW5500.writeSnCR(0,Sock_SEND);
			//dst_ptr = myW5500.readSnTX_WR(0);
			//myW5500.send_data_processing(0,(uint8_t *) ip_addr,sizeof(ip_addr));
			myUART.usart_send_int((uint16_t)enc_byte);
			enc_byte = 0;
//			dst_ptr++;
			//copy byte to next free tx buffer ptr
			//byte_ready = 0;
			//inc tx buffer ptr
			ready_state=0;
			break;
		}
		case 3:{
//			myW5500.send_data_processing_offset(0,0,(uint8_t *) &myIENA.header,sizeof(myIENA.header));
//			myW5500.send_data_processing_offset(0,dst_ptr,(uint8_t *) dstPort,sizeof(dstPort));
//			myW5500.writeSnCR(0,Sock_SEND);
			//determine header time; Achtung: Zeit muss korrigiert werden auf den ersten Sample im Packet
			//myW5500.writeSnCR(0,Sock_SEND);
			TOGGLE3;
			ready_state=0;
			dst_ptr=PAYLOADSTARTPTR;
			break;
		}
		default:break;
		}
		//ready_state=0;
		//uint16_t dst_ptr = myW5500.readSnTX_WR(0);
		//freesize = myW5500.getTXFreeSize(0);
		//myUART.usart_send_int(freesize);
		//myUART.usart_send_int(myW5500.readSnTX_WR(0));
		//myW5500.send_data_processing(0,(uint8_t *) ip_addr,sizeof(ip_addr));
		//myW5500.send_data_processing(0,(uint8_t *) &myIENA.header,sizeof(myIENA.header));
		//myW5500.writeSnCR(0,Sock_SEND);
		//_delay_ms(100);
		//myIENA.header.hdr_sequence++;
		//myIENA.header.hdr_time++;
		//if(myW5500.readSnIR(0)==SnIR::SEND_OK) myW5500.writeSnCR(0,Sock_CLOSE);
		//myUART.usart_send_int(myW5500.readSnTX_RD(0));
		//myUART.usart_send_int((uint16_t) enc_out_state);
	}
	return(0);
}


