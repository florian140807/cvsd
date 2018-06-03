/*
 * serial.h
 *
 *  Created on: 03.06.2018
 *      Author: Florian
 */

#ifndef SERIAL_H_
#define SERIAL_H_

class serial {
public:
	serial();
	~serial();
	void serial_send_byte(unsigned char _data);
	void serial_send_int(unsigned int _data);
	void serial_putstring(char* _strg_ptr);
};

#endif /* SERIAL_H_ */
