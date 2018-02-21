#ifndef __USART_H__
#define __USART_H__
void USART_Init(unsigned int baud);
void USART_Transmit(unsigned char data );
unsigned char USART_Receive(void);
void USART_RS458_Init(unsigned int baud);
void USART_Transmit_RS485(unsigned char data);
#endif
