
#include "STD_TYPES.h"
#include "CommonMacros.h"
#include <MCAL/MRCC_Interface.h>




void RCC_SetClock(u8 clock, u8 state)
{
	switch(clock) {
	case HSI_ON:
		if(state == ENABLE)
		{
			SET_BIT(RCC->CR, RCC_CR_HSION);
			while (!GET_BIT(RCC->CR, RCC_CR_HSIRDY));
		}
		else CLEAR_BIT(RCC->CR, RCC_CR_HSION);
		break;

	case HSE_ON:
		if (state == ENABLE)
		{
			SET_BIT(RCC->CR, RCC_CR_HSEON);
			while (!GET_BIT(RCC->CR, RCC_CR_HSERDY));
		}
		else CLEAR_BIT(RCC->CR, RCC_CR_HSEON);
		break;

	case HSE_BYP:
		if (state == ENABLE)
		{
			SET_BIT(RCC->CR, RCC_CR_HSEBYP);
		}
		else CLEAR_BIT(RCC->CR, RCC_CR_HSEBYP);
		break;

	case CSS_ON:
		if (state == ENABLE)
		{
			SET_BIT(RCC->CR, RCC_CR_CSSON);
		}
		else CLEAR_BIT(RCC->CR, RCC_CR_CSSON);
		break;

	case PLL_ON:
		if (state == ENABLE)
		{
			SET_BIT(RCC->CR, RCC_CR_PLLON);
			while (!GET_BIT(RCC->CR, RCC_CR_PLLRDY));
		}
		else CLEAR_BIT(RCC->CR, RCC_CR_PLLON);
		break;

	case PLLI2S_ON:
		if (state == ENABLE)
		{
			SET_BIT(RCC->CR, RCC_CR_PLLI2SON);
			while (!GET_BIT(RCC->CR, RCC_CR_PLLI2SRDY));
		}
		else CLEAR_BIT(RCC->CR, RCC_CR_PLLI2SON);
		break;

	default:
		// Optionally handle invalid inputs
		break;
	}
}

void RCC_ConfigBuses(u8 sysclk, u8 ahb_prescaler, u8 apb1_prescaler, u8 apb2_prescaler)
{
	// 1. Select system clock source (SW bits [1:0])
	RCC->CFGR &= ~(0x3 << 0);             // Clear SW bits
	RCC->CFGR |=  ((sysclk & 0x3) << 0);  // Set desired source

	// 2. Wait until SWS bits [3:2] match selected clock
	while (((RCC->CFGR >> 2) & 0x3) != (sysclk & 0x3));

	// 3. Set AHB prescaler (HPRE bits [7:4])
	RCC->CFGR &= ~(0xF << 4);                    // Clear HPRE
	RCC->CFGR |= ((ahb_prescaler & 0xF) << 4);   // Set HPRE

	// 4. Set APB1 prescaler (PPRE1 bits [12:10])
	RCC->CFGR &= ~(0x7 << 10);                   // Clear PPRE1
	RCC->CFGR |= ((apb1_prescaler & 0x7) << 10); // Set PPRE1

	// 5. Set APB2 prescaler (PPRE2 bits [15:13])
	RCC->CFGR &= ~(0x7 << 13);                   // Clear PPRE2
	RCC->CFGR |= ((apb2_prescaler & 0x7) << 13); // Set PPRE2
}


void RCC_EnablePeripheralClock(PeripheralsBus_t BusType ,u8 peripheral)
{
	switch(BusType)
	{
	case AHB1:
		SET_BIT(RCC->AHB1ENR, peripheral);
		break;

	case AHB2:
		SET_BIT(RCC->AHB2ENR, peripheral);
		break;

	case APB1:
		SET_BIT(RCC->APB1ENR, peripheral);
		break;

	case APB2:
		SET_BIT(RCC->APB2ENR, peripheral);
		break;

	}

}

void RCC_DisablePeripheralClock(PeripheralsBus_t BusType ,u8 peripheral)
{
	switch(BusType)
	{
	case AHB1:
		CLEAR_BIT(RCC->AHB1ENR, peripheral);
		break;

	case AHB2:
		CLEAR_BIT(RCC->AHB2ENR, peripheral);
		break;

	case APB1:
		CLEAR_BIT(RCC->APB1ENR, peripheral);
		break;

	case APB2:
		CLEAR_BIT(RCC->APB2ENR, peripheral);
		break;

	}

}


