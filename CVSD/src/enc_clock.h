/**
 * \class enc_clock
 *
 * \brief This class provides Sampling clock functionality for CVSD sampling
 *
 * This class provides a dedicated clock signal to the CVSD chip FX609.
 * The clock can be set up at different speeds (actual 16,32,64ksps).
 * The clock output pin is driven by the TIMER1_COMPA ISR.
 *
 * \note KEEP IN MIND: W5500 uses Big Endian, where as Atmega32u4 uses
 * Little Endian for word operations. For 16bit values, either define it already
 * in Big Endian Order or doing a Byte Swapping
 *
 * \author  f. mertl
 *
 * \version
 *
 * \date 2018/10/03 14:16:20
 *
 * Contact: s140807@h-ab.de
 *
 * Created on: Wed Jun 03 18:39:37 2018
 *
 *
 */

#ifndef _ENC_CLOCK_H
#define _ENC_CLOCK_H



class enc_clock {
public:
/** \brief Default Constructor
  *
  * This default constructor sets up the COMPA TIMER1 ISR to
  * operated at a rate of 16000Hz
  */
	enc_clock();

/** \brief Constructor
  *
  * This constructor sets up the COMPA TIMER1 ISR to be operated at
  * Default rate would be 16000Hz
  * \param _clk as rate in Hz
  *
  */
	enc_clock(uint16_t _clk);

/** \brief return actual CVSD sampling rate
  * \return rate in Hz
  *
  * This methode returns a actual CVSD sampling rate in Hz at which the
  * TIMER1 COMPA ISR is executed.
  */
	uint16_t getrate();

	/// Destructor
	~enc_clock();
private:
	uint16_t rate;	///< Samplingrate in Hz

};

#endif /* _ENC_CLOCK_H_ */
