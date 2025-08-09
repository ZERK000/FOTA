/*
 * main.c
 *
 *  Created on: Aug 5, 2025
 *      Author: Catherine Nader
 */
#include "STD_TYPES.h"
#include "CommonMacros.h"
#include "string.h"
#include "MCAL/MRCC_Interface.h"
#include "MCAL/MGPIO_Interface.h"
#include "MCAL/MNVIC_Interface.h"
#include "MCAL/MSystick_Interface.h"
#include "MCAL/MEXTI_Interface.h"
#include "MCAL/MTIMER_Interface.h"
#include "MCAL/MUART_Interface.h"
#include "MCAL/MSPI_Interface.h"
#include "MCAL/MHexParser.h"
#include "MCAL/MFLASH_Interface.h"

#include "HAL/HIR_Interface.h"
#include "HAL/HLEDMatrix_Interface.h"
#include "HAL/HSevenSegment_Interface.h"
#include "HAL/HSTP_Interface.h"
#include "HAL/HTFT_Interface.h"
#include "stdbool.h"


#define TX_PIN       		9
#define RX_PIN       		10


#define MAX_LINE_LENGTH 	128
#define MAX_HEX_LINES 		1000

#define NEXT_BUTTON			1
#define SELECT_BUTTON		2
#define PREVIOUS_BUTTON		3

#define BUZZER_PIN			0


///////////////////////////////// BOOT AND UPDATE VARIABLES ///////////////////////////////////////////
u8 ReceivedBuffer[MAX_LINE_LENGTH];
u8 PreviousBuffer[MAX_LINE_LENGTH];
volatile u8 RxIndex = 0;
volatile bool LineComplete = false;
HexRecord_t LineBytes = {0};

HexRecord_t HexRecords[MAX_HEX_LINES] = {0};
u16 HexRecordsIndex = 0;
u16 TotalLines = 0;
bool UpdateAvailable = false;
//////////////////////////////////////////////////////////////////////////////////////////////////////


u8 NEC_State = 0;

////////////////////////////////// GUI Related ////////////////////////////////////////
AppState_t CurrentState = STATE_MAIN_MENU;
u8 MainMenuCursor = 0;
u8 AppMenuCursor = 0;
u8 CountersMenuCursor = 0;
u8 LedMatrixMenuCursor = 0;
u8 BuzzerCursor = 0;
u8 NavigateFlag =0;

void InitializeUART();
void InitializeClock();
void InitializeInterrupts();

void App_Update(void);
void HandleMainMenu(void);
void HandleAppMenu(void);
void HandleUpdateMenu(void);
void HandleExitMenu(void);
void HandleCountersMenu(void);
void HandleLEDMatrixMenu(void);
void HandleBuzzerMenu(void);

void CountUp();
void CountDown();
void CountUpDown();

void LEDMatrix_DrawSadFace();
void LEDMatrix_DrawSmileyFace();
void LEDMatrix_DrawTriangle();
void LEDMatrix_DrawCircle();


void ProcessReceivedLine(void);
void NavigateDownward();
void NavigateUpward();
void SelectItem();

int main(void) {
	// Setting Clock
	InitializeClock();

	GPIO_PinMode(PORTB,0,OUTPUT);
	GPIO_OutputPinConfigure(PORTB,0,PUSH_PULL,HIGH_SPEED);

	__asm volatile ("cpsid i");

	// Setting USART
	InitializeUART();

	// Setting Interrupts
	InitializeInterrupts();

	SPI_voidInit();
	MSTK_voidInit();
	TFT_voidInit();
	HSTP_voidInit();
	//


	TFT_voidSetBackgroundColor(BLACK);


	//	for (u8 i = 0; i <= 100; i++)
	//	{
	//		TFT_voidDrawLoadingBar(24, 79, 80, 10, i, GREEN, BLACK, WHITE);
	//		MSTK_voidDelayms(30);
	//	}

	//	TFT_voidShowWarning();
	__asm volatile ("cpsie i");
	App_Update();
	while (1)
	{

		if(NavigateFlag == 1)
		{
			App_Update();
			NavigateFlag =0;
		}

	}
}

void App_Update(void)
{
	switch (CurrentState)
	{
	case STATE_MAIN_MENU:
		HandleMainMenu();
		break;

	case STATE_APP_MENU:
		HandleAppMenu();
		break;

	case STATE_UPDATE:
		HandleUpdateMenu();
		break;

	case STATE_COUNTER_MENU:
		HandleCountersMenu();
		break;

	case STATE_LED_MATRIX_MENU:
		HandleLEDMatrixMenu();
		break;

	case STATE_BUZZER:
		HandleBuzzerMenu();
		break;

		// Add the rest later...
	default:
		break;
	}
}


void HandleMainMenu(void)
{
	const u8* MainMenu[] = {"Application", "Update", "Exit"};

	// Draw the menu
	TFT_DrawMenu((const u8*)"Main Menu", MainMenu, sizeof(MainMenu)/sizeof(MainMenu[0]), MainMenuCursor);

}

void HandleAppMenu(void)
{
	const u8* AppMenu[] = {"Counters", "LED Matrix","Buzzer", "Back"};

	TFT_DrawMenu((const u8*)"App Menu", AppMenu, sizeof(AppMenu)/sizeof(AppMenu[0]), AppMenuCursor);


}

void HandleCountersMenu(void)
{
	const u8* CountersMenu[] = {"Count Up", "Count Down", "Count Up & Down", "Back"};

	TFT_DrawMenu((const u8*)"Counters", CountersMenu, sizeof(CountersMenu)/sizeof(CountersMenu[0]), CountersMenuCursor);
}
void HandleLEDMatrixMenu(void)
{
	const u8* LEDMatrixMenu[] = {"Smiley Face", "Sad Face", "Triangle", "Circle", "Back"};

	TFT_DrawMenu((const u8*)"LED Matrix", LEDMatrixMenu, sizeof(LEDMatrixMenu)/sizeof(LEDMatrixMenu[0]), LedMatrixMenuCursor);
}

void HandleBuzzerMenu(void)
{
	const u8* BuzzerMenu[] = {"ON", "OFF", "Done", "Back"};

	TFT_DrawMenu((const u8*)"Buzzer", BuzzerMenu, sizeof(BuzzerMenu)/sizeof(BuzzerMenu[0]), BuzzerCursor);
}

void HandleUpdateMenu(void)
{
	if(TotalLines == 0)
	{
		TFT_voidPrintString(X_MIDDLE,Y_MIDDLE,"No Update Available",YELLOW,TFT_TEXT_NO_BG, CENTER_ALIGNED);
		MSTK_voidDelayms(2000);
		TFT_voidPrintString(X_MIDDLE,Y_MIDDLE,"No Update Available",BLACK,TFT_TEXT_NO_BG, CENTER_ALIGNED);
	}
	else{

		TFT_voidPrintString(X_MIDDLE,Y_MIDDLE,"Update Available!",YELLOW,TFT_TEXT_NO_BG, CENTER_ALIGNED);
		MSTK_voidDelayms(2000);
		TFT_voidPrintString(X_MIDDLE,Y_MIDDLE,"Update Available!",BLACK,TFT_TEXT_NO_BG, CENTER_ALIGNED);

	}
	// Go to BOOT
	CurrentState = STATE_MAIN_MENU;
	NavigateFlag = 1;
}

void HandleExitMenu(void)
{
	TFT_voidSetBackgroundColor(BLACK);
	TFT_voidPrintString(X_MIDDLE, Y_MIDDLE,"GoodBye!",GREEN,TFT_TEXT_NO_BG,CENTER_ALIGNED);
	MSTK_voidDelayms(2000);

}




void USART1_IRQHandler() {
	u8 rec = UART_u8Receive();

	if (!LineComplete) {
		if (rec == '\n') {
			ReceivedBuffer[RxIndex] = '\0'; // null-terminate the string
			RxIndex = 0;
			LineComplete = true;
		} else if (RxIndex < MAX_LINE_LENGTH - 1) {
			ReceivedBuffer[RxIndex++] = rec;
		} else {
			// Buffer overflow; discard
			RxIndex = 0;
		}

	}

	if (LineComplete) {
		ProcessReceivedLine();
	}

}
void USART2_IRQHandler() {
	u8 rec = UART_u8Receive();
	NEC_State = rec;
	switch(NEC_State)
	{
	case 'A':
		CurrentState = STATE_MAIN_MENU;
		break;
	case 'B':
		CurrentState = STATE_APP_MENU;
		break;
	case 'C':
		CurrentState = STATE_COUNTER_MENU;
		break;
	default:
		break;
	}

}


void ProcessReceivedLine(void) {
	LineComplete = false;

	// Ignore repeated line
	if (memcmp(ReceivedBuffer, PreviousBuffer, MAX_LINE_LENGTH) == 0)
	{
		UART_voidSend('A'); // Already received
		return;
	}

	memcpy(PreviousBuffer, ReceivedBuffer, MAX_LINE_LENGTH);

	if (!HEXParser_ParseAndVerify(ReceivedBuffer ,&LineBytes)) {

		// Store it if there's still space
		if (HexRecordsIndex < MAX_HEX_LINES) {
			HexRecords[HexRecordsIndex++] = LineBytes;
		}

		if (LineBytes.RecordType == 0x01) {
			// End Of File
			TotalLines = HexRecordsIndex;
			HexRecordsIndex = 0;
			UpdateAvailable = true;
		}
		UART_voidSend('A');
	} else {
		UART_voidSend('N');
	}
}


void NavigateDownward()
{
	switch (CurrentState)
	{
	case STATE_MAIN_MENU:
		MainMenuCursor = (MainMenuCursor + 1) % 3;  // avoid negative with +2 mod 3
		break;
	case STATE_APP_MENU:
		AppMenuCursor = (AppMenuCursor + 1) % 4;  // adjust if more items later
		break;
	case STATE_COUNTER_MENU:
		CountersMenuCursor = (CountersMenuCursor + 1) % 4;  // adjust if more items later
		break;
	case STATE_LED_MATRIX_MENU:
		LedMatrixMenuCursor = (LedMatrixMenuCursor + 1) % 5;  // adjust if more items later
		break;
	case STATE_BUZZER:
		BuzzerCursor = (BuzzerCursor + 1) % 4;  // adjust if more items later
		break;
		// Add others
	}
	NavigateFlag = 1;
}
void NavigateUpward()
{
	switch (CurrentState)
	{
	case STATE_MAIN_MENU:
		MainMenuCursor = (MainMenuCursor + 2) % 3;  // avoid negative with +2 mod 3
		break;
	case STATE_APP_MENU:
		AppMenuCursor = (AppMenuCursor + 3) % 4;  // adjust if more items later
		break;
		// Add others
	case STATE_COUNTER_MENU:
		CountersMenuCursor = (CountersMenuCursor + 3) % 4;  // avoid negative with +2 mod 3
		break;
	case STATE_LED_MATRIX_MENU:
		LedMatrixMenuCursor = (LedMatrixMenuCursor+ 4) % 5;  // adjust if more items later
		break;

	case STATE_BUZZER:
		BuzzerCursor = (BuzzerCursor + 3) % 4;  // adjust if more items later
		break;
		// Add others
	}
	NavigateFlag = 1;
}
void SelectItem()
{

	switch (CurrentState)
	{
	case STATE_MAIN_MENU:
		if (MainMenuCursor == 0)
			CurrentState = STATE_APP_MENU;
		else if (MainMenuCursor == 1)
			CurrentState = STATE_UPDATE;
		else if (MainMenuCursor == 2)
			CurrentState = STATE_EXIT;
		break;

	case STATE_APP_MENU:
		if (AppMenuCursor == 0)
			CurrentState = STATE_COUNTER_MENU;
		else if (AppMenuCursor == 1)
			CurrentState = STATE_LED_MATRIX_MENU;
		else if (AppMenuCursor == 2)
			CurrentState = STATE_BUZZER;
		else if (AppMenuCursor == 3)
			CurrentState = STATE_MAIN_MENU;
		break;

	case STATE_COUNTER_MENU:
		if (CountersMenuCursor == 0)
			CountUp();
		else if (CountersMenuCursor == 1)
			CountDown();
		else if (CountersMenuCursor == 2)
			CountUpDown();
		else if (CountersMenuCursor == 3)
			CurrentState = STATE_APP_MENU;
		break;

	case STATE_LED_MATRIX_MENU:
		if (LedMatrixMenuCursor == 0)
			LEDMatrix_DrawSmileyFace();
		else if (LedMatrixMenuCursor == 1)
			LEDMatrix_DrawSadFace();
		else if (LedMatrixMenuCursor == 2)
			LEDMatrix_DrawTriangle();
		else if (LedMatrixMenuCursor == 3)
			LEDMatrix_DrawCircle();
		else if (LedMatrixMenuCursor == 4)
			CurrentState = STATE_APP_MENU;
		break;

	case STATE_BUZZER:
		if(BuzzerCursor == 0)
		{
			GPIO_SetPinValue(PORTB,0,HIGH);
		}
		else if (BuzzerCursor == 1)
		{
			GPIO_SetPinValue(PORTB,0,LOW);
		}
		else if (BuzzerCursor == 2)
		{
			CurrentState = STATE_MAIN_MENU;
		}
		else if (BuzzerCursor == 3)
		{
			CurrentState = STATE_APP_MENU;
		}

		// More cases...
	}
	NavigateFlag = 1;
}

void CountUp()
{
	TFT_voidPrintString(X_MIDDLE,Y_MIDDLE,"Counting up",RED,TFT_TEXT_NO_BG,CENTER_ALIGNED);
	SEGMENT_voidCountUp();
	CurrentState = STATE_MAIN_MENU;
	NavigateFlag = 1;
}
void CountDown()
{
	TFT_voidPrintString(X_MIDDLE,Y_MIDDLE,"Counting down",RED,TFT_TEXT_NO_BG,CENTER_ALIGNED);
	SEGMENT_voidCountDown();
	CurrentState = STATE_MAIN_MENU;
	NavigateFlag = 1;
}
void CountUpDown()
{
	TFT_voidPrintString(X_MIDDLE,Y_MIDDLE,"Counting up and down",RED,TFT_TEXT_NO_BG,CENTER_ALIGNED);
	SEGMENT_voidCountUpDown();
	CurrentState = STATE_MAIN_MENU;
	NavigateFlag = 1;
}

void LEDMatrix_DrawSmileyFace()
{
	TFT_voidPrintString(X_MIDDLE,Y_MIDDLE,"Drawing Smiley Face",RED,TFT_TEXT_NO_BG,CENTER_ALIGNED);
	Display_HappyFace();
	MSTK_voidDelayms(1000);
	CurrentState = STATE_MAIN_MENU;
	NavigateFlag = 1;
}
void LEDMatrix_DrawSadFace()
{
	TFT_voidPrintString(X_MIDDLE,Y_MIDDLE,"Drawing Sad Face",RED,TFT_TEXT_NO_BG,CENTER_ALIGNED);
	Display_SadFace();
	MSTK_voidDelayms(1000);
	CurrentState = STATE_MAIN_MENU;
	NavigateFlag = 1;
}
void LEDMatrix_DrawTriangle()
{
	TFT_voidPrintString(X_MIDDLE,Y_MIDDLE,"Drawing Triangle",RED,TFT_TEXT_NO_BG,CENTER_ALIGNED);
	Display_Triangle();
	MSTK_voidDelayms(1000);
	CurrentState = STATE_MAIN_MENU;
	NavigateFlag = 1;
}
void LEDMatrix_DrawCircle()
{
	TFT_voidPrintString(X_MIDDLE,Y_MIDDLE,"Drawing Circle",RED,TFT_TEXT_NO_BG,CENTER_ALIGNED);
	Display_Circle();
	MSTK_voidDelayms(1000);
	CurrentState = STATE_MAIN_MENU;
	NavigateFlag = 1;
}


void InitializeUART()
{
	GPIO_PinMode(PORTA, TX_PIN, ALT_FUNCTION);
	GPIO_SetAlternativeConfiguration(PORTA, TX_PIN, AF7);  // TX
	GPIO_PinMode(PORTA, RX_PIN, ALT_FUNCTION);
	GPIO_SetAlternativeConfiguration(PORTA, RX_PIN, AF7); // RX
	GPIO_InputPinConfigure(PORTA,TX_PIN,PULL_UP);
	GPIO_InputPinConfigure(PORTA,RX_PIN,PULL_UP);
	UART_voidInit();
	MNVIC_voidEnable(USART1_IRQn);

	GPIO_PinMode(PORTA, 2, ALT_FUNCTION);
	GPIO_SetAlternativeConfiguration(PORTA, 2, AF7);  // TX
	GPIO_PinMode(PORTA, 3, ALT_FUNCTION);
	GPIO_SetAlternativeConfiguration(PORTA, 3, AF7); // RX
	GPIO_InputPinConfigure(PORTA,2,PULL_UP);
	GPIO_InputPinConfigure(PORTA,3,PULL_UP);
	UART_voidInit();
	MNVIC_voidEnable(USART2_IRQn);
}

void InitializeClock()
{
	RCC_SetClock(HSI_ON, ENABLE);
	RCC_EnablePeripheralClock(AHB1, RCC_AHB1_GPIOA);
	RCC_EnablePeripheralClock(AHB1, RCC_AHB1_GPIOB);
	RCC_EnablePeripheralClock(AHB1, RCC_AHB1_GPIOC);
	RCC_EnablePeripheralClock(APB2, RCC_APB2_USART1);
	RCC_EnablePeripheralClock(APB2, RCC_APB2_SPI1);
	RCC_EnablePeripheralClock(APB2, RCC_SYSCFG);
}


void InitializeInterrupts()
{
	GPIO_PinMode(PORTA, NEXT_BUTTON, INPUT);
	GPIO_InputPinConfigure(PORTA,NEXT_BUTTON,PULL_UP);
	EXTI_voidSetInterruptPort(EXTI_lINE1, EXTI_PORT_A);
	EXTI_voidEnable(EXTI_lINE1);
	EXTI_voidSetTrigger(EXTI_lINE1, EXTI_RISING);
	MNVIC_voidEnable(EXTI1_IRQn);


	GPIO_PinMode(PORTB, SELECT_BUTTON, INPUT);
	GPIO_InputPinConfigure(PORTB,SELECT_BUTTON,PULL_UP);
	EXTI_voidSetInterruptPort(EXTI_lINE2, EXTI_PORT_B);
	EXTI_voidEnable(EXTI_lINE2);
	EXTI_voidSetTrigger(EXTI_lINE2, EXTI_RISING);
	MNVIC_voidEnable(EXTI2_IRQn);


	GPIO_PinMode(PORTB, PREVIOUS_BUTTON, INPUT);
	GPIO_InputPinConfigure(PORTB,PREVIOUS_BUTTON,PULL_UP);
	EXTI_voidSetInterruptPort(EXTI_lINE3, EXTI_PORT_B);
	EXTI_voidEnable(EXTI_lINE3);
	EXTI_voidSetTrigger(EXTI_lINE3, EXTI_RISING);
	MNVIC_voidEnable(EXTI3_IRQn);


	EXTI1_voidCallBack(NavigateDownward);
	EXTI2_voidCallBack(SelectItem);
	EXTI3_voidCallBack(NavigateUpward);
}
