/*
 * main.cpp
 *
 *  Created on: 30.03.2018
 *      Author: Florian
 *      20180409: move to git
 */

#define F_CPU 16000000UL


#include "cvsd.h"

int main(void){
	DDRC = 0xff;
	W5500Class MyWiznet;
	//MyWiznet.init();
	MyWiznet.readMR();
	while(1){
		PORTC ^= ( 1 << PC7 );  // Toggle PB0 z.&nbsp;B. angeschlossene LED
		_delay_ms(1000);       // Eine Sekunde warten...
	}
	return(0);
}


//void SPI_MasterInit(void)
//{
///* Set MOSI and SCK output, all others input */
//DDRB = (1<<PB2)|(1<<PB1);
///* Enable SPI, Master, set clock rate fck/16 */
//SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
//}
//void SPI_MasterTransmit(char cData)
//{
///* Start transmission */
//SPDR = cData;
///* Wait for transmission complete */
//while(!(SPSR & (1<<SPIF)));
//}
