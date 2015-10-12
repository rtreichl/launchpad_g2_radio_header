///////////////////////////////////////////////////////////////////////////////////////////
///
/// \file radio_settings.c
///
/// \brief menu.h includes all necessary functions macros and structs for the radio data\n
/// service
///
/// \date 14.04.2015
///
/// \author Richard Treichl
///
/// \remark
///
/// \todo Finish documentation
///
/// \version	1.0
///
///////////////////////////////////////////////////////////////////////////////////////////

#include <radio/radio_settings.h>
#if
///////////////////////////////////////////////////////////////////////////////////////////
///
/// \brief Sets the brightness
///
/// \param	<encoder_left_button>		[in]	state of the left encoder button
/// \param	<encoder_left_count>		[in]	value of the left encoder
/// \param	<encoder_right_button>		[in]	state of the right encoder button
/// \param	<encoder_right_count>		[in]	value of the right encoder
/// \param	<entry_num>					[in]	the entry in the menu
///
/// \retval uint8_t
///
/// \remarks
///
///////////////////////////////////////////////////////////////////////////////////////////

uint8_t radio_settings_brightness(ENCODER *encoder_left, ENCODER *encoder_right, MENU_STC *menu)
{
	if(menu->y == MENU_THIRD_ENTRY) {
		if(menu_encoder_range(encoder_right, &(radio.settings.brightness), 1, RADIO_BRIGHTNESS_MAX, RADIO_BRIGHTNESS_MIN, RADIO_BRIGHTNESS_STEP, RADIO_FALSE)) {
				radio_brightness(0);
			}
		menu_scroll_settings(radio.settings.brightness * 2);
	}
	else {
		radio.settings.backlight = menu->y;
		return SHORT_UP_TO_PARENT;
	}

	if(*encoder_right->button == BUTTON_SHORT) {
		*encoder_right->button = BUTTON_FREE;
		radio_store_settings(0, 0);
		return SHORT_UP_TO_CHILD;
	}

	return STAY_ON_MENU_POINT;
}

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \brief Sets the contrast
///
/// \param	<encoder_left_button>		[in]	state of the left encoder button
/// \param	<encoder_left_count>		[in]	value of the left encoder
/// \param	<encoder_right_button>		[in]	state of the right encoder button
/// \param	<encoder_right_count>		[in]	value of the right encoder
/// \param	<entry_num>					[in]	the entry in the menu
///
/// \retval uint8_t
///
/// \remarks
///
///////////////////////////////////////////////////////////////////////////////////////////

uint8_t radio_settings_contrast(ENCODER *encoder_left, ENCODER *encoder_right, MENU_STC *menu)
{

	if(menu_encoder_range(encoder_right, &(radio.settings.contrast), 1, RADIO_CONTRAST_MAX, RADIO_CONTRAST_MIN, RADIO_CONTRAST_STEP, RADIO_FALSE)) {
		lcd_contrast(radio.settings.contrast / RADIO_CONTRAST_STEP);
	}

	if(*encoder_right->button == BUTTON_SHORT) {
		*encoder_right->button = BUTTON_FREE;
		radio_store_settings(0, 0);
		return SHORT_UP_TO_CHILD;
	}
	else {
		menu_scroll_settings(radio.settings.contrast * 10);
	}
	return STAY_ON_MENU_POINT;
}

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \brief Sets the audio source
///
/// \param	<encoder_left_button>		[in]	state of the left encoder button
/// \param	<encoder_left_count>		[in]	value of the left encoder
/// \param	<encoder_right_button>		[in]	state of the right encoder button
/// \param	<encoder_right_count>		[in]	value of the right encoder
/// \param	<entry_num>					[in]	the entry in the menu
///
/// \retval uint8_t
///
/// \remarks
///
///////////////////////////////////////////////////////////////////////////////////////////

uint8_t radio_settings_source(ENCODER *encoder_left, ENCODER *encoder_right, MENU_STC *menu)
{
	AUDIO_SW_LINE_DIR |= AUDIO_SW_LINE_PIN;
	AUDIO_SW_GND_DIR |= AUDIO_SW_GND_PIN;

	switch(menu->y) {
	default:
	case RADIO_SETTINGS_SOURCE_FM:
		radio.settings.source = RADIO_SETTINGS_SOURCE_FM;
		AUDIO_SW_LINE_OUT &= ~AUDIO_SW_LINE_PIN;
		AUDIO_SW_GND_OUT &= ~AUDIO_SW_GND_PIN;
		//TODO Implement switch si4735 to FM only when AM mode is implemented else just switch audio switch
		break;
	case RADIO_SETTINGS_SOURCE_AM:
		radio.settings.source = RADIO_SETTINGS_SOURCE_AM;
		AUDIO_SW_LINE_OUT &= ~AUDIO_SW_LINE_PIN;
		AUDIO_SW_GND_OUT &= ~AUDIO_SW_GND_PIN;
		//TODO Implement switch si4735 to AM only when AM mode is implemented else just do nothing else
		break;
	case RADIO_SETTINGS_SOURCE_LINEIN:
		radio.settings.source = RADIO_SETTINGS_SOURCE_LINEIN;
		AUDIO_SW_LINE_OUT |= AUDIO_SW_LINE_PIN;
		AUDIO_SW_GND_OUT |= AUDIO_SW_GND_PIN;
		//TODO set si4735 in powerdown modus only if ta/tp mode is off else poll flag and swith to si4735 for duration ta flag is set
	}
	radio_store_settings(0, 0);
	return SHORT_UP_TO_PARENT;
}

///////////////////////////////////////////////////////////////////////////////////////////
//
/// \brief Sets the equalizer mode
///
/// Following modes are supported:\n
///	-Rock\n
///	-Pop\n
///	-Hip/Hop\n
///	-News\n
///	-Classic\n
///	-Jazz\n
///
/// \param	<encoder_left_button>		[in]	state of the left encoder button
/// \param	<encoder_left_count>		[in]	value of the left encoder
/// \param	<encoder_right_button>		[in]	state of the right encoder button
/// \param	<encoder_right_count>		[in]	value of the right encoder
/// \param	<entry_num>					[in]	the entry in the menu
///
/// \retval uint8_t
///
/// \remarks
///
///////////////////////////////////////////////////////////////////////////////////////////

uint8_t radio_settings_equalizer(ENCODER *encoder_left, ENCODER *encoder_right, MENU_STC *menu)
{
	radio.settings.equalizer = TPA2016D2_POP + menu->y;

	tpa2016d2_equalizer_mode((enum TPA2016D2_EQUALIZER)radio.settings.equalizer, RADIO_AMPLIFIER_GAIN);
	radio_store_settings(0, 0);
	return SHORT_UP_TO_PARENT;
}

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \brief Sets the volume
///
/// Calculates the new volume acording to the encoder value. Additionally u\n
///	can choose to set the startup volume or the TA/TP volume\n
///
/// \param	<encoder_left_button>		[in]	state of the left encoder button
/// \param	<encoder_left_count>		[in]	value of the left encoder
/// \param	<encoder_right_button>		[in]	state of the right encoder button
/// \param	<encoder_right_count>		[in]	value of the right encoder
/// \param	<entry_num>					[in]	the entry in the menu
///
/// \retval uint8_t
///
/// \remarks
///
///////////////////////////////////////////////////////////////////////////////////////////

uint8_t radio_settings_volume(ENCODER *encoder_left, ENCODER *encoder_right, MENU_STC *menu)
{
	static int8_t tmp_volume = 0;
	if(tmp_volume == 0 && menu->y != 0) {
		tmp_volume = radio.settings.volume;
		radio.status.audio_status = RADIO_AUDIO_SCROLL;
		if(menu->y == RADIO_SETTINGS_MENU_VOL_TA) {
			radio.settings.volume = radio.settings.volume_ta;
		}
		if(menu->y == RADIO_SETTINGS_VOLUME_START) {
			RADIO_SETTINGS tmp_settings;
			flash_read(&tmp_settings, sizeof(tmp_settings), RADIO_SETTINGS_STORE_ADR);
			radio.settings.volume  = tmp_settings.volume;
		}
	}

	if(*encoder_right->button == BUTTON_SHORT) {
		*encoder_right->button = BUTTON_FREE;
		if(tmp_volume != 0) {
			if(menu->y == RADIO_SETTINGS_VOLUME_START) {
				radio_store_settings(0, 1);
			}
			else if(menu->y == RADIO_SETTINGS_MENU_VOL_TA) {
				radio.settings.volume_ta = radio.settings.volume;
				radio_store_settings(0, 0);
			}
			radio.settings.volume = tmp_volume;
			tmp_volume = 0;
			radio.status.audio_status = RADIO_AUDIO_SCROLL;
			radio_volume(encoder_left, encoder_right, menu);
		}
		return SHORT_UP_TO_CHILD;
	}
	else {
		radio_volume(encoder_left, encoder_right, menu);
		menu_scroll_settings(radio.settings.volume);
	}
	return STAY_ON_MENU_POINT;
}

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \brief Sets the frequency
///
/// In here the u can seach for the next station up- or downwards or just set\n
///	the current frequency\n
///
/// \param	<encoder_left_button>		[in]	state of the left encoder button
/// \param	<encoder_left_count>		[in]	value of the left encoder
/// \param	<encoder_right_button>		[in]	state of the right encoder button
/// \param	<encoder_right_count>		[in]	value of the right encoder
/// \param	<entry_num>					[in]	the entry in the menu
///
/// \retval uint8_t
///
/// \remarks
///
///////////////////////////////////////////////////////////////////////////////////////////

uint8_t radio_settings_frequency(ENCODER *encoder_left, ENCODER *encoder_right, MENU_STC *menu)
{
	uint16_t tmp_freq = 0;
	uint8_t ret = 0;
	tmp_freq = radio.settings.frequency;
	switch(menu->y) {
	case RADIO_SETTINGS_FREQ_SEEK_UP:
		radio.settings.frequency = 0;
		radio_store_settings(1, 0);
		radio.settings.frequency = tmp_freq;
		return SHORT_UP_TO_PARENT;
	case RADIO_SETTINGS_FREQ_SEEK_DOWN:
		radio.settings.frequency = 0xFFFF;
		radio_store_settings(1, 0);
		radio.settings.frequency = tmp_freq;
		return SHORT_UP_TO_PARENT;
	case RADIO_SETTINGS_FREQ_CHOOSE:
		ret = station_list_handler(encoder_left, encoder_right, menu);
		radio.settings.frequency = tmp_freq;
		return ret;
	}
	return SHORT_UP_TO_CHILD;
}

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \brief Choose the data to display
///
/// \param	<encoder_left_button>		[in]	state of the left encoder button
/// \param	<encoder_left_count>		[in]	value of the left encoder
/// \param	<encoder_right_button>		[in]	state of the right encoder button
/// \param	<encoder_right_count>		[in]	value of the right encoder
/// \param	<entry_num>					[in]	the entry in the menu
///
/// \retval uint8_t
///
/// \remarks
///
///////////////////////////////////////////////////////////////////////////////////////////

//TODO: First four parameters really needed?
uint8_t radio_settings_view(ENCODER *encoder_left, ENCODER *encoder_right, MENU_STC *menu)
{
	radio.settings.display_view = menu->y;
	radio_store_settings(0, 0);
	return SHORT_UP_TO_PARENT;
	//return SHORT_UP_TO_CHILD;
}

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \brief Seeks the next station/all available
///
/// Following modes are supported:\n
///	-Seek up\n
///	-Seek down\n
///	-Auto Search\n
///	-Select station\n
///
/// \param	<encoder_left_button>		[in]	state of the left encoder button
/// \param	<encoder_left_count>		[in]	value of the left encoder
/// \param	<encoder_right_button>		[in]	state of the right encoder button
/// \param	<encoder_right_count>		[in]	value of the right encoder
/// \param	<entry_num>					[in]	the entry in the menu
///
/// \retval uint8_t
///
/// \remarks
///
///////////////////////////////////////////////////////////////////////////////////////////

uint8_t radio_settings_station(ENCODER *encoder_left, ENCODER *encoder_right, MENU_STC *menu)
{
	switch(menu->y) {
	case RADIO_SETTINGS_SEEKING_UP:
		radio.settings.frequency = radio_seeking(1);
		return SHORT_UP_TO_PARENT;
	case RADIO_SETTINGS_SEEKING_DOWN:
		radio.settings.frequency = radio_seeking(0);
		return SHORT_UP_TO_PARENT;
	case RADIO_SETTINGS_STORE_STATION:
	case RADIO_SETTINGS_STATION_VIEW:
		return station_list_handler(encoder_left, encoder_right, menu);
	case RADIO_SETTINGS_AUTO_SEARCH:
		radio_auto_search();
		return SHORT_UP_TO_PARENT;
	}
	return SHORT_UP_TO_CHILD;
}

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \brief Set TA/TP
///
/// \param	<encoder_left_button>		[in]	state of the left encoder button
/// \param	<encoder_left_count>		[in]	value of the left encoder
/// \param	<encoder_right_button>		[in]	state of the right encoder button
/// \param	<encoder_right_count>		[in]	value of the right encoder
/// \param	<entry_num>					[in]	the entry in the menu
///
/// \retval uint8_t
///
/// \remarks
///
///////////////////////////////////////////////////////////////////////////////////////////

uint8_t radio_settings_tatp(ENCODER *encoder_left, ENCODER *encoder_right, MENU_STC *menu)
{
	radio.settings.ta_tp = menu->y;
	radio_store_settings(0, 0);
	return SHORT_UP_TO_PARENT;
	//return SHORT_UP_TO_CHILD;
}

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \brief Reset the settings
///
/// \param	<encoder_left_button>		[in]	state of the left encoder button
/// \param	<encoder_left_count>		[in]	value of the left encoder
/// \param	<encoder_right_button>		[in]	state of the right encoder button
/// \param	<encoder_right_count>		[in]	value of the right encoder
/// \param	<entry_num>					[in]	the entry in the menu
///
/// \retval uint8_t
///
/// \remarks
///
///////////////////////////////////////////////////////////////////////////////////////////

uint8_t radio_settings_reset(ENCODER *encoder_left, ENCODER *encoder_right, MENU_STC *menu)
{
	switch(menu->y) {
	case RADIO_SETTINGS_RESET_NO:
		return SHORT_UP_TO_PARENT;
	case RADIO_SETTINGS_RESET_YES:
		radio_factory_state();
		return SHORT_UP_TO_PARENT;
	}
	return SHORT_UP_TO_CHILD;
}
#endif
