#ifndef MFLASH_INTERFACE_H
#define MFLASH_INTERFACE_H


typedef enum {
    FLASH_SECTOR_0,
    FLASH_SECTOR_1,
    FLASH_SECTOR_2,
    FLASH_SECTOR_3,
    FLASH_SECTOR_4,
    FLASH_SECTOR_5,
    FLASH_SECTOR_6,
    FLASH_SECTOR_7
} FlashSector_t;

void MFLASH_voidUnlock(void);
void MFLASH_voidLock(void);
void MFLASH_voidEraseSector(FlashSector_t Copy_uddtSector);
u32 MFLASH_u32ReadWord(u32 Copy_u32Address);
void MFLASH_voidMassErase(void);
u8 MFLASH_u8VerifyProgramming(u32 Copy_u32Address, u32 Copy_u32ExpectedData);
void MFLASH_voidMultipleSectorsErase(u8 Copy_u8StartSector, u8 Copy_u8EndSector);
void FLASH_voidFlashProgram(u32 Address,u16* Data, u8 DataLength);



#endif
