#include "defines.h"
#include <avr/interrupt.h>
#include <stdlib.h>
#include "message.h"
#include "uart.h"

#define MESSAGE_BUFFER_STATUS_NOT_READY 0
#define MESSAGE_BUFFER_STATUS_READY 1

static int MESSAGE_BUFFER_STATUS;
static int MESSAGE_BUFFER_WRITE_INDEX;
static char MESSAGE_BUFFER[MESSAGE_BUFFER_SIZE];

void message_init(){
	MESSAGE_BUFFER_WRITE_INDEX = 0;
	MESSAGE_BUFFER_STATUS = MESSAGE_BUFFER_STATUS_NOT_READY;

	uart_init();
	uart_read_interrupt_enable();

	sei();
}

void message_write(char * message){
	for(char * letter = message; *letter != '\0'; letter++){
		uart_write(*letter);
	}
}

char * message_read(){
	if(MESSAGE_BUFFER_STATUS == MESSAGE_BUFFER_STATUS_READY){
		/* Copy the receive buffer to avoid buffer */
		/* access race condition */
		char * letter = MESSAGE_BUFFER;
		int message_length = 1;
		while(*letter != '\0'){
			message_length++;
			letter++;
		}

		char * copy = (char *)malloc(message_length * sizeof(char));
		for(int i = 0; i <= message_length; i++){
			copy[i] = MESSAGE_BUFFER[i];
		}

		MESSAGE_BUFFER_WRITE_INDEX = 0;
		MESSAGE_BUFFER_STATUS = MESSAGE_BUFFER_STATUS_NOT_READY;

		return copy;
	}
	else{
		return NULL;
	}
}


#include <avr/io.h>

__attribute__((signal)) ISR(USART0_RXC_vect){
	PORTC ^= (1 << PC0);

	if(MESSAGE_BUFFER_STATUS == MESSAGE_BUFFER_STATUS_NOT_READY){
		char letter = uart_read();
		/* uart_write(letter); */
		MESSAGE_BUFFER[MESSAGE_BUFFER_WRITE_INDEX] = letter;

		// -2: Allow space for terminating '\0'
		if(MESSAGE_BUFFER_WRITE_INDEX < MESSAGE_BUFFER_SIZE - 2){
			MESSAGE_BUFFER_WRITE_INDEX++;
		}

		if(letter == '\n' || letter == '\r'){
			MESSAGE_BUFFER[MESSAGE_BUFFER_WRITE_INDEX] = '\0';
			MESSAGE_BUFFER_STATUS = MESSAGE_BUFFER_STATUS_READY;
		}


	}
	/* An else clause to disable subsequent interrupts on the same */
	/* new data is not necessary, since the AVR will always run */
	/* one 'main' instruction in between chained interrupts. */
}
