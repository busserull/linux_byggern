#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "ubit.h"

#include "bluetooth.h"

int main(){
	ubit_uart_init();
	ubit_led_matrix_init();
	ubit_buttons_init();

	ubit_uart_print("\n\r\n\r");

	uint32_t err_code = 0;

	err_code = bluetooth_init();
	ubit_uart_print("BLE Enable error code: %d\n\r", err_code);


	err_code = bluetooth_gap_advertise_start();

	err_code = bluetooth_gatts_start();

	bluetooth_serve_forever();

	return 0;
}
