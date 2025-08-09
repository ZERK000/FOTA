/*
 * SevenSegment.h
 *
 *  Created on: Jul 16, 2025
 *      Author: Ziad
 */

#ifndef SEVENSEGMENT_H_
#define SEVENSEGMENT_H_

#include "STD_TYPES.h"
#include "MCAL/MGPIO_Interface.h"


// Array of segments for digits 0–9 (common cathode logic)
static const u8 segment_map[11] = {
		0b00111111, // 0
		0b00000110, // 1
		0b01011011, // 2
		0b01001111, // 3
		0b01100110, // 4
		0b01101101, // 5
		0b01111101, // 6
		0b00000111, // 7
		0b01111111, // 8
		0b01101111,  // 9
		0b00000000	// OFF
};


// Displays a digit (0–9)
void SEGMENT_voidDisplayDigit(u8 Digit);

void SEGMENT_voidCountUp(void);
void SEGMENT_voidCountDown(void);
void SEGMENT_voidCountUpDown(void);

void SEGMENT_voidCloseAllSegments();



#endif /* SEVENSEGMENT_H_ */
