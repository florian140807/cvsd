/*
 * clock.h
 *
 *  Created on: 03.06.2018
 *      Author: Florian
 */

#ifndef _ENC_CLOCK_H
#define _ENC_CLOCK_H



class enc_clock {
public:
	enc_clock();
	enc_clock(uint16_t _clk);
	uint16_t getrate();
	~enc_clock();
private:
	uint16_t rate;

};

#endif /* _ENC_CLOCK_H_ */
