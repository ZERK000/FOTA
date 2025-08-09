/*
 * HSTP_Program.c
 *
 *  Created on: Aug 3, 2025
 *      Author: Catherine Nader
 */

#include "CommonMacros.h"
#include "MCAL/MSystick_Interface.h"
#include "HAL/HSTP_Config.h"
#include "HAL/HSTP_Interface.h"
#include "MCAL/MGPIO_Interface.h"


void HSTP_voidInit(void)
{

	GPIO_PinMode(STP_PORT,HSTP_u8_SDI_PIN,OUTPUT);
	GPIO_PinMode(STP_PORT,HSTP_u8_SHIFT_PIN,OUTPUT);
	GPIO_PinMode(STP_PORT,HSTP_u8_LATCH_PIN,OUTPUT);

	GPIO_OutputPinConfigure(STP_PORT,HSTP_u8_SDI_PIN,PUSH_PULL,LOW_SPEED);
	GPIO_OutputPinConfigure(STP_PORT,HSTP_u8_SHIFT_PIN,PUSH_PULL,LOW_SPEED);
	GPIO_OutputPinConfigure(STP_PORT,HSTP_u8_LATCH_PIN,PUSH_PULL,LOW_SPEED);
}

void HSTP_voidShiftData(u8 Copy_u8Data)
{

    for (s8 i = 7; i >= 0; i--)  // MSB first (change to i=0 to 7 for LSB first)
    {
        u8 bit = GET_BIT(Copy_u8Data, i);

        // Set the data pin (SDI)
        GPIO_SetPinValue(STP_PORT, HSTP_u8_SDI_PIN, bit);

        // Pulse the shift clock (SHCP)
        GPIO_SetPinValue(STP_PORT, HSTP_u8_SHIFT_PIN, HIGH);
        MSTK_voidDelayms(10);
        GPIO_SetPinValue(STP_PORT, HSTP_u8_SHIFT_PIN, LOW);

    }

	}
void HSTP_voidSendData(void)
{
	GPIO_SetPinValue(STP_PORT,HSTP_u8_LATCH_PIN,LOW);
		MSTK_voidDelayms(10);
		GPIO_SetPinValue(STP_PORT,HSTP_u8_LATCH_PIN,HIGH);

}
