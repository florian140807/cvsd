/*
 * w5500.h
 *
 *  Created on: 03.06.2018
 *      Author: Florian
 */

#ifndef SRC_W5500_H_
#define SRC_W5500_H_

class w5500 {
public:
	w5500();
	~w5500();
	void SetLayer2();
	void SetLayer3();
	void SetLayer4();
	void transmitChar(char _cData);
private:
	unsigned char mac_addr[];
	unsigned char ip_addr[];
	unsigned char sub_mask[];
	unsigned char gtw_addr[];
	unsigned int src_port;
	unsigned int dst_port;
};

#endif /* SRC_W5500_H_ */
