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
	clock(unsigned int _clk);
	unsigned int getrate();
	~clock();
private:
	unsigned int rate;
};

#endif /* SRC_CLOCK_H_ */
