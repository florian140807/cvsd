/*
 * main.cpp
 *
 *  Created on: 30.03.2018
 *      Author: Florian
 *      20180409: move to git
 *      20180409: even more moved to online git
 */

#include "cvsd.h"

void genClock(int _Rate);
void SPI_MasterInit(void);
//void Init_Socket(void);

int main(void){
	DDRC = 0xff;		// Port C als Ausgang initialisieren
	DDRB = 0x10;		// Pin PB4 als Ausgang initialisieren
	DDRD = 0x40;		// Pin PD6 als Ausgang initialisieren
	clock myClock(16000);
	SPI_MasterInit();
	serial myUART;
	sei();
	//unsigned char a = 10;
	while(1){
		myUART.serial_send_int(myClock.getrate());
	}
	return(0);
}


void SPI_MasterInit(void)
{
/* Set MOSI and SCK output, all others input */
DDRB |= (1<<PB2)|(1<<PB1);
/* Enable SPI, Master, set clock rate fck/16 */
SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void Init_W5500(void)
{
	// Ethernet Setup
	unsigned char mac_addr[] = {0x00,0x16,0x36,0xDE,0x58,0xF6};
	unsigned char ip_addr[] = {192,168,1,144};
	unsigned char sub_mask[] = {255,255,255,0};
	unsigned char gtw_addr[] = {192,168,1,1};

}
//void SPI_MasterTransmit(char cData)
//{
///* Start transmission */
//SPDR = cData;
///* Wait for transmission complete */
//while(!(SPSR & (1<<SPIF)));
//}



/* void genClock(int _Rate) erzeugt mit TC1 ein Taktsignal in der Frequenz des Uebergabeparameters _Rate
 * _Rate 16000 = 16kHz
 * _Rate 32000 = 32kHz
 * _Rate 64000 = 64kHz
 * Auswertung der gewaehlten Frequenz über switch case Abfrage
 * default: 16kHz
 * Bei der Initialisierung des Timers wird der Compare Interrupt initialisiert und bei Erreichen die ISR
 * ausgefuehrt
 */
//void genClock(int _Rate){
//	switch (_Rate){
//	case 16000:
//		OCR1A = 0x1F3;				/**< Offsetwert laden: 16e6 / Prescaler / OCRA = 16e3 Hz */
//		TCCR1B |= (1<<WGM12);		/**< Clear Timer on Compare */
//		TIMSK1 |= (1<<OCIE1A);		/**< enable interrupt */
//		TCCR1B |= (1<<CS10);
//		break;
//	case 32000:
//		OCR1A = 0x0F9;				/**< Offsetwert laden: 16e6 / Prescaler / OCRA = 32e3 Hz */
//		TCCR1B |= (1<<WGM12);		/**< Clear Timer on Compare */
//		TIMSK1 |= (1<<OCIE1A);		/**< enable interrupt */
//		TCCR1B |= (1<<CS10);
//		break;
//	case 64000:
//		OCR1A = 0x07C;				/**< Offsetwert laden: 16e6 / Prescaler / OCRA = 64e3 Hz */
//		TCCR1B |= (1<<WGM12);		/**< Clear Timer on Compare */
//		TIMSK1 |= (1<<OCIE1A);		/**< enable interrupt */
//		TCCR1B |= (1<<CS10);
//		break;
//	default:
//		OCR1A = 0x1F3;				/**< Offsetwert laden: 16e6 / Prescaler / OCRA = 16e3 Hz */
//		TCCR1B |= (1<<WGM12);		/**< Clear Timer on Compare */
//		TIMSK1 |= (1<<OCIE1A);		/**< enable interrupt */
//		TCCR1B |= (1<<CS10);
//		break;
//	}
//	return;
//}
