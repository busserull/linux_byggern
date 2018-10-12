#include <stdint.h>
#include "ubit.h"

/* #include "ble.h" */

int main(){
	/* uint32_t err_code = 0; */

	/* sd_softdevice_enable(NULL, NULL); */

	ubit_uart_init();
	ubit_led_matrix_init();
	ubit_buttons_init();

	int button_counter = 0;

	while(1){
		if(ubit_button_press_a()){
			ubit_led_matrix_turn_on();
			button_counter++;
		}
		else if(ubit_button_press_b()){
			ubit_led_matrix_turn_off();
			button_counter--;
		}

		ubit_uart_print("Button counter: %6d\n\r", button_counter);
	}

	return 0;
}
