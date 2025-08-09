#ifndef GPIO_PRIVATE_H
#define GPIO_PRIVATE_H

#include <STD_Types.h>

// Base addresses
#define GPIOA_BASE  0x40020000
#define GPIOB_BASE  0x40020400
#define GPIOC_BASE  0x40020800
#define GPIOD_BASE  0x40020C00
#define GPIOE_BASE  0x40021000
#define GPIOH_BASE  0x40021C00

typedef struct {
    volatile u32 MODER;    // 0x00
    volatile u32 OTYPER;   // 0x04
    volatile u32 OSPEEDR;  // 0x08
    volatile u32 PUPDR;    // 0x0C
    volatile u32 IDR;      // 0x10
    volatile u32 ODR;      // 0x14
    volatile u32 BSRR;     // 0x18
    volatile u32 LCKR;     // 0x1C
    volatile u32 AFRL;     // 0x20
    volatile u32 AFRH;     // 0x24
} GPIO_t;

// GPIO pointers
#define GPIOA   ((volatile GPIO_t*) GPIOA_BASE)
#define GPIOB   ((volatile GPIO_t*) GPIOB_BASE)
#define GPIOC   ((volatile GPIO_t*) GPIOC_BASE)
#define GPIOD   ((volatile GPIO_t*) GPIOD_BASE)
#define GPIOE   ((volatile GPIO_t*) GPIOE_BASE)
#define GPIOH   ((volatile GPIO_t*) GPIOH_BASE)

#endif
