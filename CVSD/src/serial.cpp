/*
 * serial.cpp
 *
 *  Created on: 03.06.2018
 *      Author: Florian
 */
#include "cvsd.h"

serial::serial() {
	UBRR1H = (uint8_t)(BAUD_PRESCALER >> 8);
	UBRR1L = (uint8_t)BAUD_PRESCALER;
	UCSR1B = (1<<RXEN1)|(1<<TXEN1);
	UCSR1C = (1<<UCSZ11)|(1<<UCSZ10);
}

serial::~serial() {
}

void serial::serial_send_byte(unsigned char _data){
	while(!(UCSR1A &(1<<UDRE1)));
	UDR1=_data;
}
void serial::serial_putstring(char* _strg_ptr){
	while(*_strg_ptr != 0x00){
		serial_send_byte(*_strg_ptr);
		_strg_ptr++;
	}
	serial_send_byte(13);
	serial_send_byte(10);
}

