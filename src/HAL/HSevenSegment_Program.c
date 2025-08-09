/*
 * SevenSegment.c
 *
 *  Created on: Jul 16, 2025
 *      Author: Ziad
 */

#include "MCAL/MSystick_Interface.h"
#include "HAL/HSTP_Interface.h"
#include <HAL/HSevenSegment_Interface.h>

#define DELAY_MS 500  // Delay between digit changes

void SEGMENT_voidDisplayDigit(u8 Digit)
{
	if (Digit > 10) return;


	HSTP_voidShiftData(segment_map[Digit]);
	HSTP_voidSendData();
}


void SEGMENT_voidCountUp(void)
{
    for(u8 digit = 0; digit <= 9; digit++)
    {
    	SEGMENT_voidDisplayDigit(digit);
        MSTK_voidDelayms(DELAY_MS);
    }
    SEGMENT_voidCloseAllSegments();
}

void SEGMENT_voidCountDown(void)
{
    for(u8 digit = 9; digit != 255; digit--)  // Underflow will exit loop
    {
    	SEGMENT_voidDisplayDigit(digit);
        MSTK_voidDelayms(DELAY_MS);
    }
    SEGMENT_voidCloseAllSegments();
}

void SEGMENT_voidCountUpDown(void)
{
	SEGMENT_voidCountUp();
	SEGMENT_voidCountDown();
	SEGMENT_voidCloseAllSegments();
}

void SEGMENT_voidCloseAllSegments()
{
	SEGMENT_voidDisplayDigit(10);
}

