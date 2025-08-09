#include <MCAL/MGPIO_Interface.h>
#include <MCAL/MGPIO_Private.h>


static volatile GPIO_t* GPIO_GetPort(Port_t port)
{
    switch (port)
    {
        case PORTA: return GPIOA;
        case PORTB: return GPIOB;
        case PORTC: return GPIOC;
        case PORTD: return GPIOD;
        case PORTE: return GPIOE;
        case PORTH: return GPIOH;
        default:    return GPIOA;
    }
}

void GPIO_PinMode(Port_t port, u8 pin, Mode_t mode)
{
    volatile GPIO_t* GPIOx = GPIO_GetPort(port);
    GPIOx->MODER &= ~(0x3 << (pin * 2));         // Clear
    GPIOx->MODER |=  ((mode & 0x3) << (pin * 2)); // Set
}


void GPIO_OutputPinConfigure(Port_t port, u8 pin, OutputType_t type, Speed_t speed)
{
    volatile GPIO_t* GPIOx = GPIO_GetPort(port);

    // Output type (push-pull / open-drain)
    GPIOx->OTYPER &= ~(1 << pin);
    GPIOx->OTYPER |=  ((type & 0x1) << pin);

    // Output speed
    GPIOx->OSPEEDR &= ~(0x3 << (pin * 2));
    GPIOx->OSPEEDR |=  ((speed & 0x3) << (pin * 2));
}

void GPIO_InputPinConfigure(Port_t port, u8 pin, InputPull_t pull)
{
    volatile GPIO_t* GPIOx = GPIO_GetPort(port);
    GPIOx->PUPDR &= ~(0x3 << (pin * 2));
    GPIOx->PUPDR |=  ((pull & 0x3) << (pin * 2));
}


void GPIO_SetAlternativeConfiguration(Port_t port, u8 pin, AlternativeFunction_t altFun)
{
    volatile GPIO_t* GPIOx = GPIO_GetPort(port);

    if (pin <= 7)
    {
        GPIOx->AFRL &= ~(0xF << (pin * 4));            // Clear
        GPIOx->AFRL |=  ((altFun & 0xF) << (pin * 4));  // Set
    }
    else if (pin <= 15)
    {
        u8 shift = pin - 8;
        GPIOx->AFRH &= ~(0xF << (shift * 4));
        GPIOx->AFRH |=  ((altFun & 0xF) << (shift * 4));
    }
}

void GPIO_SetPinValueAtomic(Port_t port, u8 pin, u8 value)
{
	u16 PinPosition = 1 << pin;
    volatile GPIO_t* GPIOx = GPIO_GetPort(port);
    if (value == HIGH)
        GPIOx->BSRR = PinPosition;         // Set bit
    else{
    	PinPosition = PinPosition << 16;
    	GPIOx->BSRR = PinPosition;  // Reset bit
    }

}

void GPIO_SetPinValue(Port_t port, u8 pin, u8 value)
{
    volatile GPIO_t* GPIOx = GPIO_GetPort(port);
    if (value == HIGH)
        GPIOx->ODR |=  (1 << pin);
    else
        GPIOx->ODR &= ~(1 << pin);
}


u8 GPIO_GetPinValue(Port_t port, u8 pin)
{
    volatile GPIO_t* GPIOx = GPIO_GetPort(port);
    return (u8)((GPIOx->IDR >> pin) & 0x1);
}

