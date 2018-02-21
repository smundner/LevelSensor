#include <avr/io.h>
#include "usart.h"
#include <util/delay.h>
#include "main.h"

void USART_Init(unsigned int baud){
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;
	UCSRB = (1<<RXEN)|(1<<TXEN)|(1<<RXCIE);
	UCSRC = (1<<UCSZ0)|(1<<UCSZ1);
}

void USART_Transmit(unsigned char data ){
    while( !( UCSRA & (1<<UDRE)) );
    UDR = data;
}

unsigned char USART_Receive(void){

    while( !(UCSRA & (1<<RXC)) );
    return UDR;
}

void USART_RS458_Init(unsigned int baud){
	DDRD|=(1<<PD2);
	USART_Init(baud);
}


void USART_Transmit_RS485(unsigned char data){
	UCSRA=(1<<TXC);
	PORTD|=(1<<PD2);
	USART_Transmit(data);
	while(!(UCSRA&(1<<TXC)));
	PORTD&=~(1<<PD2);
	
}