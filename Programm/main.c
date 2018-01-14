#include <avr/io.h>
#include "usart.h"

#define analogOut(x) PORTB = x;

void TIMER_Init(){

}

int main(){
	//
	USART_Init(103);//9600 baud
	PORTB=0x00;
	DDRB=0xff;

	while(1){

	}
	return 1;
}
