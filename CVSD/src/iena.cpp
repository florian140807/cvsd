/*
 * iena.cpp
 *
 *  Created on: 08.07.2018
 *      Author: Florian

*/

#include "cvsd.h"

iena::iena(){
	header.hdr_key = 0xAAAA;
	header.hdr_time = 0;
	header.hdr_size = 0;
	header.hdr_status = 0;
	header.hdr_n2status =0;
	header.hdr_sequence =0;
	footer = 0xDEAD;
	payload = 0xCAFE;
}

iena::~iena(){
}


