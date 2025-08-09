/*
 * RCCInterface.h
 *
 *  Created on: Jul 16, 2025
 *      Author: Ziad
 */

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

//#include "STD_TYPES.h"
#include "MCAL/MRCC_Private.h"

#define DISABLE 0
#define ENABLE  1

/////////////////// RCC_CR options /////////////////
// offset = 0x00
#define HSI_ON 0
#define HSE_ON 1
#define HSE_BYP 2
#define CSS_ON 3
#define PLL_ON 4
#define PLLI2S_ON 5







// SYSCLK options
#define RCC_SYSCLK_HSI   0
#define RCC_SYSCLK_HSE   1
#define RCC_SYSCLK_PLL   2

// AHB Prescaler options (HPRE)
#define RCC_AHB_PRESCALER_DIV1   0x0
#define RCC_AHB_PRESCALER_DIV2   0x8
#define RCC_AHB_PRESCALER_DIV4   0x9
#define RCC_AHB_PRESCALER_DIV8   0xA
// ... up to 0xF for DIV512

// APB1/2 Prescaler options (PPRE1, PPRE2)
#define RCC_APB_PRESCALER_DIV1   0x0
#define RCC_APB_PRESCALER_DIV2   0x4
#define RCC_APB_PRESCALER_DIV4   0x5
#define RCC_APB_PRESCALER_DIV8   0x6
#define RCC_APB_PRESCALER_DIV16  0x7



// AHB1 Peripheral Enable Bits
#define RCC_AHB1_GPIOA    0
#define RCC_AHB1_GPIOB    1
#define RCC_AHB1_GPIOC    2
#define RCC_AHB1_GPIOD    3
#define RCC_AHB1_GPIOE    4
#define RCC_AHB1_GPIOH    7
#define RCC_AHB1_CRC      12
#define RCC_AHB1_DMA1     21
#define RCC_AHB1_DMA2     22
#define RCC_APB2_USART1   4
#define RCC_APB2_SPI1	  12
#define RCC_SYSCFG		  14


typedef enum {
	AHB1,
	AHB2,
	APB1,
	APB2
}PeripheralsBus_t;

// Function prototype
// Function prototype
void RCC_SetClock(u8 clock, u8 state);
void RCC_ConfigBuses(u8 sysclk, u8 ahb_prescaler, u8 apb1_prescaler, u8 apb2_prescaler);
void RCC_EnablePeripheralClock(PeripheralsBus_t BusType ,u8 peripheral);
void RCC_DisablePeripheralClock(PeripheralsBus_t BusType ,u8 peripheral);



#endif
