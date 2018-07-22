#include "cvsd.h"


void W5500Class::init(void)
{

    initSS();
    _delay_ms(300);
    //delay(300);
    //SPI.begin();
    SPCR |= _BV(MSTR);
    SPCR |= _BV(SPE);
    SPSR |= _BV(SPI2X);

    for (int i=0; i<MAX_SOCK_NUM; i++) {
        uint8_t cntl_byte = (0x0C + (i<<5));
        writeSn( 0x1E, cntl_byte, 2); //0x1E - Sn_RXBUF_SIZE
        write( 0x1F, cntl_byte, 2); //0x1F - Sn_TXBUF_SIZE
    }
}

uint16_t W5500Class::getTXFreeSize(SOCKET s)
{
    uint16_t val=0, val1=0;
    do {
        val1 = readSnTX_FSR(s);
        if (val1 != 0)
            val = readSnTX_FSR(s);
    }
    while (val != val1);
    return val;
}

void W5500Class::send_data_processing(SOCKET s, const uint8_t *data, uint16_t len)
{
  // This is same as having no offset in a call to send_data_processing_offset
  send_data_processing_offset(s, 0, data, len);

}

void W5500Class::send_data_processing_offset(SOCKET s, uint16_t data_offset, const uint8_t *data, uint16_t len)
{

    uint16_t ptr = readSnTX_WR(s);
    uint8_t cntl_byte = (0x14+(s<<5));
    ptr += data_offset;
    write(ptr, cntl_byte, data, len);
    ptr += len;
    writeSnTX_WR(s, ptr);

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

uint8_t W5500Class::read(uint16_t _addr, uint8_t _cb)
{
    setSS();
    transfer(_addr >> 8);
    transfer(_addr & 0xFF);
    transfer(_cb);
    uint8_t _data = transfer(0);
    resetSS();
    return _data;
}

uint16_t W5500Class::read(uint16_t _addr, uint8_t _cb, uint8_t *_buf, uint16_t _len)
{
    setSS();
    transfer(_addr >> 8);
    transfer(_addr & 0xFF);
    transfer(_cb);
    for (uint16_t i=0; i<_len; i++){
        _buf[i] = transfer(0);
    }
    resetSS();

    return _len;
}

void W5500Class::execCmdSn(SOCKET s, SockCMD _cmd) {
    // Send command to socket
    writeSnCR(s, _cmd);
    // Wait for command to complete
    while (readSnCR(s))
    ;
}

