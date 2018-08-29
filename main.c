#ifndef F_CPU
#define F_CPU 1000000
#endif

#include <util/delay.h>
#include "led.h"

int main(){
	led_init();

	while(1){
		led_turn_on();
		_delay_ms(1000);

		led_turn_off();
		_delay_ms(1000);
	}

	return 0;
}
