/*
 * SPI_Interface.h
 *
 *  Created on: Jul 29, 2025
 *      Author: Ziad
 */

#ifndef SPI_INTERFACE_H_
#define SPI_INTERFACE_H_

#include "MCAL/MSPI_Private.h"

// SPI modes
#define MASTER      1
#define SLAVE       0


// Clock phase
#define SPI_CPHA_1EDGE  0
#define SPI_CPHA_2EDGE  1

// Data frame format
#define SPI_DFF_8BIT    0
#define SPI_DFF_16BIT   1

// First bit
#define SPI_MSB_FIRST   0
#define SPI_LSB_FIRST   1

// Baud rate values (3-bit values)
#define SPI_BR_FPCLK_DIV_2     0b000
#define SPI_BR_FPCLK_DIV_4     0b001
#define SPI_BR_FPCLK_DIV_8     0b010
#define SPI_BR_FPCLK_DIV_16    0b011
#define SPI_BR_FPCLK_DIV_32    0b100
#define SPI_BR_FPCLK_DIV_64    0b101
#define SPI_BR_FPCLK_DIV_128   0b110
#define SPI_BR_FPCLK_DIV_256   0b111

void SPI_voidInit(void);
void SPI_voidTransmit(u16 data);
u16 SPI_u16Receive(void);
u16 SPI_u16TransmitReceive(u16 data);
void SPI_voidTransmitArray(u16 *arr, u32 len);

void SPI_voidSelectSlave(void);
void SPI_voidDeselectSlave(void);



#endif /* SPI_INTERFACE_H_ */
