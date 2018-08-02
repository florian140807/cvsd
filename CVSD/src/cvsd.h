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
#define FX_ENC_DCLK (PORTD ^= _BV(6))				// FX609 Encoder Data Clock (5), ATMEGA32u4 PD6 (IO12)
#define W5500_CDS (PORTB &= ~(1<<PORTB6))		// W5500 Chip De-Select (Low active)
#define W5500_CS (PORTB |= (1<<PORTB6))		// W5500 Chip Select
#define TOGGLE1 (PORTC ^= _BV(6))			//Pin PC6 for first Interrupt Counter Indication
#define TOGGLE2 (PORTD ^= _BV(7))			//Pin PD7 for second Interrupt Counter Indication
#define TOGGLE3 (PORTE ^= _BV(6))			//Pin PE6 for second Interrupt Counter Indication
#define BYTESPERPACKET 8					//define how many cvsd bytes/packet should be packetized
#define IENAHEADERSIZE 14					//IENA Header contains 14 bytes
#define PAYLOADSTARTPTR 0+IENAHEADERSIZE	//there are 14 bytes of IENA header, hence the IENA payload data starts in the SnTX Buffer
#define IENAFOOTERSIZE 2					//nums of byte of IENAFOOTER
#define a (BYTESPERPACKET+IENAHEADERSIZE+IENAFOOTERSIZE)/2 //the value Size in the IENA Header is in words, hence divided by 2
#define IENAHEADERSIZEVALUE (a>>8)|((a&0xff)<<8) //doing byte swapping
#define IENAFOOTERVALUE 0xADDE				//keep in mind Endianess swapping





#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "avr/interrupt.h"
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <util/delay.h>
#include "avr/io.h"
#include "avr/pgmspace.h"
#include "serial.h"
#include "clock.h"
#include "w5500.h"
#include "iena.h"







#endif /* CVSD_H_ */
