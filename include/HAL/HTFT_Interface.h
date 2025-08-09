/*
 * TFT_Interface.h
 *
 *  Created on: Jul 30, 2025
 *      Author: Ziad
 */

#ifndef TFT_INTERFACE_H_
#define TFT_INTERFACE_H_

// Screen Positions

#define X_MIDDLE	63
#define Y_MIDDLE	79
#define X_MAX		127
#define Y_MAX		159

// RGB565 Color Macros
#define BLACK     			0x0000
#define WHITE     			0xFFFF
#define RED       			0xF800
#define GREEN     			0x07E0
#define BLUE      			0x001F
#define YELLOW    			0xFFE0
#define CYAN      			0x07FF
#define MAGENTA   			0xF81F
#define ORANGE    			0xFD20
#define GRAY      			0x8410
#define BROWN     			0xA145
#define PINK      			0xF81F
#define DARKGREY 			0x7BEF



// Text-Related Macros
#define TFT_TEXT_NO_BG		0xABAB
#define LEFT_ALIGNED		0
#define RIGHT_ALIGNED		1
#define CENTER_ALIGNED		2



extern const u8 Font5x7[];

typedef enum {
	STATE_MAIN_MENU,
	STATE_APP_MENU,
	STATE_UPDATE,
	STATE_EXIT,
	STATE_COUNTER_MENU,
	STATE_LED_MATRIX_MENU,
	STATE_BUZZER
}AppState_t;


void TFT_voidInit(void);
void TFT_voidSetBackgroundColor(u16 color);

void TFT_voidDrawHLine(u8 x, u8 y, u8 length, u16 color);
void TFT_voidDrawVLine(u8 x, u8 y, u8 length, u16 color);
void TFT_voidDrawRectangle(u8 x, u8 y, u8 width, u8 height, u16 color);
void TFT_voidDrawFilledRect(u8 x_start, u8 y_start, u8 width, u8 height, u16 color);

void TFT_voidShowWarning();
void TFT_voidDrawTriangle(u8 x, u8 y, u8 size, u16 color);

void TFT_voidPrintChar(u8 x, u8 y, char c, u16 color, u16 bgColor);
u8 ReverseBits(u8 b);
void TFT_voidPrintString(u8 x, u8 y, const char* str, u16 color, u16 bgColor, u8 alignment);
void TFT_DisplayImage(const u16*Image);

void TFT_voidDrawLoadingBar(u8 x, u8 y, u8 width, u8 height, u8 progress, u16 barColor, u16 bgColor, u16 borderColor);
void Animate_Text_Scroll();
void TFT_DrawMenu(const u8* title, const u8* items[], u8 numItems, u8 selectedIndex);

#endif /* TFT_INTERFACE_H_ */
