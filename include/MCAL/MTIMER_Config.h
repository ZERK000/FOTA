/*
 * MTIMER_Config.h
 *
 *  Created on: Jul 30, 2025
 *      Author: Catherine Nader
 */

#ifndef MTIMER_CONFIG_H_
#define MTIMER_CONFIG_H_

/*-----------------------------------------
 * Timer Configuration Options
 *----------------------------------------*/

/*
 * One Pulse Mode:
 * ENABLE  - Timer stops automatically after one update event
 * DISABLE - Timer runs continuously
 */
#define OnePulseMode DISABLE

/*
 * Counter Direction:
 * UP   - Up-counting mode
 * DOWN - Down-counting mode
 */
#define DIR UP

/*
 * Clock Division:
 * DIV1 - No division
 * DIV2 - Clock divided by 2
 * DIV4 - Clock divided by 4
 */
#define DIV DIV1

/*-----------------------------------------
 * Channel Enable Configuration
 *----------------------------------------*/

/*
 * Enable or disable each channel individually
 * Options: ENABLE / DISABLE
 */
#define CHANNEL1E ENABLE
#define CHANNEL2E DISABLE
#define CHANNEL3E DISABLE
#define CHANNEL4E DISABLE

/*-----------------------------------------
 * Channel Mode Configuration
 *----------------------------------------*/

/*
 * Channel Modes:
 * OUTPUT_TIMER     - Channel configured as output
 * INPUT_TIMER      - Input capture from its own input (e.g., CH1 -> TI1)
 * INPUT_CC   - Cross-channel input capture (e.g., CH1 -> TI2)
 * INPUT_TRC  - Mapped to the internal trigger (TRC)
 */
#define Ch1M INPUT_TIMER
#define Ch2M OUTPUT_TIMER
#define Ch3M OUTPUT_TIMER
#define Ch4M OUTPUT_TIMER

/*-----------------------------------------
 * Input Edge Detection
 *----------------------------------------*/

/*
 * Input Capture Edge Sensitivity:
 * FALLINGE - Trigger on falling edge
 * RISINGE  - Trigger on rising edge
 * BOTHE    - Trigger on both edges
 */
#define EDGEST BOTHE

/*-----------------------------------------
 * Future Configurable Fields:
 *-----------------------------------------
 * - Input filter configuration
 * - Input prescaler per channel
 * - Dead-time and break features (advanced timers)
 */

#endif /* MTIMER_CONFIG_H_ */
