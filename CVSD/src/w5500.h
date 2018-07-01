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
#define MR         0x0000      // Mode Register
#define GAR        0x0001      // Gateway Address: 0x0001 to 0x0004
#define SUBR       0x0005      // Subnet mask Address: 0x0005 to 0x0008
#define SHAR        0x0009      // Source Hardware Address (MAC): 0x0009 to 0x000E
#define SIPR       0x000F      // Source IP Address: 0x000F to 0x0012


class w5500 {
public:
	w5500();
	~w5500();
	void transmitChar(uint8_t _cData);
	void transmitWord(uint16_t addr, uint8_t _wData);
	uint8_t receive();
private:
};

#endif /* SRC_W5500_H_ */
