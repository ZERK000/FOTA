/*
 * Systick_Interface.h
 *
 *  Created on: Jul 15, 2025
 *      Author: Ziad
 */

#ifndef SYSTICK_INTERFACE_H_
#define SYSTICK_INTERFACE_H_

#include "MCAL/MSystick_Private.h"

typedef enum{
	Systick_IntDisable,
	Systick_IntEnable
}STK_IntState;

void MSTK_voidInit();
void MSTK_voidStartTimer(u32 Copy_u32ReloadValue);
void MSTK_voidCtrlIntState(STK_IntState Copy_uddtIntState);
u8 MSTK_u8ReadFlag();
/*Function in Single shot*/
u32 MSTK_u32GetElapsedTickSingleShot();
u32 MSTK_u32GetRemainingTickSingleShot();

void MSTK_voidDelayms(u32 Copy_u32Delayms);
void MSTK_voidDelayus(u32 Copy_u32Delayus);

#endif /* SYSTICK_INTERFACE_H_ */
