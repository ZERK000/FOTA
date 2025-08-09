/*
 * MTIMER_Interface.h
 *
 *  Created on: Jul 30, 2025
 *      Author: Catherine Nader
 */

#ifndef MTIMER_INTERFACE_H_
#define MTIMER_INTERFACE_H_

#include "MCAL/MTIMER_Private.h"
#include "MCAL/MTIMER_Config.h"

void MTIMER1_voidInit();
void MTIMER1_voidStop();
u16 MTIMER1_u16ReadCaptureValue();
u16 MTIMER1_u16ReadCounterValue();
void MTIMER1_voidSetARR(u16 Copy_u16arr);
void MTIMER1_voidSetPrescaler(u16 Copy_u16prescaler);
void MTIMER1_voidEnableInterrupt(u8 Copy_u8channel);
void MTIMER1_voidDisableInterrupt(u8 Copy_u8channel);

void TIM1_CC_IRQHandler(void);
void MTIMER1_voidSetCallback(void (*Copy_ptr)(void));

#endif /* MTIMER_INTERFACE_H_ */
