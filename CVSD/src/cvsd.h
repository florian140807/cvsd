/*
 * cvsd.h
 *
 *  Created on: 30.03.2018
 *      Author: Florian
 */

#ifndef CVSD_H_
#define CVSD_H_

#define F_CPU 16000000UL
#define BAUDRATE 9600
#define BAUD_PRESCALER	(((F_CPU / (BAUDRATE * 16UL)))-1)
#define TOGGLE_LED (PORTC ^= _BV(7)) //TOGGLE_MAKRO for Debugging PC7
#define FX_ENC_OUT 5				// FX609 Encoder Ouptut (6), ATMEGA32u4 PB5 (IO9)
//#define FX_ENC_DCLK (PORTD ^= _BV(6))				// FX609 Encoder Data Clock (5), ATMEGA32u4 PD6 (IO12)

#define SETFX_ENC_DCLK (PORTD |= _BV(6))				// set FX609 Encoder Data Clock (5), ATMEGA32u4 PD6 (IO12)
#define RESETFX_ENC_DCLK (PORTD &= ~(_BV(6)))				// reset FX609 Encoder Data Clock (5), ATMEGA32u4 PD6 (IO12)


#define W5500_CDS (PORTB &= ~(_BV(6)))		// W5500 Chip De-Select (Low active)
#define W5500_CS (PORTB |= _BV(6))		// W5500 Chip Select
//#define TOGGLE1 (PORTC ^= _BV(6))			//Pin PC6 for first Interrupt Counter Indication
#define SETSKIP (PORTC |= _BV(6))			//set Pin PC6 for Skip Indication
#define RESETSKIP (PORTC &= ~(_BV(6)))			//reset Pin PC6 for Skip Indication

//#define TOGGLE2 (PORTD ^= _BV(7))			//Pin PD7 for second Interrupt Counter Indication

#define SETSTALE (PORTD |= _BV(7))			//set Pin PD7 for Stale Indication
#define RESETSTALE (PORTD &= ~(_BV(7)))			//reset Pin PD7 for Stale Indication

//#define TOGGLE3 (PORTC ^= _BV(7))			//Pin PC7 for second Interrupt Counter Indication
#define BYTESPERPACKET 32					//define how many cvsd bytes/packet should be packetized
#define IENAHEADERSIZE 14					//IENA Header contains 14 bytes
#define IENAFOOTERSIZE 2					//nums of byte of IENAFOOTER

// Calculation of SnTX Startaddresses
#define IENAHEADERSTARTPTR 0								//Start of IENA Header is 0
#define PAYLOADSTARTPTR IENAHEADERSTARTPTR+IENAHEADERSIZE	//IENA payload data starts at 0x000E
#define IENAFOOTERSTARTPTR PAYLOADSTARTPTR+BYTESPERPACKET	//Start of IENA Footer is

// Assignments of IENA Header and Footer Fields for Size and Footer
#define a (BYTESPERPACKET+IENAHEADERSIZE+IENAFOOTERSIZE)/2 //the value Size in the IENA Header is in words, hence divided by 2
#define IENAHEADERSIZEVALUE (a>>8)|((a&0xff)<<8) //doing byte swapping
#define IENAFOOTERVALUE 0xADDE				//keep in mind Endianess swapping

#define FS 32000
#define TIMECOUNTINC (16*BYTESPERPACKET*(1/FS*1000))


#include "avr/io.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "avr/interrupt.h"
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <util/delay.h>
#include "iena.h"
#include "avr/pgmspace.h"
#include "serial.h"
#include "clock.h"
#include "w5500.h"








#endif /* CVSD_H_ */
