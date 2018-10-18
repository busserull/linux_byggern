#include "bluetooth.h"
#include <string.h>

#include "nrf_sdm.h"
#include "ble.h"
#include "ble_gap.h"

extern uint8_t __data_start__;

uint32_t bluetooth_init(){
	uint32_t err_code = 0;

	err_code = sd_softdevice_enable(NULL, NULL);
	if(err_code){
		return err_code;
	}

	static ble_enable_params_t ble_enable_params;
	memset(&ble_enable_params, 0, sizeof(ble_enable_params));
	uint32_t app_ram_base = (uint32_t)&__data_start__;

	ble_enable_params.gap_enable_params.periph_conn_count = 1;
	ble_enable_params.common_enable_params.vs_uuid_count = 1;

	err_code = sd_ble_enable(&ble_enable_params, &app_ram_base);
	return err_code;
}

uint32_t bluetooth_gap_advertise_start(){
	static uint8_t adv_data[] = {
		// Your AD structs here
	};
}
