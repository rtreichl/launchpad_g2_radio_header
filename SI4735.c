/*
 * SI4735.c
 *
 *  Created on: 04.07.2013
 *      Author: Alexander Raskopf
 *      Status: Nach dem Test
 *
 *   Kommentar: In bearbeitung: die Frequenz soll �ber FM_Tune_Status abgefragt und im Flash gespeichert werden
 *   							es soll auch die zuletzt verwendete Lautst�rke gespeichert werden
 */
#include "MSP430G2553_USCI_I2C.h"
#include "msp430.h"
#include "SI4735.h"
#include "Timer.h"
#include <stdio.h>



#define SI4735_volume 20 		// Maximalwert f�r die Lautst�rke
#define SI4735_volume_start  20 // Startlautst�rke

void SI4735_Set_Volume (signed char Volume) //setzt Volume als die Lautst�rke
{
	char Command[7];
	char response = 0;
	sprintf(Command, "%c%c%c%c%c%c", 0x12,0x00,0x40,0x00,0x00,Volume);
	I2C_write_and_read(6,Command,1,&response);
}


void SI4735_Fm_Tune_Freq_2 (unsigned int Frequenz) //setzt den FM Empfang und legt die Frequenz zwischen 64 - 108 MHz in 10 kHz einheiten fest
{
	char Command[6];
	char response;
	sprintf(Command, "%c%c%c%c%c", 0x20,0x01,(0xFF & (Frequenz>>8)),(0xFF & Frequenz),0x00);
	I2C_write_and_read(5,Command,1,&response);
 	_delay_ms(1);
 	SI4735_Fm_Tune_Status();
}

void SI4735_FM_RDS_INT_SOURCE() //RDS interrupt Quelle einstellen
{
	char Command[7];
	sprintf(Command, "%c%c%c%c%c%c", 0x12,0x00,0x15,0x00,0x00,0x01);
	USCI_I2C_WRITE1(6,Command);
}

void SI4735_Power_Up (void)	//einschalten des Si4735 aktivieren des Analogen Audio Ausgangs
{
	char Command[4];
	sprintf(Command, "%c%c%c", 0x01,0xD0,0x05);
	USCI_I2C_WRITE1(3, Command);
}

void SI4735_Power_Down (void)	//einschalten des Si4735 aktivieren des Analogen Audio Ausgangs
{
	char Command[2];
	sprintf(Command, "%c", 0x11);
	USCI_I2C_WRITE1(1, Command);
}

void SI4735_Refclk_Freq (void)	//aktivieren und festlegen der referenc clock frequency 32,768 kHz
{
	char Command[7];
	sprintf(Command, "%c%c%c%c%c%c", 0x12,0x00,0x02,0x01,0x7E,0xF4);
	USCI_I2C_WRITE1(6, Command);
}

void SI4735_RX_Volume (void)	//setzt den Maximalwert f�r die Lautst�rke
{
	char Command[7];
	sprintf(Command, "%c%c%c%c%c%c", 0x12,0x00,0x40,0x00,0x00,SI4735_volume);
	USCI_I2C_WRITE1(6, Command);
}

void SI4735_Fm_Deemphasis (void)	//entzerrt die Empfangene Frequenz, wert f�r Europa, Australien und Japan betr�gt 50�s
{
	char Command[7];
	sprintf(Command, "%c%c%c%c%c%c", 0x12,0x00,0x11,0x00,0x00,0x01);
	USCI_I2C_WRITE1(6, Command);
}

void SI4735_Rx_Hard_Mute (void)	//setzt den Audio Ausgang auf stumm, L und R Audio Ausgang k�nnten selbst�ndig auf stumm geschaltet sein
{
	char Command[7];
	sprintf(Command, "%c%c%c%c%c%c", 0x12,0x00,0x40,0x01,0x00,0x00);
	USCI_I2C_WRITE1(6, Command);
}

void SI4735_Fm_Seek_Band_Bottom (void)	//legt die untere Grenze f�r die Frequenzsuche fest
{
	char Command[7];
	sprintf(Command, "%c%c%c%c%c%c", 0x12,0x00,0x14,0x00,0x22,0x6A);
	USCI_I2C_WRITE1(6, Command);
}

void SI4735_Fm_Seek_Band_Top (void)	//legt die obere Grenze f�r die Frequenzsuche fest
{
	char Command[7];
	sprintf(Command, "%c%c%c%c%c%c", 0x12,0x00,0x14,0x01,0x2A,0x26);
	USCI_I2C_WRITE1(6, Command);
}

void SI4735_Fm_Tune_Freq (void)	//setzt den FM Empfang und legt die Frequenz zwischen 64 - 108 MHz in 10 kHz einheiten fest
{
	char Command[7];
	sprintf(Command, "%c%c%c%c%c", 0x20,0x00,0x2A,0x12,0x00);
	USCI_I2C_WRITE1(5, Command);
}

void SI4735_FM_RDS_INT_FIFO_COUNT()	//RDS FIFO Count festlegen
{
	char Command[7];
	sprintf(Command, "%c%c%c%c%c%c", 0x12,0x00,0x15,0x01,0x00,0x04);
	USCI_I2C_WRITE1(6,Command);
}

void SI4735_FM_RDS_CONFIG() //RDS Einstellungen
{
	char Command[7];
	sprintf(Command, "%c%c%c%c%c%c", 0x12,0x00,0x15,0x02,0xAA,0x01);
	USCI_I2C_WRITE1(6,Command);
}

void SI4735_Fm_Tune_Status (void)	//gibt den Aktuellen Wert der Frequenz oder Suchlauf zur�ck, ist noch in arbeit
{
	char Command[3];
	char response[8];
	sprintf(Command, "%c%c", 0x22,0x00);
	I2C_write_and_read(2,Command,8,response);
    _delay_ms(1);
}

void SI4735_Start_Volume (void)	//setzt den Startwert f�r die Lautst�rke
{
	char Command[7];
	if(SI4735_volume==63)
	{
		sprintf(Command, "%c%c%c%c%c%c", 0x12,0x00,0x40,0x00,0x00,SI4735_volume_start);
		USCI_I2C_WRITE1(6, Command);
	}
}

void SI4735_seek_Down(void)	//Frequenzsuchlauf f�r niedrige Frequenzen
{
	char Command[3];
	sprintf(Command, "%c%c", 0x21,0x0C);
	USCI_I2C_WRITE1(2, Command);
}

void SI4735_seek_Up(void)	//Frequensuchlauf f�r h�here Frequenzen
{
	char Command[3];
	sprintf(Command, "%c%c", 0x21,0x04);
	USCI_I2C_WRITE1(2, Command);
}

void SI4735_INIT(void)	// Enth�lt alle f�r den Start ben�tigten Parameter
{
   //SEN
	P3DIR |=   BIT4;
	P3OUT &=~  BIT4;

	//P2DIR |= BIT4;

	// Clear Reset
	P2DIR |=  BIT3;
	P2OUT &=~  BIT3;

	//_delay_ms(1);
	// Set Reset
	P2OUT |=  BIT3;		// Ausgang auf low gesetzt

	//_delay_ms(1);

	//GPO2/INT
	P2REN |= BIT4;
	P2OUT |= BIT4;

	//_delay_ms(1);

	SI4735_Power_Up ();

	_delay_ms(20);

	SI4735_RX_Volume ();

	__delay_cycles(8000);

	SI4735_Refclk_Freq ();
	while((P2IN & BIT4));

	SI4735_Fm_Deemphasis ();
	while((P2IN & BIT4));

	_delay_ms(200);
	SI4735_Fm_Tune_Freq();
	while((P2IN & BIT4));

	SI4735_FM_RDS_INT_SOURCE();
	SI4735_FM_RDS_INT_FIFO_COUNT();
	SI4735_FM_RDS_CONFIG();
}
