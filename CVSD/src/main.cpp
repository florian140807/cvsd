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
extern volatile uint16_t writeIdx;
extern volatile uint8_t buffer[];

uint16_t swapbytes(uint16_t wdat);

int main(void){
	PRR0 &= ~(1<<PRSPI);
	DDRC = 0xC0;		// Pin PC7 und PC6 als Ausgang (LED) initialisieren
	DDRB = 0x46;		// Pin PB6 als Ausgang initialisieren
	DDRD = 0xC0;		// Pin PD7 und PD6 als Ausgang initialisieren
	DDRE = 0x40;		// Pin PE6 als Ausgang initialisieren
	uint16_t freesize = 0;
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
	while(freesize < sizeof(myIENA)) freesize = myW5500.readSnTX_FSR(0);
	myW5500.writeSnDIPR(0,remote_ip);
	myW5500.writeSnDPORT(0,dstPort);
	sei();
	uint16_t readIdx = 0;
	uint16_t rDay = 269;
	uint8_t rhour = 12;
	uint8_t rmin = 34;
	uint8_t rsec = 30;
	uint64_t ll_hdr_time = (rDay*24)+rhour;
	ll_hdr_time = (ll_hdr_time * 60)+rmin;
	ll_hdr_time = (ll_hdr_time * 60)+rsec;
	ll_hdr_time = ll_hdr_time * 1e6;
	bool match = 0;
	while(1){
		if(readIdx == writeIdx){
			match=1;
		}
			else{
				match=0;

		}
		switch (bReady){
		case 0: break;
		case 1:
			switch(match){
			case (1):break;
			case (0):
					myIENA.SetPayload(readIdx,buffer[readIdx]);
					readIdx++;
					readIdx &= BUFMSK;
					TOGGLE3;
					switch(readIdx){
					case (BYTESPERPACKET):
							myW5500.send_data_processing(0,(uint8_t *) &myIENA,sizeof(myIENA));
							myW5500.writeSnCR(0,Sock_SEND);
							myIENA.IncSequence();
							ll_hdr_time = ll_hdr_time + TIMECOUNTINC;
							myIENA.SetIENATime(ll_hdr_time);
							readIdx=0;
							writeIdx=0;
							break;
							default:break;
							}
					break;
					default:break;
					}
			break;
			default:break;
			}
		}
	return(0);
	}

uint16_t swapbytes(uint16_t wdat){
	wdat= (wdat>>8)|((wdat & 0xff)<<8);
	return wdat;
}



