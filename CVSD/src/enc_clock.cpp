#include "cvsd.h"

bool enc_out_state=0;				/// Init for CVSD Encoder digital output; connected to FX_ENC_OUT
uint8_t ShiftCntr = 0;				/// Init for Shift Counter to merge 8 Samples from enc_out_state into 1 Byte
uint8_t enc_byte =0;				/// Init of the 8 Shift left operations
volatile uint16_t writeIndxCntr = 0;		/// Init Index of the Ring buffer, volatile because of shared with main and enc_clock
volatile uint8_t buffer[BUFSIZE];	/// Init of Ring buffer size by the value of BUFSIZE, volatile because of shared with main and enc_clock
volatile bool bReady;				/// Declaration of ready bit, indicates that 1 byte is complete available, volatile because of shared with main and enc_clock
uint16_t rate = 0;					/// Init of rate



enc_clock::enc_clock() {
	OCR1A = 0x1F3;				/// load Offsetvalue: 16e6 / Prescaler / OCRA = 16e3 Hz
	TCCR1B |= (1<<WGM12);		/// Clear Timer on Compare
	TIMSK1 |= (1<<OCIE1A);		/// enable interrupt
	TCCR1B |= (1<<CS10);
	rate = 16000;
}

enc_clock::enc_clock(uint16_t _rate){
	switch (_rate){
		case 16000:
			OCR1A = 0x3E7;				/// load Offsetvalue: 16e6 / Prescaler / OCRA = 16e3 Hz
			TCCR1B |= (1<<WGM12);		/// Clear Timer on Compare
			TIMSK1 |= (1<<OCIE1A);		/// enable interrupt
			TCCR1B |= (1<<CS10);
			break;
		case 32000:
			OCR1A = 0x1F3;				/// load Offsetvalue:: 16e6 / Prescaler / OCRA = 32e3 Hz
			TCCR1B |= (1<<WGM12);		/// Clear Timer on Compare
			TIMSK1 |= (1<<OCIE1A);		/// enable interrupt
			TCCR1B |= (1<<CS10);
			break;
		case 64000:
			OCR1A = 0x0F9;				/// load Offsetvalue: 16e6 / Prescaler / OCRA = 64e3 Hz
			TCCR1B |= (1<<WGM12);		/// Clear Timer on Compare
			TIMSK1 |= (1<<OCIE1A);		/// enable interrupt
			TCCR1B |= (1<<CS10);
			break;
		default:
			OCR1A = 0x3E7;				/// load Offsetvalue: 16e6 / Prescaler / OCRA = 16e3 Hz
			TCCR1B |= (1<<WGM12);		/// Clear Timer on Compare
			TIMSK1 |= (1<<OCIE1A);		/// enable interrupt
			TCCR1B |= (1<<CS10);
			break;
		}
		rate = _rate;					/// assigns CVSD sampling rate
		return;
}

uint16_t enc_clock::getrate(){
	return rate;						///< returns CVSD sampling rate
}

enc_clock::~enc_clock() {
}

/** \brief Interrupt Service Routine (ISR) TIMER1 COMPA
  *
  * This ISR is going to be executed on TIMER1 compare match.
  * The rate of the ISR is being called is set up by the enc_clock()
  * constructor and can be either 16ksps, 32ksps or 64ksps.
  *
  * At the selected speed the CVSD encoder data clock pin is triggered.
  *
  * The ISR incorporates are ring buffer to share the encoder byte
  * data with the main() loop
  *
  */

ISR(TIMER1_COMPA_vect){
	SETFX_ENC_DCLK;									/// set encoder data clock pin
	_delay_us(1);									/// wait at least 1us before checking encoder output state (750ns min)
	enc_out_state = (PINB & (1<<FX_ENC_OUT));		/// read encoder output state pin
	enc_byte = ((enc_byte << 1)|enc_out_state);		/// shift enc_byte 1 to the left and write Encoder output into LSB position of enc_byte
	ShiftCntr--;									/// decrement shift counter
	RESETFX_ENC_DCLK;								/// reset encoder data clock pin;  (Clock 1 Pulse Width minimum: 1us)
	bReady=0;										/// reset ready bit indicates encoder byte is not ready to be written in the buffer
	switch(ShiftCntr){								/// check shift counter Value
		case 0:										/// all 8 bits placed in the encoder byte
			buffer[writeIndxCntr++] = enc_byte;		/// write encoder byte into buffer, increment write counter
			writeIndxCntr &= BUFMSK;				/// mask write counter value to avoid buffer running out of range
			ShiftCntr=8;							/// reset shift counter
			bReady=1;								/// tell main() that encoder byte is ready to be processed
			break;
		default: break;
	}
	}
