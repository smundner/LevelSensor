#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "usart.h"
#include "onewire.h"
#include "ds18x20.h"

#define analogOut(x) PORTB = x;

uint8_t buffer[9];
volatile unsigned long mycros=0;

ISR(USART_RX_vect){
	unsigned char temp = USART_Receive();
	USART_Transmit_RS485(temp);
	PORTB = temp;
}

ISR(TIMER1_COMPA_vect){
	mycros++;
}

void TIMER_Init(){
	OCR1A=1;
	TCCR1B|=(1<<CS11)|(1<<WGM12);
	//TIMSK|=(1<<OCIE1A);
}

void sendLine(char* string){
	uint8_t i=0;
	while(string[i]!='\0'){
		USART_Transmit_RS485(string[i++]);
	}
	USART_Transmit_RS485('\n');
	USART_Transmit_RS485('\r');
}

//copy from https://www.mikrocontroller.net/articles/Festkommaarithmetik
void my_uitoa(uint32_t zahl, char* string) {
	int8_t i;                             // schleifenzähler

	string[10]='\0';                       // String Terminator
	for(i=9; i>=0; i--) {
		string[i]=(zahl % 10) +'0';         // Modulo rechnen, dann den ASCII-Code von '0' addieren
		zahl /= 10;
	}
}

uint8_t getTemp(){
	int16_t x;
	onewire_skip_rom();
	ds18x20_convert_t(1);
	_delay_ms(750);
	onewire_skip_rom();
	ds18B20_read_temp(&x);
	uint8_t temp = x/10;
	return temp;
}
uint32_t getPulse(){
	PORTD&=~(1<<PD4);
	while(!(PIND&(1<<PD5)));
	mycros=0;
	TIMSK|=(1<<OCIE1A);
	while(PIND&(1<<PD5));
	TIMSK&=~(1<<OCIE1A);
	mycros;
	PORTD|=(1<<PD4);
	return mycros;
}

int main(){
	
	USART_RS458_Init(103);//9600 baud
	TIMER_Init();
	PORTB=0xf0;
	DDRB=0xff;
	PORTD|=(1<<PD4);
	DDRD|=(1<<PD4);
	USART_Transmit_RS485('s');
	sei();
	while(1){
		_delay_ms(500);
		uint16_t c=getTemp()*6/10;
		uint32_t pulse_in_my = getPulse();
		//pulse_in_my/=2;
		uint32_t dist = pulse_in_my * c;
		dist/=20;		
		char string[10];
		my_uitoa(dist,string);
		sendLine(string);
		
		
	}
	return 1;
}
