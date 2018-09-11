#include "defines.h"
#include <util/delay.h>
#include <stdlib.h>
#include "led.h"
#include "message.h"

int main(){
	led_init();
	message_init();

	char * buffer = NULL;

	while(1){
		buffer = message_read();

		if(buffer != NULL){
			message_write(buffer);
			message_write("\n\r");

			free(buffer);
			buffer = NULL;
		}

		_delay_ms(100);
	}

	return 0;
}
