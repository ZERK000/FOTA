//#include "STD_TYPES.h"
//#include "BIT_MATH.h"
//
//#include <MRCC_Interface.h>
//#include <MGPIO_Interface.h>
//#include <MSTK_Interface.h>
//#include <MNVIC_Interface.h>
//#include <MINT_Interface.h>
//#include <MUART_Interface.h>
//#include "HSevenSegment_Interface.h"
//
//// === Globals ===
//void Func1(void);
//void Func2(void);
//
//u8 GLB_u8StartFlag = 0;
//volatile u8 GLB_u8Counter = 0;
//u32 GLB_u8IRArr[33] = {0};
//u8 Value = 0;
//u8 FrameReady = 0;
//u8 x=0;
//
//int main(void)
//{
//	// === Clock Init ===
//	MRCC_voidInit();
//	MRCC_voidEnablePeripheralClock(AHB1_BUS, AHB1_GPIOA);
//	MRCC_voidEnablePeripheralClock(APB2_BUS, APB2_SYSCFG);
//	MRCC_voidEnablePeripheralClock(APB2_BUS, APB2_USART1);
//
//	// === SysTick Init ===
//	MSTK_voidInit();  // 16MHz / 8 = 2MHz  0.5us per tick
//	HSevenSegment_voidInit(PORTA);
//	// === GPIO Setup ===
//	MGPIO_voidSetMode(PORTA, PIN11, OUTPUT);
//	MGPIO_voidSetOutputConfig(PORTA, PIN11, Push_Pull, Low_Speed);
//	MGPIO_voidSetMode(PORTA, PIN12, OUTPUT);
//	MGPIO_voidSetOutputConfig(PORTA, PIN12, Push_Pull, Low_Speed);
//
//	MGPIO_voidSetMode(PORTA, PIN0, INPUT);
//	MGPIO_voidSetInputConfig(PORTA, PIN0, PULLUP);
//
//	// UART TX (PA9), RX (PA10)
//	MGPIO_voidSetMode(PORTA, PIN9, Alternative_Func);
//	MGPIO_voidSetAlternativeConfig(PORTA, PIN9, AF7);
//	MGPIO_voidSetMode(PORTA, PIN10, Alternative_Func);
//	MGPIO_voidSetAlternativeConfig(PORTA, PIN10, AF7);
//
//	// UART Init
//	HUART_voidInit(UART1);
//
//	// === EXTI Setup for PA0 ===
//	EXTI0_voidCallBack(Func1);
//	void_SetInterrupt(EXTI_LINE0, EXTI_PORT_A);
//	MEXTI_voidSetTrigger(EXTI_LINE0, EXTI_Falling);
//	MEXTI_voidEnable(EXTI_LINE0);
//	MNVIC_voidEnable(6);
//
//	// === Enable Global IRQs ===
//	asm("CPSIE i");
//	HUART_voidSendString(UART1, "TEST\r\n");
//
//
//	while (1)
//	{
//		if (FrameReady)
//		{
//			MGPIO_voidSetPinValue(PORTA, PIN11, HIGH);
//			char buffer[5]={0};
//			sprintf(buffer, "%02X\r\n", Value);  // Convert to HEX string
//			HUART_voidSendString(UART1, buffer);
//			MGPIO_voidSetPinValue(PORTA, PIN11, LOW);
//			// Debug: React to specific values
//			if(Value==0x0C)
//			{
//				MGPIO_voidSetPinValue(PORTA, PIN12, HIGH);
//				HSevenSegment_voidNumber(1,PORTA);
//			}
//
//			if(Value==0x18)
//					{
//						MGPIO_voidSetPinValue(PORTA, PIN12, HIGH);
//						HSevenSegment_voidNumber(2,PORTA);
//					}
//			if(Value==0x5E)
//							{
//								MGPIO_voidSetPinValue(PORTA, PIN12, HIGH);
//								HSevenSegment_voidNumber(3,PORTA);
//							}
//
//
//			FrameReady = 0;
//		}
//	}
//}
//
//// === EXTI ISR: Falling Edge Handler ===
//void Func1(void)
//{
//	if (GLB_u8StartFlag == 0)
//	{
//		MSTK_voidStartTimer(15000 * 2);  // 15ms
//		MSTK_voidCtrlIntState(Systick_IntEnable);
//		GLB_u8StartFlag = 1;
//		MSTK_voidCallBackSingle(Func2, 15000);
//	}
//	else
//	{
//		if (GLB_u8Counter < 33)
//		{
//			GLB_u8IRArr[GLB_u8Counter] = MSTK_u32GetElapsedTickSingleShot() / 2;
//			GLB_u8Counter++;
//			//MGPIO_voidSetPinValue(PORTA, PIN11, !x);
//		}
//
//		// Reset the timer for 4ms again
//		MSTK_voidStartTimer(4000 * 2);
//		STK->VAL = 0;
//		MSTK_voidCallBackSingle(Func2, 4000);
//	}
//}
//
//
//// === Timeout Handler: Decode NEC frame ===
//void Func2(void)
//{
//	GLB_u8StartFlag = 0;
//
//	if (GLB_u8Counter >= 33)
//	{
//		u8 i;
//		Value = 0;
//
//		for (i = 0; i < 8; i++)
//		{
//			if ((GLB_u8IRArr[17 + i] >= 1000) && (GLB_u8IRArr[17 + i] <= 1250))
//				CLR_BIT(Value, i);
//			else if ((GLB_u8IRArr[17 + i] >= 2000) && (GLB_u8IRArr[17 + i] <= 4400))
//				SET_BIT(Value, i);
//			//MGPIO_voidSetPinValue(PORTA, PIN11, !x);
//		}
//
//		FrameReady = 1;
//	}
//
//	GLB_u8Counter = 0;
//}
