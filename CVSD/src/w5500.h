/*
 * w5500.h
 *
 *  Created on: 03.06.2018
 *      Author: Florian
 */

#ifndef SRC_W5500_H_
#define SRC_W5500_H_

#define CP_BSB_CR 0x00000
#define CP_BSP_S0 0x00001
#define CP_BSP_S0_Tx 0x00010
#define CP_BSP_S0_Rx 0x00011


class w5500 {
public:
	w5500();
	~w5500();
	void SetSHAR(unsigned char _a, unsigned char _b, unsigned char _c, unsigned char _d, unsigned char _e,
			unsigned char _f);
	void SetSIPR(unsigned char _a, unsigned char _b, unsigned char _c, unsigned char _d);
	void SetSUBR(unsigned char _a, unsigned char _b, unsigned char _c, unsigned char _d);
	void SetGAR(unsigned char _a, unsigned char _b, unsigned char _c, unsigned char _d);
	void SetPORT(unsigned char _a, unsigned char _b);
	void SetDstPORT(unsigned char _a, unsigned char _b);
	unsigned char transmitChar(char _cData);
	unsigned char receive();
private:
	unsigned char mac_addr[];
	unsigned char ip_addr[];
	unsigned char sub_mask[];
	unsigned char gtw_addr[];
	unsigned char src_port[];
	unsigned char dst_port[];
};

#endif /* SRC_W5500_H_ */
