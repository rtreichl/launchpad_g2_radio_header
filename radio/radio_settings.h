/*
 * radio_settings.h
 *
 *  Created on: 14.04.2015
 *      Author: Richard
 */

#ifndef SYSTEM_RADIO_SETTINGS_H_
#define SYSTEM_RADIO_SETTINGS_H_

#include <radio/radio.h>
#include <system/station_list.h>

uint8_t radio_settings_brightness(uint8_t *encoder_left_button, int8_t *encoder_left_count, uint8_t *encoder_right_button, int8_t *encoder_right_count, uint8_t entry_num);
uint8_t radio_settings_contrast(uint8_t *encoder_left_button, int8_t *encoder_left_count, uint8_t *encoder_right_button, int8_t *encoder_right_count, uint8_t entry_num);
uint8_t radio_settings_source(uint8_t *encoder_left_button, int8_t *encoder_left_count, uint8_t *encoder_right_button, int8_t *encoder_right_count, uint8_t entry_num);
uint8_t radio_settings_equalizer(uint8_t *encoder_left_button, int8_t *encoder_left_count, uint8_t *encoder_right_button, int8_t *encoder_right_count, uint8_t entry_num);
uint8_t radio_settings_volume(uint8_t *encoder_left_button, int8_t *encoder_left_count, uint8_t *encoder_right_button, int8_t *encoder_right_count, uint8_t entry_num);
uint8_t radio_settings_frequency(uint8_t *encoder_left_button, int8_t *encoder_left_count, uint8_t *encoder_right_button, int8_t *encoder_right_count, uint8_t entry_num);
uint8_t radio_settings_view(uint8_t *encoder_left_button, int8_t *encoder_left_count, uint8_t *encoder_right_button, int8_t *encoder_right_count, uint8_t entry_num);
uint8_t radio_settings_station(uint8_t *encoder_left_button, int8_t *encoder_left_count, uint8_t *encoder_right_button, int8_t *encoder_right_count, uint8_t entry_num);
uint8_t radio_settings_tatp(uint8_t *encoder_left_button, int8_t *encoder_left_count, uint8_t *encoder_right_button, int8_t *encoder_right_count, uint8_t entry_num);

#endif /* SYSTEM_RADIO_SETTINGS_H_ */
