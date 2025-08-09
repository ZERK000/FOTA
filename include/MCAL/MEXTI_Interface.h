#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

#include "MCAL/MEXTI_Private.h"

typedef enum {
	EXTI_lINE0,
	EXTI_lINE1,
	EXTI_lINE2,
	EXTI_lINE3,
	EXTI_lINE4,
	EXTI_lINE5,
	EXTI_lINE6,
	EXTI_lINE7,
	EXTI_lINE8,
	EXTI_lINE9,
	EXTI_lINE10,
	EXTI_lINE11,
	EXTI_lINE12,
	EXTI_lINE13,
	EXTI_lINE14,
	EXTI_lINE15

}EXTI_LINE_t;

typedef enum {
	EXTI_PORT_A,
	EXTI_PORT_B,
	EXTI_PORT_C,
	EXTI_PORT_D,
	EXTI_PORT_E,
	EXTI_PORT_F
}EXTI_PORT_t;

typedef enum
{
	EXTI_FALLING,
	EXTI_RISING,
	EXTI_ONCHANGE
}EXTI_TRIGGERMODE_t;



void EXTI_voidSetInterruptPort(EXTI_LINE_t Line, EXTI_PORT_t Port);
void EXTI_voidEnable(EXTI_LINE_t Line);
void EXTI_voidDisable(EXTI_LINE_t Line);
void EXTI_voidSetTrigger(EXTI_LINE_t Line, EXTI_TRIGGERMODE_t Mode);
void EXTI0_voidCallBack(void((*ptr)(void)));
void EXTI1_voidCallBack(void((*ptr)(void)));
void EXTI2_voidCallBack(void((*ptr)(void)));
void EXTI3_voidCallBack(void((*ptr)(void)));

#endif
