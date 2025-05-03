#include "potentiometer.h"

void POT_Init(Potentiometer* pot, ADC_HandleTypeDef* hadc, uint32_t channel) {
    pot->hadc = hadc;
    pot->channel = channel;
    pot->max_adc_value = 4095; // Assuming 12-bit ADC
}

uint32_t POT_ReadRaw(Potentiometer* pot) {
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = pot->channel;
    sConfig.Rank = 1;
    sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;

    HAL_ADC_ConfigChannel(pot->hadc, &sConfig);
    HAL_ADC_Start(pot->hadc);
    HAL_ADC_PollForConversion(pot->hadc, HAL_MAX_DELAY);
    return HAL_ADC_GetValue(pot->hadc);
}

uint8_t POT_ReadPercent(Potentiometer* pot) {
    uint32_t raw = POT_ReadRaw(pot);
    return (raw * 100) / pot->max_adc_value;
}

uint32_t POT_MapToRange(Potentiometer* pot, uint32_t min, uint32_t max) {
    uint32_t raw = POT_ReadRaw(pot);
    return (raw * (max - min)) / pot->max_adc_value + min;
}
