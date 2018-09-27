/*
 * iena.cpp
 *
 *  Created on: 08.07.2018
 *      Author: Florian

*/

#include "cvsd.h"


iena::iena(){
	footer=0xADDE;
	hdr_key = 0x1189;
	hdr_size = IENAHEADERSIZEVALUE;
	hdr_status = 0x55;
	hdr_n2status =0x66;
	hdr_sequence =0;
	}

iena::~iena(){
}

void iena::IncSequence(){
	hdr_sequence= (hdr_sequence>>8)|((hdr_sequence&0xff)<<8);
	hdr_sequence++;
	hdr_sequence= (hdr_sequence>>8)|((hdr_sequence&0xff)<<8);
}

void iena::SetIENATime(uint64_t _time){
	hdr_time[5]= _time & 0x0000000000FF;
	hdr_time[4]= (_time>>8) & 0x0000000000FF;
	hdr_time[3]= (_time>>16) & 0x0000000000FF;
	hdr_time[2]= (_time>>24) & 0x0000000000FF;
	hdr_time[1]= (_time>>32) & 0x0000000000FF;
	hdr_time[0]= (_time>>40) & 0x0000000000FF;
}

void iena::SetPayload(uint8_t _index, uint8_t _data){
	payload[_index] = _data;
}
