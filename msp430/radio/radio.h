/*
 * radio_new.h
 *
 *  Created on: 16.03.2015
 *      Author: Richard
 */

#ifdef RADIO_NEW_H_
#define RADIO_NEW_H_

#include <stdint.h>
#include <settings/radio_configuration.h>
#include <driver/driver.h>
#include <menu/menu.h>


//----------------------------------------------------------------------------------------
//
/// \brief Definition of some important values
//
//----------------------------------------------------------------------------------------

#define RADIO_VALID 		1
#define RADIO_NOT_VALID 	0
#define RADIO_STORE_VALUE	1
#define RADIO_AUDIO_NORMAL	0
#define RADIO_AUDIO_MUTE	1
#define RADIO_AUDIO_TA_TP	2
#define RADIO_AUDIO_SCROLL	3

//----------------------------------------------------------------------------------------
//
/// \brief Definition of some structs for the radio, the status, rsq, rds, the
///	settings
//
//----------------------------------------------------------------------------------------

typedef struct radio_status {
	uint8_t station_valid:1;
	uint8_t text_valid:1;
	uint8_t time_valid:1;
	uint8_t audio_status:2;
	uint8_t freq_valid:1;
	uint8_t name_valid:1;
	uint8_t volume_ta:1;
	uint8_t scroll_text;
} RADIO_STATUS;

typedef struct radio_rsq {
	uint8_t rssi;
	uint8_t snr;
	uint8_t multi;
	int8_t freq_off;
} RADIO_RSQ;

typedef struct radio_rds {
	char 	name[9];
	char	text[65];
	uint16_t pi;
	uint16_t pty:5;
	uint16_t ta:1;
	uint16_t tp:1;
	uint16_t ms:1;
	uint16_t di:4;
} RADIO_RDS;

typedef struct radio_settings {
	uint8_t :7;
	uint8_t backlight:1;
	uint8_t display_view:2;
	uint8_t ta_tp:1;
	uint8_t equalizer:3;
	uint8_t source:2;
	uint8_t volume;
	uint8_t volume_ta;
	uint8_t contrast;
	uint8_t brightness;
	uint16_t frequency;
} RADIO_SETTINGS;

typedef struct radio {
	RADIO_STATUS status;
	RADIO_RDS rds;
	RADIO_RSQ rsq;
	RADIO_SETTINGS settings;
} RADIO;

typedef struct brightness {
	uint32_t *sensor;
	uint8_t display;
} BRIGHTNESS;

extern RADIO radio;

//----------------------------------------------------------------------------------------
//
/// \brief Definition of functions for:\n
///	-Set the volume\n
///	-Set the settings\n
///	-Seeking frequency\n
///	-Radio main\n
///	-Init the radio\n
///	-Tune the frequency\n
///	-Store a station in flash\n
///	-Auto search\n
///	-Store the settings in flash\n
///	-Load the settings from flash\n
///	-Factory reset\n
//
//----------------------------------------------------------------------------------------

uint8_t radio_volume(ENCODER *encoder_left, ENCODER *encoder_right, MENU_STC *menu);
uint16_t radio_seeking(uint8_t up_down);
uint8_t radio_main(ENCODER *encoder_left, ENCODER *encoder_right, MENU_STC *menu);
uint8_t radio_init();
uint8_t radio_tune_freq(uint16_t freq);
uint8_t radio_store_station(uint16_t *freq, char *name, uint8_t pos);
uint8_t radio_auto_search();
uint8_t radio_store_settings(uint8_t freq, uint8_t volume);
BRIGHTNESS radio_brightness(uint8_t mode);
uint8_t radio_load_settings();
uint8_t radio_factory_state();
uint8_t radio_stand_by();
void radio_left_button_interrupt();

#endif /* RADIO_NEW_H_ */
