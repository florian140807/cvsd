/**
 * \file main.cpp
 *
 * \brief The main.cpp file
 *
 *  *
 * \note KEEP IN MIND: W5500 uses Big Endian, where as Atmega32u4 uses
 * Little Endian for word operations. For 16bit values, either define it already
 * in Big Endian Order or doing a Byte Swapping
 *
 *
 * \author  f. mertl
 *
 * \version
 *
 * \date 2018/10/08 14:16:20
 *
 * Contact: s140807@h-ab.de
 *
 * Created on: Wed Jun 03 18:39:37 2018
 *
 *
 */

#include "cvsd.h"

extern volatile bool bReady;
extern volatile uint16_t writeIdx;
extern volatile uint8_t buffer[];
W5500Class W5500Chip;
iena IenaPacket;



int main(void){
	uint16_t readIdx = 0;
	bool match = 0;
	uint64_t ll_hdr_time = SetCurrentUtcTimeInUs(281,15,33,45);
	PRR0 &= ~(1<<PRSPI);
	InitIO();
	InitW5500LayerSettings();
	enc_clock EncoderSamplingClock(FS);
	sei();
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
					IenaPacket.SetPayload(readIdx,buffer[readIdx]);
					readIdx++;
					readIdx &= BUFMSK;
					switch(readIdx){
					case (BYTESPERPACKET):
							W5500Chip.send_data_processing(0,(uint8_t *) &IenaPacket,sizeof(IenaPacket));
							W5500Chip.writeSnCR(0,Sock_SEND_MAC);
							IenaPacket.IncSequence();
							ll_hdr_time = ll_hdr_time + TIMECOUNTINC;
							IenaPacket.SetIENATimeInUs(ll_hdr_time);
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

void InitIO(void){
	DDRB = 0x46;
	DDRD = 0x40;
}

void InitW5500LayerSettings(void){
	uint16_t freesize = 0;
	uint8_t mac_addr[] = {0x90,0xA2,0xDA,0x11,0x34,0x30};
	uint8_t dmac_addr[] = {0x01,0x00,0x5E,0x76,0xFD,0x11};
	uint8_t ip_addr[] = {10,253,28,1};
	uint8_t dip_addr[] = {236,253,0,1};
	uint8_t sub_mask[] = {255,255,0,0};
	uint8_t gtw_addr[] = {192,168,2,1};
	uint16_t port = SOURCEPORT;
	uint16_t dport = DESTINATIONPORT;
	W5500Chip.init();
	W5500Chip.writeMR(MR::RST);
	W5500Chip.writeSnDHAR(0,dmac_addr);
	W5500Chip.writeGAR(gtw_addr);
	W5500Chip.writeSHAR(mac_addr);
	W5500Chip.writeSIPR(ip_addr);
	W5500Chip.writeSUBR(sub_mask);
	W5500Chip.writeSnMR(0,SnMR::MULTI);
	W5500Chip.writeSnDPORT(0,dport);
	W5500Chip.writeSnDIPR(0,dip_addr);
	while(W5500Chip.readSnSR(0)!=SnSR::UDP){
		W5500Chip.writeSnMR(0,SnMR::UDP);
		W5500Chip.writeSnPORT(0,port);
		W5500Chip.writeSnCR(0,Sock_OPEN);
	}
	freesize = W5500Chip.getTXFreeSize(0);
	while(freesize < sizeof(IenaPacket)) freesize = W5500Chip.readSnTX_FSR(0);
}

uint64_t SetCurrentUtcTimeInUs(uint16_t _doy, uint8_t _hour, uint8_t _min, uint8_t _sec){
	uint64_t UtcHdrTime = (_doy*24)+_hour;
	UtcHdrTime = (UtcHdrTime * 60)+_min;
	UtcHdrTime = (UtcHdrTime * 60)+_sec;
	UtcHdrTime = UtcHdrTime * 1e6;
	return UtcHdrTime;
}



