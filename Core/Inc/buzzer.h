/* buzzer.h */
#ifndef BUZZER_H
#define BUZZER_H

#include "stm32f4xx_hal.h"  // Change to your series (stm32f1xx_hal.h, etc.)

// Externally defined timer handle (configured in CubeMX for TIM3 Channel 1 PWM)
extern TIM_HandleTypeDef htim3;

/**
 * @brief  Initialize the buzzer PWM (starts TIM3 CH1 PWM with 0% duty).
 * @note   Timer 3 must be configured in CubeMX: PWM Generation CH1, Internal Clock.
 */
void Buzzer_Init(void);

/**
 * @brief  Play a tone on the buzzer using PWM.
 * @param  frequency      Tone frequency in Hz (e.g. 2000 for 2 kHz).
 * @param  duty_cycle     Duty cycle in percent (0 to 100).
 */
void Buzzer_Play(uint32_t frequency, uint8_t duty_cycle);

/**
 * @brief  Stop the buzzer (stops PWM output).
 */
void Buzzer_Stop(void);

#endif // BUZZER_H
