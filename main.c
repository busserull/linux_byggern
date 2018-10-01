#include "defines.h"
#include <util/delay.h>
#include <stdlib.h>
#include <string.h>
#include "led.h"
#include "message.h"

void set_led_output(char * buffer){
	if(strcmp(buffer, "turn on") == 0){
		led_turn_on();
	}
	else if(strcmp(buffer, "turn off") == 0){
		led_turn_off();
	}
}

int main(){
	led_init();
	message_init();

	char * buffer = NULL;

	while(1){
		buffer = message_read();

		if(buffer != NULL){
			/* set_led_output(buffer); */

			message_write("GOT: ");
			message_write(buffer);
			message_write("\n\r");

			free(buffer);
			buffer = NULL;
		}

		_delay_ms(100);
	}

	return 0;
}
