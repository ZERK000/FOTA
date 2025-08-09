#include <MCAL/MEXTI_Interface.h>
#include "STD_TYPES.h"


static void(*GlobalPtrEXTI0) (void) = NULL;
static void(*GlobalPtrEXTI1) (void) = NULL;
static void(*GlobalPtrEXTI2) (void) = NULL;
static void(*GlobalPtrEXTI3) (void) = NULL;

void EXTI_voidSetInterruptPort(EXTI_LINE_t Line, EXTI_PORT_t Port)
{
	SYSCFG ->EXTICR[Line/SYS_DIV] &= (SYS_MASK <<((Line % SYS_DIV) * 4));
	SYSCFG ->EXTICR[Line/SYS_DIV] &= (Port <<((Line % SYS_DIV) * 4));

}

void EXTI_voidEnable(EXTI_LINE_t Line)
{
	EXTI ->IMR |= (1<< Line);
}

void EXTI_voidDisable(EXTI_LINE_t Line)
{
	EXTI ->IMR &= ~(1<< Line);
}

void EXTI_voidSetTrigger(EXTI_LINE_t Line, EXTI_TRIGGERMODE_t Mode)
{
	switch(Mode)
	{
	case EXTI_FALLING:
		EXTI->RTSR &= ~(1<< Line);
		EXTI->FTSR |= (1<< Line);
		break;

	case EXTI_RISING:
		EXTI->RTSR |= (1<< Line);
		EXTI->FTSR &= ~(1<< Line);
		break;

	case EXTI_ONCHANGE:
		EXTI->RTSR |= (1<< Line);
		EXTI->FTSR |= (1<< Line);
		break;

	default:
		break;
	};
}


void EXTI0_voidCallBack(void((*ptr)(void))) {

	GlobalPtrEXTI0 = ptr;
}


void EXTI0_IRQHandler()
{
	if (GlobalPtrEXTI0 != NULL)
	{
		GlobalPtrEXTI0();
		EXTI->PR |=(1<<0);
	}
}
void EXTI1_voidCallBack(void((*ptr)(void))) {

	GlobalPtrEXTI1 = ptr;
}


void EXTI1_IRQHandler()
{
	if (GlobalPtrEXTI1 != NULL)
	{
		GlobalPtrEXTI1();
		EXTI->PR |=(1<<1);
	}
}
void EXTI2_voidCallBack(void((*ptr)(void))) {

	GlobalPtrEXTI2 = ptr;
}


void EXTI2_IRQHandler()
{
	if (GlobalPtrEXTI2 != NULL)
	{
		GlobalPtrEXTI2();
		EXTI->PR |=(1<<2);
	}
}
void EXTI3_voidCallBack(void((*ptr)(void))) {

	GlobalPtrEXTI3 = ptr;
}


void EXTI3_IRQHandler()
{
	if (GlobalPtrEXTI2 != NULL)
	{
		GlobalPtrEXTI3();
		EXTI->PR |=(1<<3);
	}
}
