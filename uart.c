#include <avr/io.h>
#include <stdint.h>
#include "defines.h"
#include "uart.h"
#define BAUD_9600 (F_CPU/16/DESIRED_BAUD_RATE - 1)

void uart_init(){
	UBRR0H = (uint8_t)(BAUD_9600 >> 8);
	UBRR0L = (uint8_t)(BAUD_9600);

	UCSR0A &= ~(1 << U2X0);

	UCSR0B = (1 << RXEN0)
		| (1 << TXEN0);

	UCSR0C = (1 << URSEL0)
		| (1 << UCSZ00)
		| (1 << UCSZ01)
		| (1 << USBS0);
}

void uart_read_interrupt_enable(){
	UCSR0B |= (1 << RXCIE0);
}

void uart_read_interrupt_disable(){
	UCSR0B &= ~(1 << RXCIE0);
}

void uart_write(char letter){
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = letter;
}

char uart_read(){
	if(!(UCSR0A & (1 << RXC0)))
		return '\0';
	return UDR0;
}
