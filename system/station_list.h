/*
 * station_list.h
 *
 *  Created on: 08.04.2015
 *      Author: Richard
 */

#ifndef SYSTEM_STATION_LIST_H_
#define SYSTEM_STATION_LIST_H_

#include <stdint.h>
#include <system/station_list_struct.h>

uint8_t station_list_display(uint8_t action);
uint8_t station_list_handler(uint8_t *encoder_right_button, int8_t *encoder_right_count, uint8_t action);

#endif /* SYSTEM_STATION_LIST_H_ */