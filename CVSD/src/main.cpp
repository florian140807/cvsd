/*
 * main.cpp
 *
 *  Created on: 30.03.2018
 *      Author: Florian
 *      20180409: move to git
 *      20180409: even more moved to online git
 */


#include "cvsd.h"

extern volatile bool bReady;
extern volatile bool bSkip;
extern volatile bool bStale;
extern volatile bool bProcessed;
extern volatile bool enc_out_state;
extern volatile uint8_t enc_byte;

void ComputeIENATime();

int main(void){
	PRR0 &= ~(1<<PRSPI);
	DDRC = 0xC0;		// Pin PC7 und PC6 als Ausgang (LED) initialisieren
	DDRB = 0x46;		// Pin PB6 als Ausgang initialisieren
	DDRD = 0xC0;		// Pin PD7 und PD6 als Ausgang initialisieren
	DDRE = 0x40;		// Pin PE6 als Ausgang initialisieren
	//bool enc_out_state =0;
	//uint8_t enc_byte=0;
	uint16_t freesize = 0;
	uint16_t dst_ptr =PAYLOADSTARTPTR;
	uint8_t mac_addr[] = {0x90,0xA2,0xDA,0x11,0x34,0x30};
	//Network Setting for Home
	uint8_t ip_addr[] = {192,168,2,144};
	uint8_t remote_ip[] = {192,168,2,114};
	uint8_t sub_mask[] = {255,255,255,0};
	uint8_t gtw_addr[] = {192,168,2,1};
	//Network Settings for Office
//	uint8_t ip_addr[] = {10,253,1,144};
//	uint8_t remote_ip[] = {10,253,255,255};
//	uint8_t sub_mask[] = {255,255,0,0};
//	uint8_t gtw_addr[] = {10,253,1,253};
	uint16_t sPort = 50000;
	uint16_t dstPort = 50001;
	serial myUART;
	iena myIENA;
	enc_clock myClock(FS);
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
	uint8_t ShiftCtr = 0;
	uint8_t ByteCntr = 0;
	uint8_t testctr = 0;
	uint64_t ll_hdr_time=22.5504e12;
	while(1){
		//FIXME: update IENA Header Time
		switch(bReady){
		case 1:
			//enc_out_state = (PINB & (1<<FX_ENC_OUT));
			//enc_byte = ((enc_byte << 1)|enc_out_state);
			ShiftCtr++;
			bReady=0;
			bProcessed=1;
			break;
		case 0:
			bStale=1;
			SETSTALE;
			break;
		default:break;
		}
			switch(ShiftCtr){
			case 7:
				dst_ptr = PAYLOADSTARTPTR + (1*ByteCntr);
				//enc_byte = (enc_byte>>4)|((enc_byte&0x0f)<<4);
				//myW5500.send_data_processing_offset(0,dst_ptr, &testctr ,sizeof(testctr));
				myW5500.send_data_processing_offset(0,dst_ptr, (uint8_t *)&enc_byte ,sizeof(enc_byte));
				ByteCntr++;
				testctr++;
				ShiftCtr=0;
				enc_out_state=0;
				break;
			default: break;
			}
			switch(ByteCntr){
			case (BYTESPERPACKET-1):
				myW5500.send_data_processing(0,(uint8_t *) &myIENA.header,sizeof(myIENA.header));
				myW5500.send_data_processing_offset(0,IENAFOOTERSTARTPTR,(uint8_t *) &myIENA.footer,sizeof(myIENA.footer));
				myW5500.writeSnCR(0,Sock_SEND);
				//dst_ptr = PAYLOADSTARTPTR;
				myIENA.header.hdr_sequence= (myIENA.header.hdr_sequence>>8)|((myIENA.header.hdr_sequence&0xff)<<8);
				myIENA.header.hdr_sequence++;
				myIENA.header.hdr_sequence= (myIENA.header.hdr_sequence>>8)|((myIENA.header.hdr_sequence&0xff)<<8);
				ll_hdr_time = ll_hdr_time + 8000;// TIMECOUNTINC;
				TOGGLE3;
				//FIXME: Propper time calculation
				myIENA.header.hdr_time[5]= ll_hdr_time & 0x0000000000FF;
				myIENA.header.hdr_time[4]= (ll_hdr_time>>8) & 0x0000000000FF;
				myIENA.header.hdr_time[3]= (ll_hdr_time>>16) & 0x0000000000FF;
				myIENA.header.hdr_time[2]= (ll_hdr_time>>24) & 0x0000000000FF;
				myIENA.header.hdr_time[1]= (ll_hdr_time>>32) & 0x0000000000FF;
				myIENA.header.hdr_time[0]= (ll_hdr_time>>40) & 0x0000000000FF;
				ByteCntr=0;
				break;
			default:break;
			}
	}
	return(0);
}




