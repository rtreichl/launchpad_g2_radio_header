///----------------------------------------------------------------------------------------
///
/// \file radio.c
///
/// \brief 
///
/// \date 24.09.2015
///
/// \author Richard Treichl
///
/// \remark
///
/// \todo
///
/// \version	1.0
///
///----------------------------------------------------------------------------------------


#include <radio/radio.h>
#include <driver/driver.h>
#include <settings/radio_configuration.h>

uint16_t radio_init(BUTTON *button_1, BUTTON *button_2)
{
	basic_clock_init();
	timer_init();
	i2c_init(RADIO_SCLK, RADIO_I2C_FREQ);

	//enable LED and turn it on
	P1DIR |= BIT0;
	P1OUT |= BIT0;


	si4735_init(RADIO_FACTORY_VOLUME * SI4735_VOLUME_MAX / (RADIO_VOLUME_MAX - RADIO_VOLUME_MIN), RADIO_BOT_FREQ);
	si4735_fm_seek_start(0);
	si4735_set_property(RX_VOLUME, RADIO_FACTORY_VOLUME * SI4735_VOLUME_MAX / (RADIO_VOLUME_MAX - RADIO_VOLUME_MIN));

	//enable amplifier
	P2DIR |= BIT5;
	P2OUT &= ~BIT5;

	button_init((uint16_t *)&(timer_count[RADIO_TIMER_BUTTON]));

	button_1->int_number_button = HEADER_TAST_INT;
	button_2->int_number_button = BOARD_TAST_INT;
	button_create(button_1, BUTTON_PULL_DOWN);
	button_create(button_2, BUTTON_PULL_UP);

	P1DIR |= BIT0;

	return 0;
}

uint16_t radio_main(BUTTON *button_1, BUTTON *button_2)
{
	static uint8_t last_button_1 = 0, last_button_2 = 0, time_1 = 0, time_2 = 0;
	static uint8_t volume = RADIO_FACTORY_VOLUME;
	time_1++;
	time_2++;

	if(last_button_1 != 0 && time_1 >= RADIO_BUTTON_INPUT_TIME) {
		time_1 = 0;
		switch(button_1->short_pressed) {
		case 1:
			RADIO_HEADER_BUTTON_ONE_FUNC();
			break;
		case 2:
			RADIO_HEADER_BUTTON_TWICE_FUNC();
			break;
		default:
			button_1->short_pressed = 0;
		}
		last_button_1 = 0;
		button_1->short_pressed = 0;
	}
	if(last_button_2 != 0 && time_2 >= RADIO_BUTTON_INPUT_TIME) {
		time_2 = 0;
		switch(button_2->short_pressed) {
		case 1:
			RADIO_BOARD_BUTTON_ONE_FUNC();
			P1OUT &= ~BIT3;
			break;
		case 2:
			RADIO_BOARD_BUTTON_TWICE_FUNC();
			P1OUT &= ~BIT3;
			break;
		default:
			button_2->short_pressed = 0;
		}
		last_button_2 = 0;
		button_2->short_pressed = 0;
	}
	else {
		P1OUT |= BIT3;
	}

	if(last_button_1 != button_1->short_pressed) {
		time_1 = 0;
		last_button_1 = button_1->short_pressed;
	}

	if(last_button_2 != button_2->short_pressed) {
		time_2 = 0;
		last_button_2 = button_2->short_pressed;
	}
	return 0;
}

uint16_t radio_volume(uint8_t *volume, int8_t up_down)
{
	if(*volume < RADIO_VOLUME_MAX && *volume > RADIO_VOLUME_MIN) {
		if(up_down != RADIO_VOLUME_UP) {
			*volume -= RADIO_VOLUME_STEP;
		}
		else {
			*volume += RADIO_VOLUME_STEP;
		}
		si4735_set_property(RX_VOLUME, ((uint16_t)(*volume) * SI4735_VOLUME_MAX) / (RADIO_VOLUME_MAX - RADIO_VOLUME_MIN));
	}
	return 0;
}

uint16_t radio_mute()
{
	static uint8_t mute = 0;
	if(mute) {
		si4735_set_property(RX_HARD_MUTE, 0);
		mute = 0;
	}
	else {
		si4735_set_property(RX_HARD_MUTE, 0x03);
		mute = RADIO_VOLUME_MUTE;
	}
	return 0;
}

uint16_t radio_seeking()
{
	si4735_fm_seek_start(1);
	return 0;
}
