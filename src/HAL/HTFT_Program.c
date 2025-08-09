/*
 * TFT_Program.c
 *
 *  Created on: Jul 30, 2025
 *      Author: Ziad
 */

#include "STD_TYPES.h"
#include "CommonMacros.h"
#include <MCAL/MGPIO_Interface.h>
#include <MCAL/MSPI_Interface.h>
#include <MCAL/MSystick_Interface.h>
#include <HAL/HTFT_Config.h>
#include <HAL/HTFT_Interface.h>



static u16 CurrentBackgroundColor = BLACK;

static void WriteCommand(u16 cmd)
{
	GPIO_SetPinValue(TFT_PORT, TFT_DC_PIN, LOW);
//	GPIO_SetPinValue(TFT_PORT, TFT_CS_PIN, LOW);
	(void)SPI_u16TransmitReceive(cmd);
//	GPIO_SetPinValue(TFT_PORT, TFT_CS_PIN, HIGH);

}

static void WriteData(u16 data)
{
	GPIO_SetPinValue(TFT_PORT, TFT_DC_PIN, HIGH);
//	GPIO_SetPinValue(TFT_PORT, TFT_CS_PIN, LOW);
	(void)SPI_u16TransmitReceive(data);
//	GPIO_SetPinValue(TFT_PORT, TFT_CS_PIN, HIGH);
}


void TFT_voidInit(void)
{
	// Set pins as output
	GPIO_PinMode(TFT_PORT, TFT_RST_PIN, OUTPUT);
	GPIO_OutputPinConfigure(TFT_PORT,TFT_RST_PIN, PUSH_PULL,LOW_SPEED);

	GPIO_PinMode(TFT_PORT, TFT_DC_PIN, OUTPUT);
	GPIO_OutputPinConfigure(TFT_PORT,TFT_DC_PIN, PUSH_PULL,LOW_SPEED);

	// Reset sequence
	GPIO_SetPinValue(TFT_PORT, TFT_RST_PIN, HIGH);
	MSTK_voidDelayus(100);
	GPIO_SetPinValue(TFT_PORT, TFT_RST_PIN, LOW);
	MSTK_voidDelayus(1);
	GPIO_SetPinValue(TFT_PORT, TFT_RST_PIN, HIGH);
	MSTK_voidDelayus(100);
	GPIO_SetPinValue(TFT_PORT, TFT_RST_PIN, LOW);
	MSTK_voidDelayus(100);
	GPIO_SetPinValue(TFT_PORT, TFT_RST_PIN, HIGH);
	MSTK_voidDelayms(120);

	// Send init commands
	WriteCommand(0x11); // Sleep out
	MSTK_voidDelayms(10);

	WriteCommand(0x3A); // Color mode
	WriteData(0x05);    // 16-bit color

	WriteCommand(0x29); // Display on
}

void TFT_voidSetBackgroundColor(u16 color)
{
	u8 high = color >> 8;
	u8 low = color & 0xFF;

	// Set drawing area (full screen)
	WriteCommand(0x2A); // Column addr set
	WriteData(0); WriteData(0);
	WriteData(0); WriteData(127);

	WriteCommand(0x2B); // Row addr set
	WriteData(0); WriteData(0);
	WriteData(0); WriteData(159);

	WriteCommand(0x2C); // Write to RAM

	for (u32 i = 0; i < 128 * 160; i++) {
		WriteData(high);
		WriteData(low);
	}

	CurrentBackgroundColor = color;
}

void TFT_voidDrawFilledRect(u8 x_start, u8 y_start, u8 width, u8 height, u16 color)
{
	u8 x_end = x_start + width - 1;
	u8 y_end = y_start + height - 1;

	// Set column address
	WriteCommand(0x2A);
	WriteData(0x00); WriteData(x_start);
	WriteData(0x00); WriteData(x_end);

	// Set row address
	WriteCommand(0x2B);
	WriteData(0x00); WriteData(y_start);
	WriteData(0x00); WriteData(y_end);

	// Start memory write
	WriteCommand(0x2C);

	u16 totalPixels = width * height;
	u8 high = color >> 8;
	u8 low  = color & 0xFF;

	for (u16 i = 0; i < totalPixels; i++)
	{
		WriteData(high);
		WriteData(low);
	}
}

void TFT_voidDrawHLine(u8 x, u8 y, u8 length, u16 color)
{
	for (u8 i = 0; i < length; i++)
	{
		TFT_voidDrawFilledRect(x + i, y, 1, 1, color);
	}
}
void TFT_voidDrawVLine(u8 x, u8 y, u8 length, u16 color)
{
	for (u8 i = 0; i < length; i++)
	{
		TFT_voidDrawFilledRect(x, y + i, 1, 1, color);
	}
}
void TFT_voidDrawRectangle(u8 x, u8 y, u8 width, u8 height, u16 color)
{
	TFT_voidDrawHLine(x, y, width, color);                      // Top
	TFT_voidDrawHLine(x, y + height - 1, width, color);         // Bottom
	TFT_voidDrawVLine(x, y, height, color);                     // Left
	TFT_voidDrawVLine(x + width - 1, y, height, color);         // Right
}


void TFT_voidDrawLoadingBar(u8 x, u8 y, u8 width, u8 height, u8 progress, u16 barColor, u16 bgColor, u16 borderColor)
{
	// Draw the border (optional)
	TFT_voidDrawRectangle(x, y, width, height, borderColor);

	// Calculate filled width
	u8 filledWidth = (progress * (width - 2)) / 100;  // -2 for inner area
	char buffer[5];  // Enough for 3 digits + null terminator

	sprintf(buffer, "%d%%", progress);  // Converts number to string
	// Clear the inside
	//    TFT_voidDrawFilledRect(x + 1, y + 1, width - 2, height - 2, bgColor);

	// Draw the progress fill
	TFT_voidDrawFilledRect(x + 1, y + 1, filledWidth, height - 2, barColor);
	TFT_voidPrintString(x+(width/2),y+(height/2)-3,buffer,WHITE,TFT_TEXT_NO_BG,CENTER_ALIGNED);
	if(progress == 100)
		TFT_voidPrintString(x+(width/2),y+12,"Download Complete!",WHITE,TFT_TEXT_NO_BG,CENTER_ALIGNED);
}

void TFT_voidDrawTriangle(u8 x, u8 y, u8 size, u16 color)
{
	u8 half = size / 2;
	for (u8 i = 0; i < size; i++)
	{
		// Draw horizontal lines to form the triangle (like filling from top to base)
		u8 startX = x - i;
		u8 endX = x + i;
		u8 currentY = y + i;
		if (startX < endX)
		{
			TFT_voidDrawHLine(startX, currentY, endX - startX + 1, color);
		}
	}
}

void TFT_voidShowWarning()
{
	// Standard parameters
	u8 x = 64;            // Center X (assuming 128 width screen)
	u8 y = 20;            // Top Y
	u8 size = 20;         // Height of triangle
	u8 times = 4;         // Number of blinks
	u16 color = YELLOW;   // Triangle color
	u16 bgColor = BLACK;  // Background color
	u16 textColor = YELLOW;

	for (u8 i = 0; i < times; i++)
	{
		TFT_voidDrawTriangle(x, y, size, color);
		// Optional: draw '!' in the center
		TFT_voidPrintChar(x -3, y + size / 2, '!', BLACK, YELLOW);
		MSTK_voidDelayms(300);

		TFT_voidDrawTriangle(x, y, size, bgColor);
		MSTK_voidDelayms(300);
	}

	// Leave triangle visible
	TFT_voidDrawTriangle(x, y, size, color);
	TFT_voidPrintChar(x - 3, y + size / 2, '!', BLACK, YELLOW);



	// Optional: show "WARNING" label below
	TFT_voidPrintString(x, y + size + 5, "WARNING", textColor, bgColor, CENTER_ALIGNED);
}


u8 ReverseBits(u8 b) {
	u8 r = 0;
	for (u8 i = 0; i < 7; i++) {
		r <<= 1;
		r |= (b & 1);
		b >>= 1;
	}
	return r;

}

void TFT_voidPrintChar(u8 x, u8 y, char c, u16 color, u16 bgColor)
{
	if (c < 32 || c > 126) return; // font supports only 32 to 126

	const u8* CharData = &Font5x7[(c - 32) * 5];

	for (u8 col = 0; col < 5; col++) {
		//		u8 line = ReverseBits(charData[col]);
		u8 line = CharData[col];

		for (u8 row = 0; row < 7; row++) {
			u16 pixelColor;
			if (bgColor == TFT_TEXT_NO_BG)
				pixelColor = (line & (1 << row)) ? color : CurrentBackgroundColor;
			else
				pixelColor = (line & (1 << row)) ? color : bgColor;
			TFT_voidDrawFilledRect(x + col, y + row, 1, 1, pixelColor);
		}
	}

	//	 1-pixel space between characters
	for (u8 row = 0; row < 7; row++) {
		if (bgColor == TFT_TEXT_NO_BG)
			TFT_voidDrawFilledRect(x + 5, y + row, 1, 1, CurrentBackgroundColor);
		else
			TFT_voidDrawFilledRect(x + 5, y + row, 1, 1, bgColor);
	}
}


void TFT_voidPrintString(u8 x, u8 y, const char* str, u16 color, u16 bgColor, u8 alignment)
{
	u8 X,Yy;
	u8 length = strlen(str);
	u8 strPixelWidth = length * 6; // 5 pixels per char + 1 spacing

	if(strPixelWidth > X_MAX)
		return;

	if((y <= Y_MAX) && (y> (Y_MAX-7)) )
	{
		Yy = Y_MAX - 7;
	}
	else Yy = y;
	switch (alignment)
	{
	case CENTER_ALIGNED:
		X = (x > strPixelWidth / 2) ? x - (strPixelWidth / 2) : 0;
		break;
	case RIGHT_ALIGNED:
		X = (x > strPixelWidth) ? x - strPixelWidth : 0;
		break;
	default:
		X = x;
		break;
	}

	while (*str)
	{
		TFT_voidPrintChar(X, Yy, *str, color, bgColor);
		str++;
		X += 6; // Move to the next character position (5 pixels for the character + 1 for spacing)
	}
}







void TFT_DisplayImage(const u16*Image)
{
	u16 i;
	u8 HighPart,LowPart;
	//Set x
	WriteCommand(0x2A);
	WriteData(0);
	WriteData(0);
	WriteData(0);
	WriteData(127);
	//Set Y
	WriteCommand(0x2B);
	WriteData(0);
	WriteData(0);
	WriteData(0);
	WriteData(159);

	//Write on screen
	WriteCommand(0x2C);
	for(i=0;i<20480;i++)
	{
		LowPart=(u8)Image[i];
		HighPart=(u8)(Image[i]>>8);
		WriteData(HighPart);
		WriteData(LowPart);
	}
}
void Animate_Text_Scroll()
{
	u8 x = 0;
	const char* str = "Hello";

	while (1)
	{
		// Clear previous position
		TFT_voidPrintString(x, 20, str, CurrentBackgroundColor, CurrentBackgroundColor, LEFT_ALIGNED);

		// Update position
		x++;
		if (x > X_MAX) x = 0;

		// Draw new position
		TFT_voidPrintString(x, 20, str, RED, CurrentBackgroundColor, LEFT_ALIGNED);

		MSTK_voidDelayus(1);
	}
}


///// Menus

#define MENU_TITLE_Y       5
#define MENU_ITEM_START_Y  20
#define MENU_ITEM_SPACING  12  // pixels between each item
#define SELECTOR_COLOR     YELLOW
#define ITEM_COLOR          WHITE
#define ITEM_BG_COLOR       BLACK
#define SELECTED_ITEM_BG    DARKGREY


void TFT_DrawMenu(const u8* title, const u8* items[], u8 numItems, u8 selectedIndex)
{
    // 1. Clear the screen
    TFT_voidSetBackgroundColor(BLACK);

    // 2. Draw the title centered at the top
    TFT_voidPrintString(X_MAX/2, MENU_TITLE_Y, title, ITEM_COLOR, TFT_TEXT_NO_BG, CENTER_ALIGNED);

    // 3. Draw menu items with selector
    for (u8 i = 0; i < numItems; i++)
    {
        u8 y = MENU_ITEM_START_Y + (i * MENU_ITEM_SPACING);

        if (i == selectedIndex)
        {
            // Draw highlight background for selected item
            TFT_voidDrawFilledRect(0, y - 1, X_MAX, 10, SELECTED_ITEM_BG);
            // Draw selector arrow  at left
            TFT_voidPrintString(2, y, "-> ", SELECTOR_COLOR, SELECTED_ITEM_BG, LEFT_ALIGNED);
            // Print item text next to it
            TFT_voidPrintString(12, y, items[i], ITEM_COLOR, SELECTED_ITEM_BG, LEFT_ALIGNED);
        }
        else
        {
            // Draw item text without selector
            TFT_voidPrintString(12, y, items[i], ITEM_COLOR, TFT_TEXT_NO_BG, LEFT_ALIGNED);
        }
    }
}












const  u8 Font5x7[]  =
{
		0x00, 0x00, 0x00, 0x00, 0x00,// (space)
		0x00, 0x00, 0x5F, 0x00, 0x00,// !
		0x00, 0x07, 0x00, 0x07, 0x00,// "
		0x14, 0x7F, 0x14, 0x7F, 0x14,// #
		0x24, 0x2A, 0x7F, 0x2A, 0x12,// $
		0x23, 0x13, 0x08, 0x64, 0x62,// %
		0x36, 0x49, 0x55, 0x22, 0x50,// &
		0x00, 0x05, 0x03, 0x00, 0x00,// '
		0x00, 0x1C, 0x22, 0x41, 0x00,// (
		0x00, 0x41, 0x22, 0x1C, 0x00,// )
		0x08, 0x2A, 0x1C, 0x2A, 0x08,// *
		0x08, 0x08, 0x3E, 0x08, 0x08,// +
		0x00, 0x50, 0x30, 0x00, 0x00,// ,
		0x08, 0x08, 0x08, 0x08, 0x08,// -
		0x00, 0x60, 0x60, 0x00, 0x00,// .
		0x20, 0x10, 0x08, 0x04, 0x02,// /
		0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
		0x00, 0x42, 0x7F, 0x40, 0x00,// 1
		0x42, 0x61, 0x51, 0x49, 0x46,// 2
		0x21, 0x41, 0x45, 0x4B, 0x31,// 3
		0x18, 0x14, 0x12, 0x7F, 0x10,// 4
		0x27, 0x45, 0x45, 0x45, 0x39,// 5
		0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
		0x01, 0x71, 0x09, 0x05, 0x03,// 7
		0x36, 0x49, 0x49, 0x49, 0x36,// 8
		0x06, 0x49, 0x49, 0x29, 0x1E,// 9
		0x00, 0x36, 0x36, 0x00, 0x00,// :
		0x00, 0x56, 0x36, 0x00, 0x00,// ;
		0x00, 0x08, 0x14, 0x22, 0x41,// <
		0x14, 0x14, 0x14, 0x14, 0x14,// =
		0x41, 0x22, 0x14, 0x08, 0x00,// >
		0x02, 0x01, 0x51, 0x09, 0x06,// ?
		0x32, 0x49, 0x79, 0x41, 0x3E,// @
		0x7E, 0x11, 0x11, 0x11, 0x7E,// A
		0x7F, 0x49, 0x49, 0x49, 0x36,// B
		0x3E, 0x41, 0x41, 0x41, 0x22,// C
		0x7F, 0x41, 0x41, 0x22, 0x1C,// D
		0x7F, 0x49, 0x49, 0x49, 0x41,// E
		0x7F, 0x09, 0x09, 0x01, 0x01,// F
		0x3E, 0x41, 0x41, 0x51, 0x32,// G
		0x7F, 0x08, 0x08, 0x08, 0x7F,// H
		0x00, 0x41, 0x7F, 0x41, 0x00,// I
		0x20, 0x40, 0x41, 0x3F, 0x01,// J
		0x7F, 0x08, 0x14, 0x22, 0x41,// K
		0x7F, 0x40, 0x40, 0x40, 0x40,// L
		0x7F, 0x02, 0x04, 0x02, 0x7F,// M
		0x7F, 0x04, 0x08, 0x10, 0x7F,// N
		0x3E, 0x41, 0x41, 0x41, 0x3E,// O
		0x7F, 0x09, 0x09, 0x09, 0x06,// P
		0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
		0x7F, 0x09, 0x19, 0x29, 0x46,// R
		0x46, 0x49, 0x49, 0x49, 0x31,// S
		0x01, 0x01, 0x7F, 0x01, 0x01,// T
		0x3F, 0x40, 0x40, 0x40, 0x3F,// U
		0x1F, 0x20, 0x40, 0x20, 0x1F,// V
		0x7F, 0x20, 0x18, 0x20, 0x7F,// W
		0x63, 0x14, 0x08, 0x14, 0x63,// X
		0x03, 0x04, 0x78, 0x04, 0x03,// Y
		0x61, 0x51, 0x49, 0x45, 0x43,// Z
		0x00, 0x00, 0x7F, 0x41, 0x41,// [
		0x02, 0x04, 0x08, 0x10, 0x20,// "\"
		0x41, 0x41, 0x7F, 0x00, 0x00,// ]
		0x04, 0x02, 0x01, 0x02, 0x04,// ^
		0x40, 0x40, 0x40, 0x40, 0x40,// _
		0x00, 0x01, 0x02, 0x04, 0x00,// `
		0x20, 0x54, 0x54, 0x54, 0x78,// a
		0x7F, 0x48, 0x44, 0x44, 0x38,// b
		0x38, 0x44, 0x44, 0x44, 0x20,// c
		0x38, 0x44, 0x44, 0x48, 0x7F,// d
		0x38, 0x54, 0x54, 0x54, 0x18,// e
		0x08, 0x7E, 0x09, 0x01, 0x02,// f
		0x08, 0x14, 0x54, 0x54, 0x3C,// g
		0x7F, 0x08, 0x04, 0x04, 0x78,// h
		0x00, 0x44, 0x7D, 0x40, 0x00,// i
		0x20, 0x40, 0x44, 0x3D, 0x00,// j
		0x00, 0x7F, 0x10, 0x28, 0x44,// k
		0x00, 0x41, 0x7F, 0x40, 0x00,// l
		0x7C, 0x04, 0x18, 0x04, 0x78,// m
		0x7C, 0x08, 0x04, 0x04, 0x78,// n
		0x38, 0x44, 0x44, 0x44, 0x38,// o
		0x7C, 0x14, 0x14, 0x14, 0x08,// p
		0x08, 0x14, 0x14, 0x18, 0x7C,// q
		0x7C, 0x08, 0x04, 0x04, 0x08,// r
		0x48, 0x54, 0x54, 0x54, 0x20,// s
		0x04, 0x3F, 0x44, 0x40, 0x20,// t
		0x3C, 0x40, 0x40, 0x20, 0x7C,// u
		0x1C, 0x20, 0x40, 0x20, 0x1C,// v
		0x3C, 0x40, 0x30, 0x40, 0x3C,// w
		0x44, 0x28, 0x10, 0x28, 0x44,// x
		0x0C, 0x50, 0x50, 0x50, 0x3C,// y
		0x44, 0x64, 0x54, 0x4C, 0x44,// z
		0x00, 0x08, 0x36, 0x41, 0x00,// {
		0x00, 0x00, 0x7F, 0x00, 0x00,// |
		0x00, 0x41, 0x36, 0x08, 0x00,// }
		0x08, 0x08, 0x2A, 0x1C, 0x08,// ->
		0x08, 0x1C, 0x2A, 0x08, 0x08 // <-
};


