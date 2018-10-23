#include "bluetooth.h"
#include <string.h>

#include "nrf_sdm.h"
#include "ble.h"
#include "ble_gap.h"
#include "ble_gatts.h"

#include "ubit.h"

#define CUSTOM_UUID_BASE {{\
	0x46, 0x58, 0x99, 0xa6, 0x43, 0x7f, 0x79, 0xb4,\
	0xcf, 0x4b, 0x1a, 0x2e, 0xaf, 0x10, 0xff, 0xd8\
}}
#define CUSTOM_UUID_SERVICE_UBIT 0xbabe
#define CUSTOM_UUID_CHAR_MATRIX 0xdead


extern uint8_t __data_start__;

static uint8_t m_matrix_attr_value = 0;

static struct {
	uint16_t conn_handle;
	uint16_t service_handle;
	ble_gatts_char_handles_t matrix_handles;
} m_service_ubit;

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
	uint32_t err_code = 0;

	static uint8_t adv_data[] = {
		11, BLE_GAP_AD_TYPE_COMPLETE_LOCAL_NAME,
		'B', 0xc3, 0xbc, 'c', 'k', ' ', 'D', 'i', 'c', 'h',
		/* 'P', 'a', 'r', 'e', 'i', 'd', 'o', 'l', 'i', 'a' */
	};
	uint8_t adv_data_length = 12;

	err_code = sd_ble_gap_adv_data_set(
		adv_data, adv_data_length, NULL, 0
	);
	if(err_code){
		return err_code;
	}

	ble_gap_adv_params_t adv_params;
	memset(&adv_params, 0, sizeof(ble_gap_adv_params_t));
	adv_params.type = BLE_GAP_ADV_TYPE_ADV_IND;
	adv_params.interval = 0x80;

	err_code = sd_ble_gap_adv_start(&adv_params);
	return err_code;
}

uint32_t bluetooth_gatts_start(){
	uint32_t err_code = 0;

	ble_uuid128_t base_uuid = CUSTOM_UUID_BASE;

	ble_uuid_t ubit_service_uuid;
	ubit_service_uuid.uuid = CUSTOM_UUID_SERVICE_UBIT;

	err_code = sd_ble_uuid_vs_add(
		&base_uuid,
		&ubit_service_uuid.type
	);


	err_code = sd_ble_gatts_service_add(
		BLE_GATTS_SRVC_TYPE_PRIMARY,
		&ubit_service_uuid,
		&m_service_ubit.service_handle
	);


	ble_uuid_t matrix_uuid;
	matrix_uuid.uuid = CUSTOM_UUID_CHAR_MATRIX;

	err_code = sd_ble_uuid_vs_add(&base_uuid, &matrix_uuid.type);


	static uint8_t matrix_char_desc[] = {
		'L', 'E', 'D', ' ', 'M', 'a', 't', 'r', 'i', 'x',
	};
	ble_gatts_char_md_t matrix_char_md;
	memset(&matrix_char_md, 0, sizeof(matrix_char_md));
	matrix_char_md.char_props.read = 1;
	matrix_char_md.char_props.write = 1;
	matrix_char_md.p_char_user_desc = matrix_char_desc;
	matrix_char_md.char_user_desc_max_size = 10;
	matrix_char_md.char_user_desc_size = 10;


	ble_gatts_attr_md_t matrix_attr_md;
	memset(&matrix_attr_md, 0, sizeof(matrix_attr_md));
	matrix_attr_md.read_perm.lv = 1;
	matrix_attr_md.read_perm.sm = 1;
	matrix_attr_md.write_perm.lv = 1;
	matrix_attr_md.write_perm.sm = 1;
	matrix_attr_md.vloc = BLE_GATTS_VLOC_USER;

	ble_gatts_attr_t matrix_attr;
	memset(&matrix_attr, 0, sizeof(matrix_attr));
	matrix_attr.p_uuid = &matrix_uuid;
	matrix_attr.p_attr_md = &matrix_attr_md;
	matrix_attr.init_len = 1;
	matrix_attr.max_len = 1;
	matrix_attr.p_value = &m_matrix_attr_value;


	err_code = sd_ble_gatts_characteristic_add(
		m_service_ubit.service_handle,
		&matrix_char_md,
		&matrix_attr,
		&m_service_ubit.matrix_handles
	);

	return err_code;
}

void bluetooth_serve_forever(){
	uint8_t ble_event_buffer[100] = {0};
	uint16_t ble_event_buffer_size = 100;

	while(1){
		if(m_matrix_attr_value != 0){
			ubit_led_matrix_turn_on();
		}
		else{
			ubit_led_matrix_turn_off();
		}

		while(
			sd_ble_evt_get(
				ble_event_buffer,
				&ble_event_buffer_size
			) != NRF_ERROR_NOT_FOUND
			){

			ble_evt_t * p_ble_event = (ble_evt_t *)ble_event_buffer;
			uint16_t event_id = p_ble_event->header.evt_id;

			switch(event_id){
				case BLE_GAP_EVT_CONNECTED:
					m_service_ubit.conn_handle =
						p_ble_event->evt.gap_evt.conn_handle;

					sd_ble_gatts_sys_attr_set(
						m_service_ubit.conn_handle,
						0,
						0,
						0
					);
					break;

				case BLE_GAP_EVT_DISCONNECTED:
					m_service_ubit.conn_handle =
						BLE_CONN_HANDLE_INVALID;

					bluetooth_gap_advertise_start();
					break;

				default:
					break;
			}

			ble_event_buffer_size = 100;
		}
		ble_event_buffer_size = 100;
	}
}
