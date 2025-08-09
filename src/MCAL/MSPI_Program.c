/*
 * SPI_Program.c
 *
 *  Created on: Jul 29, 2025
 *      Author: Ziad
 */


#include "STD_TYPES.h"
#include "CommonMacros.h"
#include <MCAL/MGPIO_Interface.h>
#include <MCAL/MSPI_Config.h>
#include <MCAL/MSPI_Interface.h>


void SPI_voidInit(void)
{
//
	// SCK - PA5
	GPIO_PinMode(SPI_PORT, SCK_PIN, ALT_FUNCTION);
	GPIO_SetAlternativeConfiguration(SPI_PORT, SCK_PIN, AF5);

	// MOSI - PA7
	GPIO_PinMode(SPI_PORT, MOSI_PIN, ALT_FUNCTION);
	GPIO_SetAlternativeConfiguration(SPI_PORT, MOSI_PIN, AF5);

	// MISO - PA6
//	GPIO_PinMode(SPI_PORT, MISO_PIN, ALT_FUNCTION);
//	GPIO_SetAlternativeConfiguration(SPI_PORT, MISO_PIN, AF5);

//	if(!SPI_SSM_ENABLE)
//	{
//		GPIO_PinMode(SPI_PORT,NSS_PIN,OUTPUT);
//		GPIO_OutputPinConfigure(SPI_PORT,NSS_PIN,PUSH_PULL,HIGH_SPEED);
//		GPIO_SetPinValue(SPI_PORT,NSS_PIN,LOW);
//	}

	SPI->CR1 = 0;

	// Set Mode
	SPI->CR1 |= (SPI_MODE << 2); // MASTER or SLAVE

	// Baudrate
	SPI->CR1 |= SPI_BAUDRATE <<3;

	// Polarity and Phase
	SPI->CR1 |= (SPI_CPOL << 1); // CPOL
	SPI->CR1 |= (SPI_CPHA << 0);

	// Data Format
	SPI->CR1 |= (SPI_DFF << 11);

	// First bit
	SPI->CR1 |= (SPI_FIRST_BIT << 7);

	// Software slave management
	SPI->CR1 |= (SPI_SSM_ENABLE << 9); // SSM
	SPI->CR1 |= (SPI_SSM_ENABLE << 8); // SSI
	// Enable SPI
	SPI->CR1 |= (1 << 6); // SPE

}
void SPI_voidTransmit(u16 data)
{
	while (!(SPI->SR & (1 << 1))); // TXE
	SPI->DR = data;
	while (SPI->SR & (1 << 7));    // Wait for BSY to clear
}
u16   SPI_u16Receive()
{
	while (!(SPI->SR & (1 << 0))); // RXNE
	return (u16)SPI->DR;
}


void SPI_voidTransmitArray(u16 *arr, u32 len)
{
	for (u32 i = 0; i < len; ++i)
		SPI_voidTransmit(arr[i]);
}

u16 SPI_u16TransmitReceive(u16 data)
{
	while (!(SPI->SR & (1 << 1))); // TXE
	SPI->DR = data;
	while (!(SPI->SR & (1 << 0))); // RXNE
	return (u16)SPI->DR;
}


