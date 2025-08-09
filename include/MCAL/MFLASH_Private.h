#ifndef MFLASH_PRIVATE_H
#define MFLASH_PRIVATE_H


#define FLASH_BASE_ADDRESS     0x40023C00

typedef struct {
    volatile u32 ACR;
    volatile u32 KEYR;
    volatile u32 OPTKEYR;
    volatile u32 SR;
    volatile u32 CR;
    volatile u32 OPTCR;
} FLASH_t;

#define FLASH ((volatile FLASH_t*)FLASH_BASE_ADDRESS)
#define MUSK_SIZE 3

/* CR Register Bits */
#define FLASH_CR_PG         0
#define FLASH_CR_SER        1
#define FLASH_CR_MER        2
#define FLASH_CR_SNB        3
#define FLASH_CR_PSIZE      8
#define FLASH_CR_STRT       16
#define FLASH_CR_LOCK       31

/* SR Register Bits */
#define FLASH_SR_EOP        0
#define FLASH_SR_OPERR      1
#define FLASH_SR_WRPERR     4
#define FLASH_SR_PGAERR     5
#define FLASH_SR_PGPERR     6
#define FLASH_SR_PGSERR     7
#define FLASH_SR_BSY        16


/* Keys */
#define FLASH_KEY1          0x45670123
#define FLASH_KEY2          0xCDEF89AB
#define FLASH_OPTKEY1       0x08192A3B
#define FLASH_OPTKEY2       0x4C5D6E7F

#endif
