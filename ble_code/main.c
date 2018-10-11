#include <stdint.h>
#include "ubit.h"

/* #include "ble.h" */

int main(){
	/* uint32_t err_code = 0; */

	/* sd_softdevice_enable(NULL, NULL); */

	ubit_uart_init();

	while(1){
		ubit_uart_print(
			"Here are some nubers: |%6d|, |%d|, |%6d|, |%d|\n\r",
			12, -751, -7, 571
		);
	}

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
