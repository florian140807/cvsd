/*
 * iena.cpp
 *
 *  Created on: 08.07.2018
 *      Author: Florian

*/

#include "cvsd.h"

iena::iena(){
	header.hdr_key = 0x1111;
	header.hdr_size = 0x2222;
	header.hdr_time = 0x3333;
	header.hdr_status = 0x44;
	header.hdr_n2status =0x55;
	header.hdr_sequence =0x6666;
	footer = 0xADDE;
	payload = 0xCAFE;
}

iena::~iena(){
}


