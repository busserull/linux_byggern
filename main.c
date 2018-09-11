#include "defines.h"
#include <util/delay.h>
#include <stdlib.h>
#include "led.h"
#include "message.h"

int main(){
	led_init();
	message_init();

	char * buffer = (char *)malloc(20 * sizeof(char));

	while(1){
		for(int i = 0; i < 20; i++){
			buffer[i] = '\0';
		}

		if(message_read(buffer, 20)){
			message_write(buffer);
		}
	}

	return 0;
}
