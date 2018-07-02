/*----------------------------------------------------------------------------
 Copyright:      Radig Ulrich  mailto: mail@ulrichradig.de
 Author:         Radig Ulrich
 Remarks:        
 known Problems: none
 Version:        14.06.2007
 Description:    RS232 Routinen

 Dieses Programm ist freie Software. Sie können es unter den Bedingungen der 
 GNU General Public License, wie von der Free Software Foundation veröffentlicht, 
 weitergeben und/oder modifizieren, entweder gemäß Version 2 der Lizenz oder 
 (nach Ihrer Option) jeder späteren Version. 

 Die Veröffentlichung dieses Programms erfolgt in der Hoffnung, 
 daß es Ihnen von Nutzen sein wird, aber OHNE IRGENDEINE GARANTIE, 
 sogar ohne die implizite Garantie der MARKTREIFE oder der VERWENDBARKEIT 
 FÜR EINEN BESTIMMTEN ZWECK. Details finden Sie in der GNU General Public License. 

 Sie sollten eine Kopie der GNU General Public License zusammen mit diesem 
 Programm erhalten haben. 
 Falls nicht, schreiben Sie an die Free Software Foundation, 
 Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA. 
------------------------------------------------------------------------------*/

#ifndef _UART_H
#define _UART_H

#include "cvsd.h"

#define USART_ECHO	1
#define BUFFER_SIZE	100

volatile unsigned char buffercounter;
char usart_rx_buffer[BUFFER_SIZE];

struct {
		volatile unsigned char usart_ready:1;
		volatile unsigned char usart_rx_ovl:1;
		}usart_status ;
		
//----------------------------------------------------------------------------
	
//	#include <avr/interrupt.h>
//	#include <avr/pgmspace.h>
//	#include <stdlib.h>
//	#include <stdarg.h>
//	#include <ctype.h>
//	#include <string.h>
//	#include <avr/io.h>

	#define USR UCSR1A
	#define UCR UCSR1B
	#define UBRR UBRR1L
	#define TXEN TXEN1
	#define UDR UDR1
	#define UDRE UDRE1
	
void usart_init(unsigned int baudrate); 
void usart_write_char(char c);
void usart_write_str(char *str);
	
void usart_write_P (const char *Buffer,...);
#define usart_write(format, args...)   usart_write_P(PSTR(format) , ## args)
	
//----------------------------------------------------------------------------

#endif //_UART_H

