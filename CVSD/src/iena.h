/**
 * \class iena
 * \brief This class provides methods and attributes to handle IENA Ethernetpackets
 *
 * This class provides IENA objects conform to IENA standard rev 6.0
 * It provides methods to increment the sequence number as well as
 * methods to compute the header time and to set up the IENA payload
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

#ifndef SRC_IENA_H_
#define SRC_IENA_H_



class iena{

public:
/** \brief Default Constructor
  *
  * This default constructor creates an IENA object an initializes the attributes
  * as follows:
  *
  * footer=IENAFOOTERVALUE;
  * hdr_key = IENAKEYVALUE;
  * hdr_size = IENAHEADERSIZEVALUE;
  * hdr_status = 0x00;
  * hdr_n2status =0x00;
  * hdr_sequence =0;
  *
  */
	iena();


	~iena();			/// Default Destructor


	/** \brief IncSequence() increments the sequence counter in the IENA Header
	  *
	  * This method increments the sequence number and assigns the new value to the
	  * hdr_sequence attribute
	  *
	  */
	void IncSequence();


	/** \brief SetIENATimeInUs() writes _time into hdr_time[] array
	 * \param _time uint64_t value in Microseconds since Jan 1st.
	 * \return hdr_time[] array
	  *
	  * This method gets the time in microseconds since Jan. 1st and split/assign
	  * this value into the hdr_time[] array.
	  *
	  */
	void SetIENATimeInUs(uint64_t _time);


	/** \brief SetPayload() assign
	 * \param _index uint8_t ring buffer read index
	 * \param _data uint8_t ring buffer index content
	  *
	  * This method receives the ring buffer read index and the shared ring buffer
	  * content of the read index. The _data is stored in the _index position of
	  * payload
	  *
	  */
	void SetPayload(uint8_t _index, uint8_t _data);


private:
			uint16_t hdr_key;					/// declaration IENA Header Key
			uint16_t hdr_size;					/// declaration IENA Header Size Value
			uint8_t hdr_time[6];				/// declaration IENA Header Time array
			uint8_t hdr_status;					/// declaration IENA Status, not used
			uint8_t hdr_n2status;				/// declaration IENA N2 Status, not used
			uint16_t hdr_sequence;				/// declaration IENA Header Sequence
			uint8_t payload[BYTESPERPACKET];	/// declaration IENA Payload array
			uint16_t footer;					/// declaration IENA Footer/Trailer
};
#endif /* SRC_IENA_H_ */
