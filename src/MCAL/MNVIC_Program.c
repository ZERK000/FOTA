
#include "STD_TYPES.h"
#include "CommonMacros.h"
#include <MCAL/MNVIC_Config.h>
#include <MCAL/MNVIC_Interface.h>


void MNVIC_voidEnable(u8 Copy_u8Position)
{
	NVIC->ISER[Copy_u8Position/REG_DIV]|=(1<<(Copy_u8Position%REG_DIV));
}
void MNVIC_voidDisable(u8 Copy_u8Position)
{
	NVIC->ICER[Copy_u8Position/REG_DIV]|=(1<<(Copy_u8Position%REG_DIV));
}
void MNVIC_voidSetPendingFlag(u8 Copy_u8Position)
{
	NVIC->ISPR[Copy_u8Position/REG_DIV]|=(1<<(Copy_u8Position%REG_DIV));
}
void MNVIC_voidClearPendingFlag(u8 Copy_u8Position)
{
	NVIC->ICPR[Copy_u8Position/REG_DIV]|=(1<<(Copy_u8Position%REG_DIV));
}
u8 MNVIC_u8ReadingActiveState(u8 Copy_u8Position)
{
	return GET_BIT(NVIC->IABR[Copy_u8Position/REG_DIV],(Copy_u8Position%REG_DIV));
}

void MNVIC_voidSetGroupMode(NVIC_Group_t Copy_uddtGroupMode)
{
    // Clear PRIGROUP[10:8] and write the new value with the key
    SCB_AIRCR = VECTKEY | (Copy_uddtGroupMode << 8);
}


void MNVIC_voidSetInterruptPriority(u8 Copy_u8Position, u8 Copy_u8Group, u8 Copy_u8SubGroup)
{
    // Extract PRIGROUP from SCB->AIRCR to determine group/subgroup split
    u32 local_u32Group = (SCB_AIRCR >> 8) & 0x07;

    // Calculate the number of group and subpriority bits
    // Total priority bits STM32 supports = 4 (i.e. bits [7:4])
    u8 groupBits = 7 - local_u32Group;
    u8 subGroupBits = local_u32Group - 3;

    // Merge group & subgroup into a single priority value
    u8 priority = (Copy_u8Group << subGroupBits) | (Copy_u8SubGroup);

    // Write the priority to the IPR register (only upper 4 bits used)
    NVIC->IPR[Copy_u8Position] = (priority << 4); // shift left to align with bits [7:4]
}

