#ifndef MFLASH_CONFIG_H
#define MFLASH_CONFIG_H

/* Flash programming parallelism configuration */
#define FLASH_PSIZE_X8      0
#define FLASH_PSIZE_X16     1
#define FLASH_PSIZE_X32     2
#define FLASH_PSIZE_X64     3

#define FLASH_PROGRAMMING_WIDTH  FLASH_PSIZE_X32

#endif
