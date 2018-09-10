#include <stdlib.h>
#include "message.h"
#include "uart.h"

#define BUFFER_SIZE 20

static char MESSAGE_BUFFER[BUFFER_SIZE];

void message_init(){
	uart_init();
}

void message_write(char * message){
	for(char * letter = message; *letter != '\0'; letter++){
		uart_write(*letter);
	}
}
