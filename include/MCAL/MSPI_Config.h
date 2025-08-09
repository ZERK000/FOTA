/*
 * SPI_Config.h
 *
 *  Created on: Jul 29, 2025
 *      Author: Ziad
 */

#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_


#include "MCAL/MSPI_Interface.h"

// SPI and Pins
#define SPI_INSTANCE  1  // choose between SPI1 or SPI2

#if (SPI_INSTANCE == 1)

#define SPI 			SPI1
#define SPI_PORT 		PORTA
#define SCK_PIN 		5
#define MOSI_PIN 		7
#define MISO_PIN		6
#define NSS_PIN			4

#elif (SPI_INSTANCE == 2)

#define SPI 			SPI2
#define SPI_PORT 		PORTB
#define SCK_PIN 		13
#define MOSI_PIN 		15
#define MISO_PIN 		14
#define NSS_PIN			12

#endif


#define SPI_MODE          MASTER // Choose between master or slave

// Clock polarity and phase
#define SPI_CPOL          1 // 0 for low, 1 for high
#define SPI_CPHA          SPI_CPHA_1EDGE // 0 for 1 edge, 1 for 2 edge

// Data frame format
#define SPI_DFF           SPI_DFF_8BIT

// First bit
#define SPI_FIRST_BIT     SPI_MSB_FIRST

// Baud rate control (0 to 7 for fPCLK/2 to fPCLK/256)
#define SPI_BAUDRATE      SPI_BR_FPCLK_DIV_2

// Software slave management
#define SPI_SSM_ENABLE    1



#endif /* SPI_CONFIG_H_ */
