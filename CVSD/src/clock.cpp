/*
 * clock.cpp
 *
 *  Created on: 03.06.2018
 *      Author: Florian
 */

#include "cvsd.h"


uint16_t ReadClkCntr = 0;
uint16_t MrgCntr = 0;
uint16_t TxClkCntr = 0;
uint16_t cntr = 0;
//volatile enum {bit_ready, byte_ready, packet_ready} ready_state;
//volatile bool bit_ready;
//volatile bool byte_ready;
//volatile bool packet_ready;
volatile bool bReady;
volatile bool bSkip=0;
volatile bool bStale=0;
volatile bool bProcessed=0;


uint16_t rate = 0;

clock::clock() {
	OCR1A = 0x1F3;				/**< Offsetwert laden: 16e6 / Prescaler / OCRA = 16e3 Hz */
	TCCR1B |= (1<<WGM12);		/**< Clear Timer on Compare */
	TIMSK1 |= (1<<OCIE1A);		/**< enable interrupt */
	TCCR1B |= (1<<CS10);
	rate = 16000;
}

clock::clock(uint16_t _rate){
	switch (_rate){
		case 16000:
			OCR1A = 0x1F3;				/**< Offsetwert laden: 16e6 / Prescaler / OCRA = 16e3 Hz */
			TCCR1B |= (1<<WGM12);		/**< Clear Timer on Compare */
			TIMSK1 |= (1<<OCIE1A);		/**< enable interrupt */
			TCCR1B |= (1<<CS10);
			break;
		case 32000:
			OCR1A = 0x0F9;				/**< Offsetwert laden: 16e6 / Prescaler / OCRA = 32e3 Hz */
			TCCR1B |= (1<<WGM12);		/**< Clear Timer on Compare */
			TIMSK1 |= (1<<OCIE1A);		/**< enable interrupt */
			TCCR1B |= (1<<CS10);
			break;
		case 64000:
			OCR1A = 0x07C;				/**< Offsetwert laden: 16e6 / Prescaler / OCRA = 64e3 Hz */
			TCCR1B |= (1<<WGM12);		/**< Clear Timer on Compare */
			TIMSK1 |= (1<<OCIE1A);		/**< enable interrupt */
			TCCR1B |= (1<<CS10);
			break;
		default:
			OCR1A = 0x1F3;				/**< Offsetwert laden: 16e6 / Prescaler / OCRA = 16e3 Hz */
			TCCR1B |= (1<<WGM12);		/**< Clear Timer on Compare */
			TIMSK1 |= (1<<OCIE1A);		/**< enable interrupt */
			TCCR1B |= (1<<CS10);
			break;
		}
		rate = _rate;
		return;
}

uint16_t clock::getrate(){
	rate = rate/1;
	return rate;
}

clock::~clock() {
}

//extern serial myUART;

/* Die ISR erzeugt im Takt der genClock() Funktion an den Clockausgängen ein Rechtecksignal
 * Das Makro FX_ENC_DCLK toggled den Ausgang PD6 und den Ausgang PB4
 */

ISR(TIMER1_COMPA_vect){
	RESETSTALE;
	switch(bProcessed){
	case 0:
		bSkip = 1;
		SETSKIP;
		break;
	case 1:
		bSkip=0;
		RESETSKIP;
		break;
	}
	bReady = 1;
	//FX_ENC_DCLK;
	SETFX_ENC_DCLK;
	_delay_us(1);
	RESETFX_ENC_DCLK;
	}
