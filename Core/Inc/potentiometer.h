#ifndef __POTENTIOMETER_H__
#define __POTENTIOMETER_H__

#include "stm32f4xx_hal.h"

typedef struct {
    ADC_HandleTypeDef* hadc;  // Pointer to the ADC handle
    uint32_t channel;         // ADC channel (e.g., ADC_CHANNEL_0)
    uint32_t max_adc_value;   // Usually 4095 for 12-bit resolution
} Potentiometer;

/**
 * @brief Initialize the potentiometer structure.
 *
 * @param pot Pointer to the Potentiometer structure
 * @param hadc ADC handle (e.g., &hadc1)
 * @param channel ADC channel used (e.g., ADC_CHANNEL_0)
 */
void POT_Init(Potentiometer* pot, ADC_HandleTypeDef* hadc, uint32_t channel);

/**
 * @brief Read the raw ADC value from the potentiometer.
 *
 * @param pot Pointer to the Potentiometer structure
 * @return uint32_t Raw ADC value (0–4095 for 12-bit)
 */
uint32_t POT_ReadRaw(Potentiometer* pot);

/**
 * @brief Read the potentiometer value scaled to 0–100.
 *
 * @param pot Pointer to the Potentiometer structure
 * @return uint8_t Scaled value (0–100)
 */
uint8_t POT_ReadPercent(Potentiometer* pot);

/**
 * @brief Map the potentiometer value to a custom range.
 *
 * @param pot Pointer to the Potentiometer structure
 * @param min Minimum value
 * @param max Maximum value
 * @return uint32_t Mapped value
 */
uint32_t POT_MapToRange(Potentiometer* pot, uint32_t min, uint32_t max);

#endif // __POTENTIOMETER_H__
