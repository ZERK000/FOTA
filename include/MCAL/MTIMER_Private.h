/*
 * MTIMER_Private.h
 *
 *  Created on: Jul 30, 2025
 *      Author: Catherine Nader
 */

#ifndef MTIMER_PRIVATE_H_
#define MTIMER_PRIVATE_H_

/*-----------------------------------------
 * Base Addresses for STM32F401 Timers
 *----------------------------------------*/
#define TIMER1_BASE_ADDRESS   0x40010000
#define TIMER2_BASE_ADDRESS   0x40000000
#define TIMER3_BASE_ADDRESS   0x40000400
#define TIMER4_BASE_ADDRESS   0x40000800
#define TIMER5_BASE_ADDRESS   0x40000C00
#define TIMER9_BASE_ADDRESS   0x40014800
#define TIMER10_BASE_ADDRESS  0x40014400
#define TIMER11_BASE_ADDRESS  0x40014800

/*-----------------------------------------
 * Timer Register Definitions
 *----------------------------------------*/

/* Advanced Control Timer (TIM1) */
typedef struct
{
	u32 CR1;
	u32 CR2;
	u32 SMCR;
	u32 DIER;
	u32 SR;
	u32 EGR;
	u32 CCMR1;
	u32 CCMR2;
	u32 CCER;
	u32 CNT;
	u32 PSC;
	u32 ARR;
	u32 RCR;
	u32 CCR1;
	u32 CCR2;
	u32 CCR3;
	u32 CCR4;
	u32 BDTR;
	u32 DCR;
	u32 DMAR;
} TIMER1_t;

/* General-Purpose Timers (TIM2-TIM5) */
typedef struct
{
	u32 CR1;
	u32 CR2;
	u32 SMCR;
	u32 DIER;
	u32 SR;
	u32 EGR;
	u32 CCMR1;
	u32 CCMR2;
	u32 CCER;
	u32 CNT;
	u32 PSC;
	u32 ARR;
	u32 Reserved1;
	u32 CCR1;
	u32 CCR2;
	u32 CCR3;
	u32 CCR4;
	u32 Reserved2;
	u32 DCR;
	u32 DMAR;
} TIMER2_5_t;

/* Basic Timer Structure for TIM9 (2-channel) */
typedef struct
{
	u32 CR1;
	u32 Resrved1;
	u32 SMCR;
	u32 DIER;
	u32 SR;
	u32 EGR;
	u32 CCMR1;
	u32 Resrved2;
	u32 CCER;
	u32 CNT;
	u32 PSC;
	u32 ARR;
	u32 Reserved3;
	u32 CCR1;
	u32 CCR2;
	u32 Reserved4;
	u32 Reserved5;
	u32 Reserved6;
	u32 Reserved7;
	u32 Reserved8;
} TIMER9_t;

/* Minimal Timer Structure for TIM10 & TIM11 (1-channel) */
typedef struct
{
	u32 CR1;
	u32 Reserved1;
	u32 SMCR;
	u32 DIER;
	u32 SR;
	u32 EGR;
	u32 CCMR1;
	u32 Reserved2;
	u32 CCER;
	u32 CNT;
	u32 PSC;
	u32 ARR;
	u32 Reserved3;
	u32 CCR1;
	u32 Reserved4;
	u32 Reserved5;
	u32 Reserved6;
	u32 Reserved7;
	u32 Reserved8;
	u32 Reserved9;
	u32 OR;
} TIMER10_11_t;

/*-----------------------------------------
 * Peripheral Pointers
 *----------------------------------------*/
#define TIMER1  ((volatile TIMER1_t*)TIMER1_BASE_ADDRESS)
#define TIMER2  ((volatile TIMER2_5_t*)TIMER2_BASE_ADDRESS)
#define TIMER3  ((volatile TIMER2_5_t*)TIMER3_BASE_ADDRESS)
#define TIMER4  ((volatile TIMER2_5_t*)TIMER4_BASE_ADDRESS)
#define TIMER5  ((volatile TIMER2_5_t*)TIMER5_BASE_ADDRESS)
#define TIMER9  ((volatile TIMER9_t*)TIMER9_BASE_ADDRESS)
#define TIMER10 ((volatile TIMER10_11_t*)TIMER10_BASE_ADDRESS)
#define TIMER11 ((volatile TIMER10_11_t*)TIMER11_BASE_ADDRESS)

/*-----------------------------------------
 * Common Bit Definitions
 *----------------------------------------*/
#define CEN      0   // Counter enable bit
#define UP       0   // Up-counting direction
#define DOWN     1   // Down-counting direction
#define ENABLE   1   // General enable
#define DISABLE  0   // General disable

/* Clock Division */
#define DIV1     0
#define DIV2     1
#define DIV4     2

/* Channel Modes */
#define OUTPUT_TIMER      0   // Channel as output
#define INPUT_TIMER       1   // Input capture from corresponding input (TIx)
#define INPUT_CC    2   // Input capture from cross input (TIx on another channel)
#define INPUT_TRC   3   // Mapped to internal trigger controller (TRC)

/* Input Edge Triggers */
#define RISINGE     0
#define FALLINGE    1
#define BOTHE       3

/* Channel Identifiers */
#define Channel1    1
#define Channel2    2
#define Channel3    3
#define Channel4    4

#endif /* MTIMER_PRIVATE_H_ */
