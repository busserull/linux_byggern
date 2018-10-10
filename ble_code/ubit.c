#include "ubit.h"
#include <stdint.h>

#define GPIO ((NRF_GPIO_REGS*)0x50000000)
#define BUTTON_A_PIN 17
#define BUTTON_B_PIN 26

typedef struct {
	volatile uint32_t RESERVED0[321];
	volatile uint32_t OUT;
	volatile uint32_t OUTSET;
	volatile uint32_t OUTCLR;
	volatile uint32_t IN;
	volatile uint32_t DIR;
	volatile uint32_t DIRSET;
	volatile uint32_t DIRCLR;
	volatile uint32_t RESERVED1[120];
	volatile uint32_t PIN_CNF[32];
} NRF_GPIO_REGS;


void ubit_led_matrix_init(){
	for(int i = 4; i <= 15; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}
}

void ubit_led_matrix_turn_on(){
	GPIO->OUTSET = (1 << 13 | 1 << 14 | 1 << 15);
}

void ubit_led_matrix_turn_off(){
	GPIO->OUTCLR = (1 << 13 | 1 << 14 | 1 << 15);
}

void ubit_buttons_init(){
	GPIO->PIN_CNF[BUTTON_A_PIN] = 0;
	GPIO->PIN_CNF[BUTTON_B_PIN] = 0;
}

int ubit_button_press_a(){
	return !(GPIO->IN & (1 << BUTTON_A_PIN));
}

int ubit_button_press_b(){
	return !(GPIO->IN & (1 << BUTTON_B_PIN));
}
