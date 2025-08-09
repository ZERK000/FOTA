/*
 * UART_Program.c
 *
 *  Created on: Jul 23, 2025
 *      Author: Ziad
 */




#include "STD_TYPES.h"
#include "CommonMacros.h"
#include <MCAL/MUART_Config.h>
#include <MCAL/MUART_Interface.h>
#include <MCAL/MUART_Private.h>

// Helper macros
#define USART    UART_SELECTED_PERIPHERAL

void UART_voidInit(void)
{
	// Enable USART, TX, RX
	SET_BIT(USART->CR1, 13); // UE: USART Enable
	SET_BIT(USART->CR1, 3);  // TE: Transmit Enable
	SET_BIT(USART->CR1, 2);  // RE: Receive Enable

	// Word Length
#if UART_WORD_LENGTH == UART_WORD_LENGTH_9BITS
	SET_BIT(USART->CR1, 12);
#else
	CLEAR_BIT(USART->CR1, 12);
#endif

	// Parity
#if UART_PARITY_MODE == UART_PARITY_NONE
	CLEAR_BIT(USART->CR1, 10); // Parity control disable
#elif UART_PARITY_MODE == UART_PARITY_EVEN
	SET_BIT(USART->CR1, 10); // Enable parity
	CLEAR_BIT(USART->CR1, 9);  // Even
#elif UART_PARITY_MODE == UART_PARITY_ODD
	SET_BIT(USART->CR1, 10); // Enable parity
	SET_BIT(USART->CR1, 9);  // Odd
#else
	CLEAR_BIT(USART->CR1, 10);
	CLEAR_BIT(USART->CR1, 9);
#endif

	// Stop Bits
	USART->CR2 &= ~(0b11 << 12); // Clear STOP bits
#if UART_STOP_BITS == UART_STOP_BITS_0_5
	USART->CR2 |= (0b01 << 12);
#elif UART_STOP_BITS == UART_STOP_BITS_2
	USART->CR2 |= (0b10 << 12);
#elif UART_STOP_BITS == UART_STOP_BITS_1_5
	USART->CR2 |= (0b11 << 12);
#endif

	// Calculate BRR dynamically
	f32 USARTDIV;
	u32 Mantissa, Fraction, BRR_Value;

#if UART_OVERSAMPLING == UART_OVERSAMPLING_8
	SET_BIT(USART->CR1, 15);
	USARTDIV = ((f32)UART_FCK) / (8.0f * UART_BAUD_RATE);
	Mantissa = (u32)USARTDIV;
	Fraction = (u32)((USARTDIV - Mantissa) * 8.0f + 0.5f); // Round
	if (Fraction > 7) {
		Fraction = 0;
		Mantissa += 1;
	}
	BRR_Value = (Mantissa << 4) | (Fraction & 0x07);

#else
	CLEAR_BIT(USART->CR1, 15);
	USARTDIV = ((f32)UART_FCK) / (16.0f * UART_BAUD_RATE);
	Mantissa = (u32)USARTDIV;
	Fraction = (u32)((USARTDIV - Mantissa) * 16.0f + 0.5f); // Round
	if (Fraction > 15) {
		Fraction = 0;
		Mantissa += 1;
	}
	BRR_Value = (Mantissa << 4) | (Fraction & 0x0F);

#endif

	USART->BRR = BRR_Value;
	// Enable RX interrupt LAST
	SET_BIT(USART->CR1, 5); // RXNEIE: RX not empty interrupt enable
}

void UART_voidSend(u8 Copy_u8Data)
{
	// Wait until TXE = 1
	while (GET_BIT(USART->SR, 7) == 0);
	USART->DR = Copy_u8Data;
}

u8 UART_u8Receive(void)
{
	return (u8)(USART->DR & 0xFF);
}

void UART_voidSendString(const char* Copy_str)
{
	u8 i = 0;
	while (Copy_str[i] != '\0')
	{
		UART_voidSend(Copy_str[i]);
		i++;
	}
}
