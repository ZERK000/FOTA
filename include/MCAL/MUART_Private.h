/*
 * UART_Private.h
 *
 *  Created on: Jul 23, 2025
 *      Author: Ziad
 */

#ifndef UART_PRIVATE_H_
#define UART_PRIVATE_H_

#include "STD_TYPES.h"

#define USART1_BASE_ADDRESS   0x40011000
#define USART2_BASE_ADDRESS   0x40004400
#define USART6_BASE_ADDRESS   0x40011400
typedef struct{
	u32 SR;
	u32 DR;
	u32 BRR;
	u32 CR1;
	u32 CR2;
	u32 CR3;
	u32 GTPR;

}UART_t;


#define USART1   ((volatile UART_t*)USART1_BASE_ADDRESS)
#define USART2   ((volatile UART_t*)USART2_BASE_ADDRESS)
#define USART6   ((volatile UART_t*)USART6_BASE_ADDRESS)

#endif /* UART_PRIVATE_H_ */
