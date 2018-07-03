/*
 * clock.h
 *
 *  Created on: 03.06.2018
 *      Author: Florian
 */

#ifndef _CLOCK_H
#define _CLOCK_H

#include "cvsd.h"


class clock {
public:
	clock();
	clock(uint16_t _clk);
	uint16_t getrate();
	~clock();
private:
	uint16_t rate;

};

#endif /* _CLOCK_H_ */
