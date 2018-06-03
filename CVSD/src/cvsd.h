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

#include <stdio.h>
#include "avr/interrupt.h"
#include <stdint.h>
#include <string.h>
#include <util/delay.h>
#include "avr/io.h"
#include "avr/pgmspace.h"
#include "serial.h"



#endif /* CVSD_H_ */
