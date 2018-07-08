
#include "cvsd.h"

serial::serial() {
	UCSR1B |= (1 << RXEN1) | (1 << TXEN1);							//turn on rx and tx
	UCSR1C |= (1 << UCSZ10) | (1 << UCSZ11);		//set data bits to 8

	UBRR1H = (BAUD_PRESCALER >> 8);								//load upper 8 bits of baud value into high byte of UBBR
	UBRR1L = (BAUD_PRESCALER);									//load lower 8 bits of baud value into high byte of UBBR
}

void serial::usart_send_char(char c)
{
	while ((UCSR1A & (1 << UDRE1)) == 0) {};
	UDR1 = c;
}


void serial::usart_send_string(char s[])
{
	int i =0;
	
	while (s[i] != 0x00)
	{
		usart_send_char(s[i]);
		i++;
	}
	usart_send_char('\r');
	usart_send_char('\n');
}

void serial::usart_send_int(uint16_t val){
	char t[10];
	uint16_t tmp = val;
	itoa(tmp,t,10);
	usart_send_string(t);
}






