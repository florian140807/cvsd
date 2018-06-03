/*
 * main.cpp
 *
 *  Created on: 30.03.2018
 *      Author: Florian
 *      20180409: move to git
 *      20180409: even more moved to online git
 */

#define F_CPU 16000000UL
#define TOGGLE_LED (PORTC ^= _BV(7)) //TOGGLE_MAKRO for Debugging PC7
#define FX_XTAL 4					// FX609 XTALI (1), ATMEGA32u4 PB4 (IO8)
#define FX_ENC_OUT 7				// FX609 Encoder Ouptut (6), ATMEGA32u4 PB7 (IO11)
#define FX_ENC_DCLK 6				// FX609 Encoder Data Clock (5), ATMEGA32u4 PD6 (IO12)


#include "cvsd.h"

void genClock(int _Rate);
void SPI_MasterInit(void);
//void Init_Socket(void);

int main(void){
	DDRC = 0xff;		// Port C als Ausgang initialisieren

	SPI_MasterInit();
	while(1){
//		TOGGLE_LED;  // Toggle PC7 z.B. angeschlossene LED
//		_delay_ms(1000);       // Eine Sekunde warten...
		genClock(16000);
	}
	return(0);
}


void SPI_MasterInit(void)
{
/* Set MOSI and SCK output, all others input */
DDRB = (1<<PB2)|(1<<PB1);
/* Enable SPI, Master, set clock rate fck/16 */
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void Init_W5500(void)
{
	// Ethernet Setup
	unsigned char mac_addr[] = {0x00,0x16,0x36,0xDE,0x58,0xF6};
	unsigned char ip_addr[] = {192,168,1,144};
	unsigned char sub_mask[] = {255,255,255,0};
	unsigned char gtw_addr[] = {192,168,1,1};

}
//void SPI_MasterTransmit(char cData)
//{
///* Start transmission */
//SPDR = cData;
///* Wait for transmission complete */
//while(!(SPSR & (1<<SPIF)));
//}


void genClock(int _Rate){
	switch (_Rate){
	case 16000:
		OCR1A = 0x3E8;				/**< Offsetwert laden: 16e6 / Prescaler / OCRA = 16e3 Hz */
		TCCR1B |= (1<<WGM12);		/**< Clear Timer on Compare */
		TIMSK1 |= (1<<OCIE1A);		/**< enable interrupt */
		TCCR1B |= (1<<CS10);
		TOGGLE_LED;
		_delay_ms(1000);       // Eine Sekunde warten...
		break;
	case 32000:
		TOGGLE_LED;
		_delay_ms(2000);       // Zwei Sekunden warten...
		break;
	case 64000:
		TOGGLE_LED;
		_delay_ms(200);       // Eine halbe Sekunde warten...
		break;
	default:
		break;
	}
	return;
}
