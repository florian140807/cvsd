/**
 * \file cvsd.h
 *
 * \brief This header file provide Macros, Includes and declarations
 * of some functions used by main.cpp
 *
 *  *
 * \note KEEP IN MIND: W5500 uses Big Endian, where as Atmega32u4 uses
 * Little Endian for word operations. For 16bit values, either define it already
 * in Big Endian Order (see IENAFOOTERVALUE) or doing a Byte Swapping
 * (as in IENAHEADERSIZEVALUE). The w5500.h/cpp files are provided by the W5500 Chip
 * manufacturer and are implemented without any changes from Github
 * https://github.com/Wiznet/WIZ_Ethernet_Library/tree/master/Arduino%20IDE%201.0.x/Ethernet/utility
 *
 * \author  f. mertl
 *
 * \version
 *
 * \date 2018/10/08 14:16:20
 *
 * Contact: s140807@h-ab.de
 *
 * Created on: Wed Jun 03 18:39:37 2018
 *
 *
 */

#ifndef CVSD_H_
#define CVSD_H_


#define F_CPU 16000000UL						/// CPU Speed for _delay() routines
#define FX_ENC_OUT 5							/// FX609 Encoder Output (Pin 6), ATMEGA32u4 PB5 (IO9)
#define IENAHEADERSIZE 14						/// IENA Header contains 14 byte
#define IENAFOOTERSIZE 2						/// IENAFOOTER contains 2 byte
#define IENAFOOTERVALUE 0xADDE					/// keep in mind endianness conflict, 0xADDE results in 0xDEAD
#define IENAKEYVALUE 0x1189						/// keep in mind endianness conflict, 0x1189 results in 0x8911
#define DESTINATIONPORT 50001					/// Define Destination Port for IENA Packets
#define SOURCEPORT 50000						/// Define Source Port for Sn Socket Register
#define FS 64000								/// set CVSD sampling rate in Hz
#if FS < 17000									/// conditional compiling of BYTESPERPACKET depending on CVSD sampling rate
#define BYTESPERPACKET 16						/// for 16ksps CVSD sampling rate 16 bytes should be placed into on IENA packet
#define BUFSIZE 32								/// Shared Memory between main() and ISR
#define BUFMSK 31								/// Buffer mask for Shared Memory as ring buffer to prevent Overflow
#elif  FS > 16000
#define BYTESPERPACKET 256						/// for 32 or 64ksps CVSD sampling rate 256 bytes should be placed into on IENA packet
#define BUFSIZE 1024							/// Shared Memory between main() and ISR
#define BUFMSK 1023								/// Buffer mask for Shared Memory as ring buffer to prevent Overflow
#endif

/*
 * Definition of Current UTC Time
 */

//TODO: Define Macros for doy, hour, min, sec



/*
 * Calculation of IENA Header SizeValue
 */
#define PacketSize ((BYTESPERPACKET)+IENAHEADERSIZE+IENAFOOTERSIZE)/2 	/// Size of the IENA Packet to be placed into the IENA Header (is in words, hence divided by 2)
#define IENAHEADERSIZEVALUE (PacketSize>>8)|((PacketSize & 0xff)<<8) 	/// doing byte swapping
/*
 * Macros for toggling FX609 Encoder Data Clock Pin
 */
#define SETFX_ENC_DCLK (PORTD |= _BV(6))		/// set FX609 Encoder Data Clock (5), ATMEGA32u4 PD6 (IO12)
#define RESETFX_ENC_DCLK (PORTD &= ~(_BV(6)))	/// reset FX609 Encoder Data Clock (5), ATMEGA32u4 PD6 (IO12)
/*
 * Macro for incrementing the timestamp for the next IENA packet
 */
#define TIMECOUNTINC (((8*BYTESPERPACKET))*1000000)/FS		/// calculate IENA headertime Increment



#include "avr/io.h"
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "avr/interrupt.h"
#include <stdint.h>
#include <string.h>
#include <ctype.h>
#include <util/delay.h>
#include "iena.h"
#include "avr/pgmspace.h"
#include "enc_clock.h"
#include "w5500.h"


/** \brief Digital IO Setup
  *
  * This function initialize the IO Pins as output
  * for controlling the W5500 Wiznet Chip and
  * the CVSD Shield
  *
  * Init Pin PB1 (SPI SCK), PB2 (SPI MOSI), PB6 (IO9 W5500 SS/CS) as output
  *
  * Init Pin PD6 (IO12 CVSD Encoder_Data_Clock) as output
  *
  *
  *
  */
void InitIO(void);
/** \brief W5500 Layer 2 to Layer 4 Setup
  *
  * This function initialize the Layer 2 to Layer 4 Parameter.
  *
  * Layer 2 Settings:
  *
  * Source MAC Address mac_addr --> writeSHAR()
  *
  * Destination MAC Address dmac_addr --> writeSnDHAR()
  *
  * Layer 3 Settings:
  *
  * Source (W5500) IP Address ip_addr --> writeSIPR()
  *
  * Destination IP Address dip_addr --> writeSnDIPS()
  *
  * Subnetmask sub_mask --> writeSUBR()
  *
  * Gateway IP Address gtw_addr --> writeGAR()
  *
  * Layer 4 Settings:
  *
  * Source Port port --> writeSnPORT()
  *
  * Destination Port dport --> writeSnDPORT()
  *
  *
  * the writexxx() methods are implemented in w5500.h / w5500.cpp provided
  * by the Chip manufacturer Wiznet
  *
  */
void InitW5500LayerSettings(void);

/** \brief Manual Setup of UTC Time for IENA Header Time
 * \param _doy current day of year
 * \param _hour current hour, keep in mind UTC time scale (means local winter time - 2)
 * \param _min current minute
 * \param _sec actual second - 4-5 seconds (to cover programming process
 * \return ll_hdr_time current time in microseconds since Jan. 1st *
 *
 * This function receives the day and time comma separated and calculates based on this information
 * the current time in microseconds since Jan. 1st
 *
 */
uint64_t SetCurrentUtcTimeInUs(uint16_t _doy, uint8_t _hour, uint8_t _min, uint8_t _sec);








#endif /* CVSD_H_ */
