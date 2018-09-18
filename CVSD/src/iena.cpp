/*
 * iena.cpp
 *
 *  Created on: 08.07.2018
 *      Author: Florian

*/

#include "cvsd.h"

iena::iena(){
	header.hdr_key = 0x1189;
	header.hdr_size = IENAHEADERSIZEVALUE;
	header.hdr_time[0] = 0x00;
	header.hdr_time[1] = 0x00;
	header.hdr_time[2] = 0x00;
	header.hdr_time[3] = 0x00;
	header.hdr_time[4] = 0x00;
	header.hdr_time[5] = 0x00;
	header.hdr_status = 0x55;
	header.hdr_n2status =0x66;
	header.hdr_sequence =0;
	footer = 0XADDE;
}

iena::~iena(){
}
