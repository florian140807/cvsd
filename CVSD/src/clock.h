/*
 * clock.h
 *
 *  Created on: 03.06.2018
 *      Author: Florian
 */

#ifndef SRC_CLOCK_H_
#define SRC_CLOCK_H_

class clock {
public:
	clock();
	clock(uint16_t _clk);
	uint16_t getrate();
	~clock();
private:
	uint16_t rate;
};

#endif /* SRC_CLOCK_H_ */
