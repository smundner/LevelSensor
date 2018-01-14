#include <avr/io.h>
void USART_Init(unsigned int baud){
	UBRRH = (unsigned char)(baud>>8);
	UBRRL = (unsigned char)baud;
	UCSRB = (1<<RXEN)|(1<<TXEN);//|(1<<RXCIE);
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
