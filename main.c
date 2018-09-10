#include "defines.h"
#include <util/delay.h>
#include <stdlib.h>
#include "led.h"
#include "message.h"
/* #include "uart.h" */

int main(){
	led_init();
	message_init();

	while(1){
		message_write("Hello world\n\r");

		led_turn_on();
		_delay_ms(1000);

		led_turn_off();
		_delay_ms(1000);
	}

	return 0;
}
