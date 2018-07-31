/*
 * iena.h
 *
 *  Created on: 08.07.2018
 *      Author: Florian
 */

#ifndef SRC_IENA_H_
#define SRC_IENA_H_


class iena{
public:
	iena();
	~iena();
//private:
	//struct strct_iena{
		struct iena_header{
			uint16_t hdr_key;
			uint16_t hdr_size;
			uint16_t hdr_time[3];
			uint8_t hdr_status;
			uint8_t hdr_n2status;
			uint16_t hdr_sequence;
		}header;
		uint16_t footer;
		uint16_t payload;
//}iena_packet;
};


#endif /* SRC_IENA_H_ */
