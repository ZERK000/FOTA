#include "STD_TYPES.h"
#include "CommonMacros.h"
#include "MCAL/MFLASH_Interface.h"
#include "MCAL/MFLASH_Private.h"

#define __IO volatile


void MFLASH_voidUnlock(void)
{
    /* Write KEY1 to FLASH_KEYR */
    FLASH->KEYR = FLASH_KEY1;

    /* Write KEY2 to FLASH_KEYR */
    FLASH->KEYR = FLASH_KEY2;
}

void MFLASH_voidLock(void)
{
    /* Set LOCK bit */
    SET_BIT(FLASH->CR, FLASH_CR_LOCK);
}

void MFLASH_voidEraseSector(FlashSector_t Copy_uddtSector)
{
    /* Wait for any ongoing operation */
    while(GET_BIT(FLASH->SR, FLASH_SR_BSY));

    /* Set SER bit and select sector */
    MODIFY_REG(FLASH->CR, (0xF << FLASH_CR_SNB), (Copy_uddtSector << FLASH_CR_SNB));
    SET_BIT(FLASH->CR, FLASH_CR_SER);

    /* Start erase operation */
    SET_BIT(FLASH->CR, FLASH_CR_STRT);

    /* Wait for completion */
    while(GET_BIT(FLASH->SR, FLASH_SR_BSY));

    /* Clear SER bit */
    CLR_BIT(FLASH->CR, FLASH_CR_SER);
}

void FLASH_voidFlashProgram(u32 Address,u16* Data, u8 DataLength)
{
	while(GET_BIT(FLASH->SR,FLASH_SR_BSY) == 1);
	// unlock CR regs
	if(GET_BIT(FLASH->CR,FLASH_CR_LOCK) == 1)
	{
		FLASH->KEYR = FLASH_KEY1;
		FLASH->KEYR = FLASH_KEY2;
	}

	FLASH->CR &= ~(MUSK_SIZE<<FLASH_CR_PSIZE);
	FLASH->CR |= (1<<FLASH_CR_PSIZE);

	for (u8 i =0; i<DataLength; i++ )
	{
		// Select Program modes
		FLASH->CR |=(1<<FLASH_CR_PG);
        *((volatile u16*) Address) = Data[i];
		Address +=2;

		while(GET_BIT(FLASH->SR,FLASH_SR_BSY) == 1);
		FLASH->CR &= ~(1<<FLASH_CR_PG);
	}


}

u32 MFLASH_u32ReadWord(u32 Copy_u32Address)
{
    return (*(__IO u32*)Copy_u32Address);
}

u8 MFLASH_u8VerifyProgramming(u32 Copy_u32Address, u32 Copy_u32ExpectedData)
{
    u32 Local_u32ReadData = MFLASH_u32ReadWord(Copy_u32Address);
    return (Local_u32ReadData == Copy_u32ExpectedData) ? 1 : 0;
}

void MFLASH_voidMassErase(void)
{
    // Wait for any ongoing operation to complete
    while(GET_BIT(FLASH->SR, FLASH_SR_BSY));

    // Unlock the flash control register
    MFLASH_voidUnlock();

    // Set the Mass Erase bit
    SET_BIT(FLASH->CR, FLASH_CR_MER);

    // Start the erase operation
    SET_BIT(FLASH->CR, FLASH_CR_STRT);

    // Wait for the operation to complete
    while(GET_BIT(FLASH->SR, FLASH_SR_BSY));

    // Clear the Mass Erase bit
    CLR_BIT(FLASH->CR, FLASH_CR_MER);

    // Lock the flash
  //  MFLASH_voidLock();
}


void MFLASH_voidMultipleSectorsErase(u8 Copy_u8StartSector, u8 Copy_u8EndSector)
{
    /* Unlock the flash first (only once for all sectors) */
    MFLASH_voidUnlock();

    /* Clear any previous errors */
    FLASH->SR = (FLASH_SR_OPERR | FLASH_SR_WRPERR |
                FLASH_SR_PGAERR | FLASH_SR_PGPERR | FLASH_SR_PGSERR);

    /* Erase each sector in sequence */
    for(u8 Local_u8Sector = Copy_u8StartSector;
        Local_u8Sector <= Copy_u8EndSector;
        Local_u8Sector++)
    {
        MFLASH_voidEraseSector((FlashSector_t)Local_u8Sector);
    }

    /* Lock the flash when done */
    //MFLASH_voidLock();
}
