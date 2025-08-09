/*
 * MTIMER_Program.c
 *
 *  Created on: Jul 30, 2025
 *      Author: Catherine Nader
 */
#include "STD_TYPES.h"
#include "CommonMacros.h"
#include <MCAL/MTIMER_Interface.h>


//callback timer1_cc function pointer
static void (*MTIMER1_CC_Callback)(void) = NULL;



/*
 * Function: MTIMER1_voidInit
 * --------------------------
 * Initializes Timer 1 based on the configuration defined in MTIMER_Config.h.
 * - One Pulse Mode
 * - Counter Direction
 * - Clock Division
 * - Channel Modes (Input/Output)
 * - Edge Configuration (for input mode)
 */
void MTIMER1_voidInit()
{
	// Configure One Pulse Mode (0: continuous, 1: one-shot)
	TIMER1->CR1 |= (OnePulseMode << 3);

	// Set counter direction (UP/DOWN)
	TIMER1->CR1 |= (DIR << 4);

	// Set clock division (DIV1, DIV2, DIV4)
	TIMER1->CR1 |= (DIV << 8);

	// Configure Channel 1
	if (CHANNEL1E)
	{
		TIMER1->CCMR1 |= (Ch1M << 0);           // Set mode for channel 1
		TIMER1->CCER |= (EDGEST << 1);           // Set edge sensitivity
		TIMER1->CCER |= (1 << 0);               // Enable channel 1
	}

	// Configure Channel 2
	if (CHANNEL2E)
	{
		TIMER1->CCMR1 |= (Ch2M << 8);           // Set mode for channel 2
		TIMER1->CCER |= (1 << 4);               // Enable channel 2
	}

	// Configure Channel 3
	if (CHANNEL3E)
	{
		TIMER1->CCMR2 |= (Ch3M << 0);           // Set mode for channel 3
		TIMER1->CCER |= (1 << 8);               // Enable channel 3
	}

	// Configure Channel 4
	if (CHANNEL4E)
	{
		TIMER1->CCMR2 |= (Ch4M << 8);           // Set mode for channel 4
		TIMER1->CCER |= (1 << 12);              // Enable channel 4
	}

	// Start the timer
	TIMER1->CR1 |= (ENABLE << CEN);
}

/*
 * Function: MTIMER1_u16ReadCaptureValue
 * -------------------------------------
 * Reads the captured value from the enabled channel.
 * - Waits until the capture flag is set
 * - Returns 0xFFFF if overcapture is detected (data loss)
 */
u16 MTIMER1_u16ReadCaptureValue()
{
	if (CHANNEL1E)
	{
		while (!GET_BIT(TIMER1->SR, 1));            // Wait for CC1IF flag
		if (GET_BIT(TIMER1->SR, 9))                 // Check CC1OF flag
		{
			TIMER1->SR &= ~(1 << 9);                // Clear overcapture flag
			return 0xFFFF;
		}
		return (u16)(TIMER1->CCR1);
	}

	if (CHANNEL2E)
	{
		while (!GET_BIT(TIMER1->SR, 2));            // Wait for CC2IF flag
		if (GET_BIT(TIMER1->SR, 10))                // Check CC2OF flag
		{
			TIMER1->SR &= ~(1 << 10);               // Clear overcapture flag
			return 0xFFFF;
		}
		return (u16)(TIMER1->CCR2);
	}

	if (CHANNEL3E)
	{
		while (!GET_BIT(TIMER1->SR, 3));            // Wait for CC3IF flag
		if (GET_BIT(TIMER1->SR, 11))                // Check CC3OF flag
		{
			TIMER1->SR &= ~(1 << 11);               // Clear overcapture flag
			return 0xFFFF;
		}
		return (u16)(TIMER1->CCR3);
	}

	if (CHANNEL4E)
	{
		while (!GET_BIT(TIMER1->SR, 4));            // Wait for CC4IF flag
		if (GET_BIT(TIMER1->SR, 12))                // Check CC4OF flag
		{
			TIMER1->SR &= ~(1 << 12);               // Clear overcapture flag
			return 0xFFFF;
		}
		return (u16)(TIMER1->CCR4);
	}

	return 0;
}

/*
 * Function: MTIMER1_u16ReadCounterValue
 * -------------------------------------
 * Returns the current counter value from the CNT register.
 */
u16 MTIMER1_u16ReadCounterValue()
{
	return (u16)(TIMER1->CNT);
}

/*
 * Function: MTIMER1_voidStop
 * --------------------------
 * Stops Timer 1 by clearing the CEN bit.
 */
void MTIMER1_voidStop()
{
	TIMER1->CR1 &= ~(1 << 0); // Clear CEN bit to stop the timer
}

/*
 * Function: MTIMER1_voidSetPrescaler
 * ----------------------------------
 * Sets the prescaler value for Timer 1.
 * - Argument: Copy_u16prescaler -> the desired prescaler value
 */
void MTIMER1_voidSetPrescaler(u16 Copy_u16prescaler)
{
	TIMER1->PSC = Copy_u16prescaler;
}

/*
 * Function: MTIMER1_voidSetARR
 * ----------------------------
 * Sets the auto-reload value for Timer 1.
 * - Argument: Copy_u16arr -> the desired ARR value
 */
void MTIMER1_voidSetARR(u16 Copy_u16arr)
{
	TIMER1->ARR = Copy_u16arr;
}

/*
 * Function: MTIMER1_voidEnableInterrupt
 * -------------------------------------
 * Enables interrupt for a specific channel or update event.
 * - Argument: Copy_u8channel -> use 0 for UIE, 1-4 for CCxIE
 */
void MTIMER1_voidEnableInterrupt(u8 Copy_u8channel)
{
	TIMER1->DIER |= (1 << Copy_u8channel);
}

/*
 * Function: MTIMER1_voidDisableInterrupt
 * --------------------------------------
 * Disables interrupt for a specific channel or update event.
 * - Argument: Copy_u8channel -> use Channel1-Channel4
 */
void MTIMER1_voidDisableInterrupt(u8 Copy_u8channel)
{
	TIMER1->DIER &= ~(1 << Copy_u8channel);
}


//call back
void MTIMER1_voidSetCallback(void (*Copy_ptr)(void))
{
	if (Copy_ptr != NULL)
	{
		MTIMER1_CC_Callback = Copy_ptr;
	}
}

void TIM1_CC_IRQHandler(void)
{
	if (MTIMER1_CC_Callback != NULL)
	{
		MTIMER1_CC_Callback();  // Call your application logic
	}

	// Clear capture interrupt flags to avoid re-entering
	if (GET_BIT(TIMER1->SR, 1)) TIMER1->SR &= ~(1 << 1);  // CC1IF
	if (GET_BIT(TIMER1->SR, 2)) TIMER1->SR &= ~(1 << 2);  // CC2IF
	if (GET_BIT(TIMER1->SR, 3)) TIMER1->SR &= ~(1 << 3);  // CC3IF
	if (GET_BIT(TIMER1->SR, 4)) TIMER1->SR &= ~(1 << 4);  // CC4IF
}
