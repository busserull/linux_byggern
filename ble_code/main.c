#include "ubit.h"

int main(){
	ubit_led_matrix_init();
	ubit_buttons_init();

	while(1){
		if(ubit_button_press_a()){
			ubit_led_matrix_turn_on();
		}
		else if(ubit_button_press_b()){
			ubit_led_matrix_turn_off();
		}
	}

	return 0;
}
