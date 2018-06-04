/*
 * w5500.cpp
 *
 *  Created on: 03.06.2018
 *      Author: Florian
 */

#include "cvsd.h"

w5500::w5500() {
	/* Set MOSI and SCK output, all others input */
	DDRB |= (1<<PB2)|(1<<PB1);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

void w5500::SetLayer2(){
	mac_addr[0] = 0x00;
	mac_addr[1] = 0x16;
	mac_addr[2] = 0x36;
	mac_addr[3] = 0xDE;
	mac_addr[4] = 0x58;
	mac_addr[5] = 0xF6;
}

void w5500::SetLayer3(){
	ip_addr[0] = 192;
	ip_addr[1] = 168;
	ip_addr[2] = 1;
	ip_addr[3] = 144;

	sub_mask[0] = 255;
	sub_mask[1] = 255;
	sub_mask[2] = 255;
	sub_mask[3] = 0;

	gtw_addr[0] = 192;
	gtw_addr[1] = 168;
	gtw_addr[2] = 1;
	gtw_addr[3] = 1;

}

void w5500::SetLayer4(){
	src_port = 50000;
	dst_port = 50001;
}

void w5500::transmitChar(char cData)
{
/* Start transmission */
SPDR = cData;
/* Wait for transmission complete */
while(!(SPSR & (1<<SPIF)));
}

w5500::~w5500() {
	// TODO Auto-generated destructor stub
}

