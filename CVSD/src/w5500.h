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
	void SetSHAR(uint8_t _a, uint8_t _b, uint8_t _c, uint8_t _d, uint8_t _e, uint8_t _f);
	void SetSIPR(uint8_t _a, uint8_t _b, uint8_t _c, uint8_t _d);
	void SetSUBR(uint8_t _a, uint8_t _b, uint8_t _c, uint8_t _d);
	void SetGAR(uint8_t _a, uint8_t _b, uint8_t _c, uint8_t _d);
	void SetPORT(uint8_t _a, uint8_t _b);
	void SetDstPORT(uint8_t _a, uint8_t _b);
	uint8_t GetSHAR(uint8_t _a);
	uint8_t GetSIPR(uint8_t _a);
	uint8_t GetSUBR(uint8_t _a);
	uint8_t GetGAR(uint8_t _a);
	uint8_t GetPORT(uint8_t _a);
	uint8_t GetDstPORT(uint8_t _a);
	void transmitChar(uint8_t _cData);
	uint8_t receive();
private:
	uint8_t SHAR[6];
	uint8_t SIPR[4];
	uint8_t SUBR[4];
	uint8_t GAR[4];
	uint8_t PORT[2];
	uint8_t DstPORT[2];
};

#endif /* SRC_W5500_H_ */
