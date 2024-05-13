/*
 * log.c
 *
 *  Created on: Oct 6, 2023
 *      Author: Sander
 */
#include "log.h"
#include <stdint.h>
#include "usb_device.h"
#include "usbd_cdc_if.h"

char buffer [n];
void _log_process_msg(char* msg, uint16_t len){
		CDC_Transmit_HS((uint8_t*) msg, len);
}
