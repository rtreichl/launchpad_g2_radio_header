#ifndef RADIO_CONF_H_
#define RADIO_CONF_H_

#include <driver/external/include/si4735_cmd_prop.h>
#include <libs/time.h>

/* Define macros for version */

#define RADIO_VERSION_MAJOR	3
#define RADIO_VERSION_MINOR	10

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Radio Macros for gloabl configuration settings
///	@{
///
#define RADIO_VALID_SNR			15				///< Valid signal to noise ratio 10dB
#define RADIO_VALID_RSSI		20				///< Valid reseived signal strengh 25dBuV
#define RADIO_BOT_FREQ			0x222E 			///< Lowest possible freqency 87,50 MHz
#define RADIO_TOP_FREQ			0x2A30			///< Highest possible freqency 108,00 MHz
#define RADIO_SEEK_FREQ_SPACE	SKSPACE_10		///< Frequency step size 100 kHz
#define RADIO_CALBC1			CALBC1_16MHZ	///< MCU basis clock 16 MHz
#define RADIO_CALDCO			CALDCO_16MHZ	///< MCU basis clock 16 MHz
#define RADIO_DCO_FREQ			16				///< MCU basis clock 16 MHz
#define RADIO_MCLK				16				///< MCU basis clock 16 MHz
#define RADIO_SCLK				2				///< MCU slave clock 2 MHz
#define RADIO_I2C_FREQ			100				///< I2C clock 100 kHz
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Factory_State Macros for factory state
///	@{
///
#define RADIO_FACTORY_FREQENCY		0			///< Seekup on start
#define RADIO_FACTORY_VIEW			0			///< RDS view
#define RADIO_FACTORY_VOLUME		20			///< Normal volume 20%
#define RADIO_FACTORY_EQUALIZER		0			///< Equalizer POP
#define RADIO_FACTORY_SOURCE		0			///< Source FM
#define RADIO_FACTORY_BRIGHTNESS	35			///< Brightness 70%
#define RADIO_FACTORY_CONTRAST		6			///< Contrast 60%
#define RADIO_FACTORY_TATP			0			///< TA TP off
#define RADIO_FACTORY_VOLUME_TA		50			///< TA volume 50%
#define RADIO_FACTORY_BACKLIGHT		0			///< Backlight autmatic
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Scroll Macros for scroll interfaces
///	@{
///
#define RADIO_BRIGHTNESS_MAX 	50				///< Brightness max 50
#define RADIO_BRIGHTNESS_MIN 	0				///< Brightness min 0
#define RADIO_BRIGHTNESS_STEP 	1				///< Brightness step 1
#define RADIO_CONTRAST_MAX 		10				///< Contrast max 10
#define RADIO_CONTRAST_MIN 		0				///< Contrast min 0
#define RADIO_CONTRAST_STEP 	1				///< Contrast step 1
#define RADIO_VOLUME_MAX 		100				///< Volume max 100
#define RADIO_VOLUME_MIN 		0				///< Volume min 0
#define RADIO_VOLUME_STEP 		2				///< Volume step 2
#define RADIO_FREQENCY_MAX		RADIO_TOP_FREQ	///< Freqency max RADIO_TOP_FREQ
#define RADIO_FREQENCY_MIN		RADIO_BOT_FREQ	///< Freqency min RADIO_BOT_FREQ
#define RADIO_FREQENCY_STEP		10				///< Freqency step 10 for 100 kHz
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Store Macros for flash storing
///	@{
///
#define RADIO_STATION_NAME_STORE_ADR 	0x1000	///< Store adress at start adress from segment D for 14 elements
#define RADIO_STATION_NAME_STORE_SIZE 	8		///< Store size of one station name
#define RADIO_STATION_FREQ_STORE_ADR 	0x1070	///< Store adress after 14 station name elements
#define RADIO_STATION_FREQ_STORE_SIZE 	2		///< Store size of one station freqency
#define RADIO_SETTINGS_STORE_ADR 		0x108C	///< Store adress after 14 station freqency elements
#define RADIO_INIT_STORE_ADR 			0x10B8	///< Store adress at end of segment B
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Button Macros for button states
///	@{
///
#define BUTTON_LONG 			'l'				///< Value for encoder button pressed long
#define BUTTON_SHORT 			'k'				///< Value for encoder button pressed short
#define BUTTON_FREE 			'f'				///< Value for encoder button idle state
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Timer Macros for timer use
///	@{
///
#define RADIO_TIMER_RSQ			0				///< Timer for radio signal quality
#define RADIO_TIMER_RDS			1				///< Timer for radio digital service
#define RADIO_TIMER_MINUTE		2				///< Timer for minute counting
#define RADIO_TIMER_DISPLAY		3				///< Timer for display refresh
#define RADIO_TIMER_ENCODER		4				///< Timer for encoder button
#define RADIO_TIMER_BACKLIGHT	5				///< Timer for backlight controll
#define RADIO_TIMER_USED		6				///< Must be changed if a timer is added
///
/// @}
///
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Count Macros for time refresh rates
///	@{
///
#define RADIO_COUNT_ENCODER		10				///< Count for encoder button execute underlying code every 10ms
#define	RADIO_COUNT_MINUTE		60000			///< Count for minute counting execute underlying code every 60s
#define RADIO_COUNT_RSQ			1000			///< Count for radio signal quality execute underlying code every 1s
#define RADIO_COUNT_RDS			200				///< Count for radio digital service execute underlying code every 200ms
#define RADIO_COUNT_DISPLAY 	500				///< Count for display refresh execute underlying coder every 500ms
#define RADIO_COUNT_BACKLIGHT	200				///< Count for backlight calculation is executed every 200ms
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Time_Date Macros for time and date for cold start
///	@{
///
#define RADIO_DATE_DAY			BUILD_DAY		///< Day where firmware is build
#define RADIO_DATE_MONTH		BUILD_MONTH		///< Month where firmware is build
#define RADIO_DATE_YEAR			BUILD_YEAR		///< Year where firmware is build
#define RADIO_TIME_HOUR			BUILD_HOUR		///< Hour where firmware is build
#define RADIO_TIME_MINUTE		BUILD_MIN		///< Minute where firmware is build
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////////////////
///
/// \defgroup Stuff Macros for all other kinds of configuration
///	@{
///
#define RADIO_AMPLIFIER_GAIN	3				///< Gain for tpa2016d2 amplifier in dB
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////

///----------------------------------------------------------------------------------------
///
/// \defgroup States Macros for boolean values which are used for radio
///	@{
///
#define RADIO_TRUE 				1				///< Logical high or true is equal to a one
#define RADIO_FALSE 			0				///< Logical low or false is equal to a zero
///
///	@}
///
///////////////////////////////////////////////////////////////////////////////////////////

#endif /* RADIO_CONF_H_ */
