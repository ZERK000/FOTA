#ifndef COMMON_MACROS_H
#define COMMON_MACROS_H

/* Set a certain bit in any register */
#define SET_BIT(REG,BIT) (REG|=(1<<BIT))

/* Clear a certain bit in any register */
#define CLEAR_BIT(REG,BIT) (REG&=(~(1<<BIT)))

/* Toggle a certain bit in any register */
#define TOGGLE_BIT(REG,BIT) (REG^=(1<<BIT))

/* Get a certain bit in any register */
#define GET_BIT(REG,BIT) (((REG) >> (BIT)) & 1)
#endif
