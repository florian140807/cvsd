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
 * This application is intended to run on an Arduino Leonardo Ethernet. It receives
 * encoded audio information from an own developed CVSD Shield.
 *
 * The Arduino board provides the variable Sampling rate clock (Macro FS) for the CVSD encoder chip.
 *
 * The sampling rate clock FS can be set to 16/32/64ksps
 *
 * The Arduino's Atmega32u4 packetizes the encoded data bits into a byte array, whose size is defined
 * by the Macro BYTESPERPACKET.
 *
 * The packed bytes are encapseled into a IENA conform Layer. The data are sent over Ethernet via the
 * W5500 Wiznet Serial-Ethernet converter chip. The packets are transmitted as multicast.
 *
 * Further functions: Setup the W5500 Layer 2 to 4 parameter, Modify/Elaborate IEAN Header parameter
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
extern volatile uint16_t writeIndxCntr;
extern volatile uint8_t buffer[];
W5500Class W5500Chip;
iena IenaPacket;



int main(void){														/// main()
	bool bmatch = 0;												/// init bmatch bit to compare index counter (readIndxCntr/writeIndxCntr)
	uint16_t readIndxCntr = 0;										/// init readIndxCntr index counter
	uint64_t ll_hdr_time = SetCurrentUtcTimeInUs(281,15,33,45);	 	/// init and set current time for IENA header time field
	PRR0 &= ~(1<<PRSPI);											/// disable power reduction serial peripheral interface SPI
	InitIO();
	InitW5500LayerSettings();
	enc_clock EncoderSamplingClock(FS);								/// create enc_clock instance, Samplingrate = FS
	sei();															/// enable interrupts
	while(1){														///while() loop
		if(readIndxCntr == writeIndxCntr){							/// if both index counter are equal,
			bmatch=1;												///	set bmatch bit
		}															///
			else{													///
				bmatch=0;											/// reset bmatch bit
		}
		switch (bReady){											/// check if ISR allows reading of the next buffered enc_byte
		case 0: break;												/// not allowed, ISR not ready, so return to while()
		case 1:
			switch(bmatch){											///	check bmatch bit (both index counter equal
			case (1):break;											/// yes, counter equal, so return to while()
			case (0):												/// no, so proceed with send procedure
					IenaPacket.SetPayload(readIndxCntr,buffer[readIndxCntr]);	/// copy buffered enc_byte into IENA Payload array
					readIndxCntr++;									/// one buffer byte was read, so increment the counter
					readIndxCntr &= BUFMSK;							/// mask read counter index value to avoid buffer running out of range
					switch(readIndxCntr){							/// check read counter index value
					case (BYTESPERPACKET):							/// are the same number of buffered enc_bytes aquired then defined by BYTESPERPACKET ?
							W5500Chip.send_data_processing(0,(uint8_t *) &IenaPacket,sizeof(IenaPacket));	/// transfer the IENA packet to the W5500 write memory
							W5500Chip.writeSnCR(0,Sock_SEND_MAC);		/// send the IEAN packet
							IenaPacket.IncSequence();					/// after one IENA packet was sent, increment the sequence counter value for the next IENA packet
							ll_hdr_time = ll_hdr_time + TIMECOUNTINC;	/// after one IENA packet was sent, compute new IENA header time value for the next IENA packet
							IenaPacket.SetIENATimeInUs(ll_hdr_time);	/// set the new IENA header time by calling SetIENATimeInUs()
							readIndxCntr=0;								/// reset read index counter for next packet
							writeIndxCntr=0;							/// reset read index counter for next packet
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



