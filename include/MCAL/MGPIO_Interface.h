#ifndef GPIO_INTERFACE_H
#define GPIO_INTERFACE_H

#include "MCAL/MGPIO_Private.h"

// Ports

typedef enum {
	PORTA,
	PORTB,
	PORTC,
	PORTD,
	PORTE,
	PORTH
} Port_t;

// Pin modes
typedef enum {
	INPUT,
	OUTPUT,
	ALT_FUNCTION,
	ANALOG

} Mode_t;


// Output type
typedef enum {
	PUSH_PULL,
	OPEN_DRAIN
} OutputType_t;


// Pull-up/down
typedef enum {
	NO_PULL,
	PULL_UP,
	PULL_DOWN
}InputPull_t;

// speeds
typedef enum {
	LOW_SPEED,
	MEDIUM_SPEED,
	HIGH_SPEED,
	VERY_HIGH_SPEED
}Speed_t;

typedef enum{
	AF0,
	AF1,
	AF2,
	AF3,
	AF4,
	AF5,
	AF6,
	AF7,
	AF8,
	AF9,
	AF10,
	AF11,
	AF12,
	AF13,
	AF14,
	AF15
}AlternativeFunction_t;


// Pin states
#define LOW             0
#define HIGH            1

// API functions
void GPIO_PinMode(Port_t port, u8 pin, Mode_t mode);
void GPIO_OutputPinConfigure(Port_t port, u8 pin, OutputType_t type, Speed_t speed);
void GPIO_InputPinConfigure(Port_t port, u8 pin, InputPull_t pull);
void GPIO_SetPinValueAtomic(Port_t port,u8 pin, u8 value);
void GPIO_SetPinValue(Port_t port, u8 pin, u8 value);
u8   GPIO_GetPinValue(Port_t port, u8 pin);
void GPIO_SetAlternativeConfiguration(Port_t port, u8 pin, AlternativeFunction_t altFun );


#endif
