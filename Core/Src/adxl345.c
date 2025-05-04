#include "adxl345.h"

extern I2C_HandleTypeDef hi2c1;  /* I2C1 handle (defined in main code) */

/* Write a single byte to an ADXL345 register */
static HAL_StatusTypeDef ADXL345_WriteRegister(uint8_t reg, uint8_t value) {
    return HAL_I2C_Mem_Write(&hi2c1, ADXL345_I2C_ADDR, reg,
                             I2C_MEMADD_SIZE_8BIT, &value, 1, HAL_MAX_DELAY);
}

/* Read a single byte from an ADXL345 register */
static HAL_StatusTypeDef ADXL345_ReadRegister(uint8_t reg, uint8_t *value) {
    return HAL_I2C_Mem_Read(&hi2c1, ADXL345_I2C_ADDR, reg,
                            I2C_MEMADD_SIZE_8BIT, value, 1, HAL_MAX_DELAY);
}

/* Initialize ADXL345: full-resolution ±2g, 100 Hz, measurement mode */
HAL_StatusTypeDef ADXL345_Init(void) {
    HAL_StatusTypeDef status;

    /* Set data format: FULL_RES=1, Range=±2g (0) */
    uint8_t dataFormat = ADXL345_FULL_RES | ADXL345_RANGE_2G;
    status = ADXL345_WriteRegister(ADXL345_REG_DATA_FORMAT, dataFormat);
    if (status != HAL_OK) return status;

    /* Set output data rate to 100 Hz (BW_RATE = 0x0A) */
    status = ADXL345_WriteRegister(ADXL345_REG_BW_RATE, 0x0A);
    if (status != HAL_OK) return status;

    /* Enable measurement mode (set Measure bit = 1 in POWER_CTL) */
    status = ADXL345_WriteRegister(ADXL345_REG_POWER_CTL, 0x08);
    return status;
}

/* Read X, Y, Z axis acceleration data (in raw ADC counts) */
HAL_StatusTypeDef ADXL345_ReadXYZ(int16_t *x, int16_t *y, int16_t *z) {
    uint8_t buffer[6];
    HAL_StatusTypeDef status;

    /* Read 6 bytes starting from DATAX0 (auto-increment on consecutive reads) */
    status = HAL_I2C_Mem_Read(&hi2c1, ADXL345_I2C_ADDR, ADXL345_REG_DATAX0,
                              I2C_MEMADD_SIZE_8BIT, buffer, 6, HAL_MAX_DELAY);
    if (status != HAL_OK) {
        return status;
    }

    /* Combine LSB and MSB for each axis (twos-complement) */
    *x = (int16_t)((uint16_t)buffer[1] << 8 | buffer[0]);  /* X-axis */
    *y = (int16_t)((uint16_t)buffer[3] << 8 | buffer[2]);  /* Y-axis */
    *z = (int16_t)((uint16_t)buffer[5] << 8 | buffer[4]);  /* Z-axis */
    return HAL_OK;
}
