#include <avr/io.h>
#include "led.h"

void led_init(){
	DDRC |= (1 << PC0);
	PORTC |= (1 << PC0);
}

void led_turn_on(){
	PORTC &= ~(1 << PC0);
}

void led_turn_off(){
	PORTC |= (1 << PC0);
}
