/*
 * w5500.cpp
 *
 *  Created on: 03.06.2018
 *      Author: Florian
 */

#include "cvsd.h"

w5500::w5500() {
	volatile char IOReg;
	/* Set MOSI and SCK output, all others input */
	//DDRB |= (1<<PB2)|(1<<PB1);
	/* Enable SPI, Master, set clock rate fck/4 */
	SPCR = (1<<SPE)|(1<<MSTR);
	// clear SPIF bit in SPSR
	IOReg   = SPSR;
	IOReg   = SPDR;
}
void w5500::transmitChar(uint8_t _cData)
{
//W5500_CS;
/* Start transmission */
SPDR = _cData;
/* Wait for transmission complete */
//asm volatile("nop");
while(!(SPSR & (1<<SPIF)));
//W5500_CDS;
}

void w5500::transmitWord(uint16_t addr, uint8_t _wData)
{
}


uint8_t w5500::receive(){
	return SPDR;
}

w5500::~w5500() {
	// TODO Auto-generated destructor stub
}
