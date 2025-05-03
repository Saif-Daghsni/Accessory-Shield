#ifndef LM75_H
#define LM75_H

#include "stm32f4xx_hal.h"

// LM75 I2C address
#define LM75_I2C_ADDR 0x90  // 8-bit address for LM75 (0x48 << 1)

// LM75 Registers
#define LM75_TEMP_REG   0x00   // Temperature Register
#define LM75_CONF_REG   0x01   // Configuration Register
#define LM75_THYST_REG  0x02   // Hysteresis Register
#define LM75_TOS_REG    0x03   // Overtemperature Shutdown Register

// Function Prototypes
HAL_StatusTypeDef LM75_Init(I2C_HandleTypeDef *hi2c);
float LM75_ReadTemperature(I2C_HandleTypeDef *hi2c);
HAL_StatusTypeDef LM75_SetConfig(I2C_HandleTypeDef *hi2c, uint8_t config);

#endif /* LM75_H */
