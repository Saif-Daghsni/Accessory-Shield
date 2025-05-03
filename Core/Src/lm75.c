#include "lm75.h"

/**
 * @brief  Initializes the LM75 sensor.
 * @param  hi2c: I2C handle.
 * @retval HAL status.
 */
HAL_StatusTypeDef LM75_Init(I2C_HandleTypeDef *hi2c) {
    uint8_t config_data = 0x00;  // Default config (Continuous Conversion mode)
    return LM75_SetConfig(hi2c, config_data);
}

/**
 * @brief  Reads the temperature from the LM75 sensor.
 * @param  hi2c: I2C handle.
 * @retval Temperature in Celsius (float).
 */
float LM75_ReadTemperature(I2C_HandleTypeDef *hi2c) {
    uint8_t temp_data[2];
    HAL_StatusTypeDef status;

    // Read the temperature register (2 bytes)
    status = HAL_I2C_Mem_Read(hi2c, LM75_I2C_ADDR, LM75_TEMP_REG, I2C_MEMADD_SIZE_8BIT, temp_data, 2, HAL_MAX_DELAY);
    if (status != HAL_OK) {
        return -1;  // Error reading temperature
    }

    // Combine the two bytes to form the 16-bit temperature data
    int16_t temp_raw = (int16_t)((temp_data[0] << 8) | temp_data[1]);

    // Convert to Celsius
    return temp_raw / 256.0f;
}

/**
 * @brief  Configures the LM75 sensor (e.g., setting shutdown mode, resolution).
 * @param  hi2c: I2C handle.
 * @param  config: Configuration data (register value).
 * @retval HAL status.
 */
HAL_StatusTypeDef LM75_SetConfig(I2C_HandleTypeDef *hi2c, uint8_t config) {
    return HAL_I2C_Mem_Write(hi2c, LM75_I2C_ADDR, LM75_CONF_REG, I2C_MEMADD_SIZE_8BIT, &config, 1, HAL_MAX_DELAY);
}
