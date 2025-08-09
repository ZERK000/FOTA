/*
 * HIR_Program.c
 *
 *  Created on: Aug 5, 2025
 *      Author: Catherine Nader
 */
#include "CommonMacros.h"
#include "STD_TYPES.h"

#include "HAL/HIR_Interface.h"
#include "HAL/HIR_Private.h"
#include "MCAL/MGPIO_Interface.h"
#include "MCAL/MEXTI_Interface.h"
#include "MCAL/MSystick_Interface.h"



volatile u16 PreviousCapture = 0;
volatile u16 CurrentCapture = 0;
volatile u8 startnec=0;
u8 FrameReady = 0;
u8 FrameBits[32] = {0};
u8 FrameIndex = 0;
u8 Command = 0;

u8 BitArrayToByte(u8 *arr)
{
	u8 result = 0;
	for (int i = 0; i < 8; i++)
		result |= (arr[i] << i);
	return result;
}

void Handler(void)
{

	MGPIO_voidSetPinValue(PORTA,10,1);
	u32 diff = MSTK_u32GetElapsedTickSingleShot()/2;

	if (startnec == 0)
	{
		// Expecting start pulse (9ms + 4.5ms)
		if (IS_IN_RANGE(diff, NEC_START_MS_MIN, NEC_START_MS_MAX))
		{MGPIO_voidSetPinValue(PORTA,11,1);
			startnec++;
			FrameIndex = 0;  // Reset just in case
		}
	}
	else
	{
		if (IS_IN_RANGE(diff, NEC_BIT_HIGH_MIN, NEC_BIT_HIGH_MAX))
		{MGPIO_voidSetPinValue(PORTA,10,0);
			FrameBits[FrameIndex++] = 0;
		}
		else if (IS_IN_RANGE(diff, NEC_BIT_LOW_MIN, NEC_BIT_LOW_MAX))
		{MGPIO_voidSetPinValue(PORTA,10,0);
			FrameBits[FrameIndex++] = 1;
		}
		else
		{
			// Invalid pulse width — reset everything
			FrameIndex = 0;
			startnec=0;
			return;
		}

		if (FrameIndex == 32)
		{MGPIO_voidSetPinValue(PORTA,11,0);
			u8 Address     = BitArrayToByte(&FrameBits[0]);
			u8 NotAddress  = BitArrayToByte(&FrameBits[8]);
			u8 Cmd         = BitArrayToByte(&FrameBits[16]);
			u8 NotCmd      = BitArrayToByte(&FrameBits[24]);

			if ((Address ^ NotAddress) == 0xFF && (Cmd ^ NotCmd) == 0xFF)
			{
				Command = Cmd;
				FrameReady = 1;
			}

			// Always reset after full frame
			FrameIndex = 0;
			startnec=0;
		}
	}

	PreviousCapture = CurrentCapture;
	MSTK_voidStartTimer(0xFFFFFF);  // Restart after capturing
}
void IR_voidInit()
{
	//MRCC_voidEnablePeripheralClock(APB2_BUS, APB2_SYSCFG);
	//MRCC_voidEnablePeripheralClock(AHB1_BUS, AHB1_GPIOA);
	//MRCC_voidEnablePeripheralClock(APB2_BUS,APB2_USART1);
	//MSTK_voidInit();

	MGPIO_voidSetMode(PORTA,12,OUTPUT);
    MGPIO_voidSetOutputConfig(PORTA,12,PUSH_PULL,LOW_SPEED);
	MGPIO_voidSetMode(PORTA,11,OUTPUT);
    MGPIO_voidSetOutputConfig(PORTA,11,PUSH_PULL,LOW_SPEED);
    void_SetInterrupt(EXTI_lINE0,EXTI_PORT_A);
    MEXTI_voidEnable(EXTI_lINE0);

	MEXTI_voidSetTrigger(EXTI_lINE0,EXTI_FALLING);


	MNVIC_voidEnable(6);
	EXTI0_voidCallBack(Handler);

	asm("CPSIE i");  // Enable global interrupts

	MSTK_voidStartTimer(0xFFFFFF);  // 24-bit max count



}

void IR_voidLoop()
{
	while (1)
		{
			if (FrameReady)
			{
				// Do something with decoded command
				const char* cmdfull = Command;
				char buffer[5];
				sprintf(buffer, "%02X", cmdfull);  // Convert to hex
				//HUART_voidSendString(UART1,buffer); //testing uart
				//HUART_voidWrite(UART1,'\n'); //testing uart
				//HUART_voidSendString(UART1,cmdfull);
				FrameReady = 0; // Reset flag
				// e.g., toggle LED, send UART, etc.
			}
		}

}
