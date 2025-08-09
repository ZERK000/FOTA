/*
 * WiFi_Program.c
 *
 *  Created on: Jul 27, 2025
 *      Author: Ziad
 */


#include "STD_TYPES.h"
#include "CommonMacros.h"
#include <MCAL/MUART_Interface.h>

void WiFi_voidInit()
{
	do
	{
		// Turn off echo
		UART_voidSendString("ATE0\r\n");
	}while(UART_u8Receive() == "ERROR");

	do
	{
		// Turn off echo
		UART_voidSendString("AT+CWMODE=1\r\n");
	}while(UART_u8Receive() == "ERROR");

		// Station Mode

}

void ConnectToAccessPoint(u8* Name, u8* Password)
{
	do
	{
		UART_voidSendString("AT+CWJAP=\"");
		UART_voidSendString(Name);
		UART_voidSendString("\",\"");
		UART_voidSendString(Password);
		UART_voidSendString("\"\r\n");
	}while(UART_u8Receive() == "ERROR");

}

void WiFi_voidConnectServer(u8* Mode, u8* IPAddress, u8* Port)
{

}

void WiFi_voidHTTPRequest()
{

}
