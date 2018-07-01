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
// Set W5500 MAC Address
void w5500::SetSHAR(uint8_t _a, uint8_t _b, uint8_t _c, uint8_t _d, uint8_t _e, uint8_t _f){
	SHAR[5] = _a;
	SHAR[4] = _b;
	SHAR[3] = _c;
	SHAR[2] = _d;
	SHAR[1] = _e;
	SHAR[0] = _f;
}
//Set W5500 IP Address
void w5500::SetSIPR(uint8_t _a, uint8_t _b, uint8_t _c, uint8_t _d){
	SIPR[3] = _a;
	SIPR[2] = _b;
	SIPR[1] = _c;
	SIPR[0] = _d;
}
//Set W5500 Subnetmask
void w5500::SetSUBR(uint8_t _a, uint8_t _b, uint8_t _c, uint8_t _d){
	SUBR[3] = _a;
	SUBR[2] = _b;
	SUBR[1] = _c;
	SUBR[0] = _d;
}
//Set W5500 Gateway Address
void w5500::SetGAR(uint8_t _a, uint8_t _b, uint8_t _c, uint8_t _d){
	GAR[3] = _a;
	GAR[2] = _b;
	GAR[1] = _c;
	GAR[0] = _d;
}
//Set W5500 Source Port
void w5500::SetPORT(uint8_t _a, uint8_t _b){
	PORT[1] = _a;
	PORT[0] = _b;
}
//Set W5500 Destination Port
void w5500::SetDstPORT(uint8_t _a, uint8_t _b){
	DstPORT[1] = _a;
	DstPORT[0] = _b;
}
//Liefert Argumentenwert SHAR zurück
uint8_t w5500::GetSHAR(uint8_t _a){
	return SHAR[_a];
}
//Liefert Argumentenwert SIPR zurück
uint8_t w5500::GetSIPR(uint8_t _a){
	return SIPR[_a];
}
//Liefert Argumentenwert SUBR zurück
uint8_t w5500::GetSUBR(uint8_t _a){
	return SUBR[_a];
}
//Liefert Argumentenwert GAR zurück
uint8_t w5500::GetGAR(uint8_t _a){
	return GAR[_a];
}
//Liefert Argumentenwert PORT zurück
uint8_t w5500::GetPORT(uint8_t _a){
	return PORT[_a];
}
//Liefert Argumentenwert DstPORT zurück
uint8_t w5500::GetDstPORT(uint8_t _a){
	return DstPORT[_a];
}


void w5500::transmitChar(uint8_t _cData)
{
/* Start transmission */
SPDR = _cData;
/* Wait for transmission complete */
asm volatile("nop");
while(!(SPSR & (1<<SPIF)));
}

uint8_t w5500::receive(){
	return SPDR;
}

w5500::~w5500() {
	// TODO Auto-generated destructor stub
}

