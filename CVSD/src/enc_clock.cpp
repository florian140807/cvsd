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
volatile bool bReady;
volatile bool bSkip=0;
volatile bool bStale=0;
volatile bool bProcessed=0;
volatile bool enc_out_state=0;
volatile uint8_t enc_byte =0;


uint16_t rate = 0;

enc_clock::enc_clock() {
	OCR1A = 0x1F3;				/**< Offsetwert laden: 16e6 / Prescaler / OCRA = 16e3 Hz */
	TCCR1B |= (1<<WGM12);		/**< Clear Timer on Compare */
	TIMSK1 |= (1<<OCIE1A);		/**< enable interrupt */
	TCCR1B |= (1<<CS10);
	rate = 16000;
}

enc_clock::enc_clock(uint16_t _rate){
	switch (_rate){
		case 16000:
			OCR1A = 0x3E7;				/**< Offsetwert laden: 16e6 / Prescaler / OCRA = 16e3 Hz */
			TCCR1B |= (1<<WGM12);		/**< Clear Timer on Compare */
			TIMSK1 |= (1<<OCIE1A);		/**< enable interrupt */
			TCCR1B |= (1<<CS10);
			break;
		case 32000:
			OCR1A = 0x1F3;				/**< Offsetwert laden: 16e6 / Prescaler / OCRA = 32e3 Hz */
			TCCR1B |= (1<<WGM12);		/**< Clear Timer on Compare */
			TIMSK1 |= (1<<OCIE1A);		/**< enable interrupt */
			TCCR1B |= (1<<CS10);
			break;
		case 64000:
			OCR1A = 0x0F9;				/**< Offsetwert laden: 16e6 / Prescaler / OCRA = 64e3 Hz */
			TCCR1B |= (1<<WGM12);		/**< Clear Timer on Compare */
			TIMSK1 |= (1<<OCIE1A);		/**< enable interrupt */
			TCCR1B |= (1<<CS10);
			break;
		default:
			OCR1A = 0x3E7;				/**< Offsetwert laden: 16e6 / Prescaler / OCRA = 16e3 Hz */
			TCCR1B |= (1<<WGM12);		/**< Clear Timer on Compare */
			TIMSK1 |= (1<<OCIE1A);		/**< enable interrupt */
			TCCR1B |= (1<<CS10);
			break;
		}
		rate = _rate;
		return;
}

uint16_t enc_clock::getrate(){
	rate = rate/1;
	return rate;
}

enc_clock::~enc_clock() {
}

//extern serial myUART;

/* Die ISR erzeugt im Takt der genClock() Funktion an den Clockausg�ngen ein Rechtecksignal
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
	SETFX_ENC_DCLK;
	_delay_us(1);
	enc_out_state = (PINB & (1<<FX_ENC_OUT));
	enc_byte = ((enc_byte << 1)|enc_out_state);
	RESETFX_ENC_DCLK;
	bReady = 1;
	}