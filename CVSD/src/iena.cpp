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
	header.hdr_time[0] = 0x2233;
	header.hdr_time[1] = 0x4444;
	header.hdr_time[2] = 0x5555;
	header.hdr_status = 0x55;
	header.hdr_n2status =0x66;
	header.hdr_sequence =0;
	footer = IENAFOOTERVALUE;
	payload = 0xCAFE;
}

iena::~iena(){
}


