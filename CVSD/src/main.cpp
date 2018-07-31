/*
 * main.cpp
 *
 *  Created on: 30.03.2018
 *      Author: Florian
 *      20180409: move to git
 *      20180409: even more moved to online git
 */



#include "cvsd.h"

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
	freesize = myW5500.getTXFreeSize(0);
	while(freesize < sizeof(myIENA.header)) freesize = myW5500.readSnTX_FSR(0);
	myW5500.writeSnDIPR(0,remote_ip);
	myW5500.writeSnDPORT(0,dstPort);

	sei();
	bool NewValAvailable = 0;
	bool StaleBit = 0;
	uint8_t ShiftCtr = 0;
	while(1){
		//FIXME: update IENA Header Time
		myW5500.send_data_processing(0,(uint8_t *) &myIENA.header,sizeof(myIENA.header));
		switch(ready_state){
		case 1:
			ready_state=0;
			enc_out_state = (PINB & (1 << FX_ENC_OUT));
			NewValAvailable = 1;
			break;
		default:break;
		}
		switch(NewValAvailable){
		case 1:
			NewValAvailable = 0;
			enc_byte = ((enc_byte << 1)|enc_out_state);
			StaleBit = 0;
			ShiftCtr ++;
			break;
		case 0:
			StaleBit = 1;
			break;
		default:break;
		}
		switch(ShiftCtr){
		case 7:
			myW5500.send_data_processing_offset(0,dst_ptr, &enc_byte,sizeof(enc_byte));
			dst_ptr++;
			ShiftCtr=0;
			TOGGLE2;
			break;
		default:break;
		}
		switch(dst_ptr){
		case (BYTESPERPACKET+PAYLOADSTARTPTR):
			myW5500.send_data_processing_offset(0,dst_ptr,(uint8_t *) &myIENA.footer,sizeof(myIENA.footer));
			myW5500.writeSnCR(0,Sock_SEND);
			dst_ptr = PAYLOADSTARTPTR;
			myIENA.header.hdr_sequence= (myIENA.header.hdr_sequence>>8)|((myIENA.header.hdr_sequence&0xff)<<8);
			myIENA.header.hdr_sequence++;
			myIENA.header.hdr_sequence= (myIENA.header.hdr_sequence>>8)|((myIENA.header.hdr_sequence&0xff)<<8);
			TOGGLE3;
			break;
		default:break;
		}
	}
	return(0);
}



