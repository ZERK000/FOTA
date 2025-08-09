/*
 * UART_Config.h
 *
 *  Created on: Jul 23, 2025
 *      Author: Ziad
 */

#ifndef UART_CONFIG_H_
#define UART_CONFIG_H_

#define UART_WORD_LENGTH_8BITS   0
#define UART_WORD_LENGTH_9BITS   1

#define UART_PARITY_NONE         0
#define UART_PARITY_EVEN         1
#define UART_PARITY_ODD          2

#define UART_STOP_BITS_1         0
#define UART_STOP_BITS_0_5       1
#define UART_STOP_BITS_2         2
#define UART_STOP_BITS_1_5       3

#define UART_OVERSAMPLING_16     0
#define UART_OVERSAMPLING_8      1



#define UART_FCK   16000000UL  // Define your actual peripheral clock frequency here

/*
 * Select UART Peripheral
 * Options: USART1, USART2, USART6
 */
#define UART_SELECTED_PERIPHERAL     USART1

/*
 * Baud Rate
 * Common values: 9600, 115200, 57600, etc.
 */
#define UART_BAUD_RATE               115200

/*
 * Word Length
 * Options:
 *   UART_WORD_LENGTH_8BITS
 *   UART_WORD_LENGTH_9BITS
 */
#define UART_WORD_LENGTH             UART_WORD_LENGTH_8BITS

/*
 * Parity Control
 * Options:
 *   UART_PARITY_NONE
 *   UART_PARITY_EVEN
 *   UART_PARITY_ODD
 */
#define UART_PARITY_MODE             UART_PARITY_NONE

/*
 * Stop Bits
 * Options:
 *   UART_STOP_BITS_1
 *   UART_STOP_BITS_0_5
 *   UART_STOP_BITS_2
 *   UART_STOP_BITS_1_5
 */
#define UART_STOP_BITS               UART_STOP_BITS_1

/*
 * Oversampling Mode
 * Options:
 *   UART_OVERSAMPLING_16
 *   UART_OVERSAMPLING_8
 */
#define UART_OVERSAMPLING            UART_OVERSAMPLING_16



#endif /* UART_CONFIG_H_ */
