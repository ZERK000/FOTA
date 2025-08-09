/*
 * UART_Interface.h
 *
 *  Created on: Jul 23, 2025
 *      Author: Ziad
 */

#ifndef UART_INTERFACE_H_
#define UART_INTERFACE_H_

#include "MCAL/MUART_Private.h"

void UART_voidInit(void);
void UART_voidSend(u8 Copy_u8Data);
u8   UART_u8Receive(void);
void UART_voidSendString(const char* Copy_str);


#endif /* UART_INTERFACE_H_ */
