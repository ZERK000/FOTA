/*
 * SPI_Private.h
 *
 *  Created on: Jul 29, 2025
 *      Author: Ziad
 */

#ifndef SPI_PRIVATE_H_
#define SPI_PRIVATE_H_


#define SPI1_BASE  0x40013000
#define SPI2_BASE  0x40003800

typedef struct
{
	 u32 CR1;
	 u32 CR2;
	 u32 SR;
	 u32 DR;
	 u32 CRCPR;
	 u32 RXCRCR;
	 u32 TXCRCR;
	 u32 I2SCFGR;
	 u32 I2SPR;
} SPI_t;

#define SPI1   ((volatile SPI_t *) SPI1_BASE)
#define SPI2   ((volatile SPI_t *) SPI2_BASE)



#endif /* SPI_PRIVATE_H_ */
