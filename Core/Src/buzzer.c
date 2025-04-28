
/* buzzer.c */
#include "buzzer.h"

void Buzzer_Init(void) {
    // Start PWM with 0% duty cycle (silent)
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, 0);
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

void Buzzer_Play(uint32_t frequency, uint8_t duty_cycle) {
    // Calculate timer clock frequency (APB1 timer clocks)
    uint32_t timer_clk = HAL_RCC_GetPCLK1Freq();
    if ((RCC->CFGR & RCC_CFGR_PPRE1) != RCC_CFGR_PPRE1_DIV1) {
        timer_clk *= 2;  // APB1 prescaled
    }

    // Compute auto-reload value for desired frequency
    uint32_t arr = (timer_clk / frequency) - 1;

    // Update timer registers
    __HAL_TIM_SET_AUTORELOAD(&htim3, arr);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, ((arr + 1) * duty_cycle) / 100);

    // Force update event to reload ARR immediately
    HAL_TIM_GenerateEvent(&htim3, TIM_EVENTSOURCE_UPDATE);

    // Ensure PWM is running
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);
}

void Buzzer_Stop(void) {
    HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_1);
}
