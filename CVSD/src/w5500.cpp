/*
 * w5500.cpp
 *
 *  Created on: 03.06.2018
 *      Author: Florian
 */

#include "cvsd.h"

w5500::w5500() {
	/* Set MOSI and SCK output, all others input */
	DDRB |= (1<<PB2)|(1<<PB1)|(1<<PB6);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
// Set W5500 MAC Address
void w5500::SetSHAR(unsigned char _a, unsigned char _b, unsigned char _c, unsigned char _d, unsigned char _e,
		unsigned char _f){
	mac_addr[5] = _a;
	mac_addr[4] = _b;
	mac_addr[3] = _c;
	mac_addr[2] = _d;
	mac_addr[1] = _e;
	mac_addr[0] = _f;
}
//Set W5500 IP Address
void w5500::SetSIPR(unsigned char _a, unsigned char _b, unsigned char _c, unsigned char _d){
	ip_addr[3] = _a;
	ip_addr[2] = _b;
	ip_addr[1] = _c;
	ip_addr[0] = _d;
}
//Set W5500 Subnetmask
void w5500::SetSUBR(unsigned char _a, unsigned char _b, unsigned char _c, unsigned char _d){
	sub_mask[3] = _a;
	sub_mask[2] = _b;
	sub_mask[1] = _c;
	sub_mask[0] = _d;
}
//Set W5500 Gateway Address
void w5500::SetGAR(unsigned char _a, unsigned char _b, unsigned char _c, unsigned char _d){
	gtw_addr[3] = _a;
	gtw_addr[2] = _b;
	gtw_addr[1] = _c;
	gtw_addr[0] = _d;
}
//Set W5500 Source Port
void w5500::SetPORT(unsigned char _a, unsigned char _b){
	src_port[1] = _a;
	src_port[0] = _b;
}
//Set W5500 Destination Port
void w5500::SetDstPORT(unsigned char _a, unsigned char _b){
	src_port[1] = _a;
	src_port[0] = _b;
}

unsigned char w5500::transmitChar(char _cData)
{
/* Start transmission */
SPDR = _cData;
/* Wait for transmission complete */
//asm volatile("nop");
while(!(SPSR & (1<<SPIF)));
return SPDR;
}
w5500::~w5500() {
	// TODO Auto-generated destructor stub
}

