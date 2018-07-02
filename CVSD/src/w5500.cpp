#include "cvsd.h"



void W5500Class::init(void)
{
	_delay_ms(1000);
	initSS();
	resetSS();
	SPCR |= _BV(MSTR);
	SPCR |= _BV(SPE);
}

uint8_t W5500Class::write(uint16_t _addr, uint8_t _cb, uint8_t _data)
{
    setSS();
    transfer(_addr >> 8);
    transfer(_addr & 0xFF);
    transfer(_cb);
    transfer(_data);
    resetSS();
    return 1;
}

uint16_t W5500Class::write(uint16_t _addr, uint8_t _cb, const uint8_t *_buf, uint16_t _len)
{
    setSS();
    transfer(_addr >> 8);
    transfer(_addr & 0xFF);
    transfer(_cb);
    for (uint16_t i=0; i<_len; i++){
        transfer(_buf[i]);
    }
    resetSS();
    return _len;
}

