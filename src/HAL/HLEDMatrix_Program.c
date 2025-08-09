#include "CommonMacros.h"
#include "STD_TYPES.h"
#include "HAL/HSTP_Interface.h"
#include "MCAL/MSystick_Interface.h"
#include "MCAL/MGPIO_Interface.h"
#include "HAL/HLEDMatrix_Config.h"
#include "HAL/HLEDMatrix_Interface.h"


// Shape definitions (8x8 arrays)
static const u8 TRIANGLE[] = {
    0x00, 0x00, 0x10, 0x38, 0x7C, 0xFE, 0x00, 0x00
};

static const u8 CIRCLE[] = {
    0x3C, 0x42, 0x81, 0x81, 0x81, 0x81, 0x42, 0x3C
};

static const u8 SAD_FACE[] = {
    0x3C, 0x42, 0xA5, 0x81, 0x99, 0x42, 0x3C, 0x00
};

static const u8 HAPPY_FACE[] = {
    0x3C, 0x42, 0xA5, 0x81, 0x81, 0x99, 0x42, 0x3C
};

static void Column_STP_Shift(u8 data)
{
    for(s8 i = 7; i >= 0; i--) {
        GPIO_SetPinValue(COL_STP_PORT, COL_STP_SDI_PIN, GET_BIT(data, i));

        // Pulse shift clock
        GPIO_SetPinValue(COL_STP_PORT, COL_STP_SHCP_PIN, HIGH);
        MSTK_voidDelayus(1);
        GPIO_SetPinValue(COL_STP_PORT, COL_STP_SHCP_PIN, LOW);
    }
}

static void Column_STP_Latch(void)
{
    GPIO_SetPinValue(COL_STP_PORT, COL_STP_STCP_PIN, HIGH);
    MSTK_voidDelayus(1);
    GPIO_SetPinValue(COL_STP_PORT, COL_STP_STCP_PIN, LOW);
}

void LEDMatrix_Init()
{
    // Initialize both STP interfaces using your GPIO driver
    GPIO_PinMode(COL_STP_PORT, COL_STP_SDI_PIN, OUTPUT);
    GPIO_PinMode(COL_STP_PORT, COL_STP_SHCP_PIN, OUTPUT);
    GPIO_PinMode(COL_STP_PORT, COL_STP_STCP_PIN, OUTPUT);

    GPIO_OutputPinConfigure(COL_STP_PORT, COL_STP_SDI_PIN, PUSH_PULL, LOW_SPEED);
    GPIO_OutputPinConfigure(COL_STP_PORT, COL_STP_SHCP_PIN, PUSH_PULL, LOW_SPEED);
    GPIO_OutputPinConfigure(COL_STP_PORT, COL_STP_STCP_PIN, PUSH_PULL, LOW_SPEED);

    // Initialize with all columns OFF (active low)
    Column_STP_Shift(0xFF);
    Column_STP_Latch();
}

void LEDMatrix_Display(u8* frame)
{
    for(u8 col = 0; col < 8; col++) {
        // 1. Disable all columns (active low)
        Column_STP_Shift(0xFF);
        Column_STP_Latch();

        // 2. Set row data via your original HSTP driver
        HSTP_voidShiftData(frame[col]);
        HSTP_voidSendData();

        // 3. Enable only current column
        Column_STP_Shift(~(1 << col));
        Column_STP_Latch();

        // 4. Display delay using your SYSTICK driver
        MSTK_voidDelayus(2500);
    }
}

// Shape display functions
void Display_Triangle() {
    LEDMatrix_Display((u8*)TRIANGLE);
}

void Display_Circle() {
    LEDMatrix_Display((u8*)CIRCLE);
}

void Display_SadFace() {
    LEDMatrix_Display((u8*)SAD_FACE);
}

void Display_HappyFace() {
    LEDMatrix_Display((u8*)HAPPY_FACE);
}
