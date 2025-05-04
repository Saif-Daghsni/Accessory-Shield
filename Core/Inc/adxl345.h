#ifndef ADXL345_I2C_H
#define ADXL345_I2C_H

#include "stm32f4xx_hal.h"
#include <stdint.h>

/* I2C address (7-bit << 1) for ADXL345 with SDO/ALT = 0 (i.e. 0x53 << 1 = 0xA6) */
#define ADXL345_I2C_ADDR         (0x53 << 1)

/* ADXL345 register addresses */
#define ADXL345_REG_DEVID        0x00  /* Device ID (should read 0xE5) */
#define ADXL345_REG_THRESH_TAP   0x1D
#define ADXL345_REG_OFSX         0x1E
#define ADXL345_REG_OFSY         0x1F
#define ADXL345_REG_OFSZ         0x20
#define ADXL345_REG_DUR          0x21
#define ADXL345_REG_LATENT       0x22
#define ADXL345_REG_WINDOW       0x23
#define ADXL345_REG_THRESH_ACT   0x24
#define ADXL345_REG_THRESH_INACT 0x25
#define ADXL345_REG_TIME_INACT   0x26
#define ADXL345_REG_ACT_INACT_CTL 0x27
#define ADXL345_REG_THRESH_FF    0x28
#define ADXL345_REG_TIME_FF      0x29
#define ADXL345_REG_TAP_AXES     0x2A
#define ADXL345_REG_ACT_TAP_STATUS 0x2B
#define ADXL345_REG_BW_RATE      0x2C  /* Data rate and power mode */
#define ADXL345_REG_POWER_CTL    0x2D  /* Power-saving control */
#define ADXL345_REG_INT_ENABLE   0x2E
#define ADXL345_REG_INT_MAP      0x2F
#define ADXL345_REG_INT_SOURCE   0x30
#define ADXL345_REG_DATA_FORMAT  0x31  /* Data format (range, resolution) */
#define ADXL345_REG_DATAX0       0x32  /* X-Axis Data 0 (LSB) */
#define ADXL345_REG_DATAX1       0x33  /* X-Axis Data 1 (MSB) */
#define ADXL345_REG_DATAY0       0x34  /* Y-Axis Data 0 */
#define ADXL345_REG_DATAY1       0x35  /* Y-Axis Data 1 */
#define ADXL345_REG_DATAZ0       0x36  /* Z-Axis Data 0 */
#define ADXL345_REG_DATAZ1       0x37  /* Z-Axis Data 1 */
#define ADXL345_REG_FIFO_CTL     0x38
#define ADXL345_REG_FIFO_STATUS  0x39

/* Data Format bits */
#define ADXL345_FULL_RES         0x08  /* Full resolution (4 mg/LSB) */
#define ADXL345_RANGE_2G         0x00  /* ±2g range */
#define ADXL345_RANGE_4G         0x01  /* ±4g range */
#define ADXL345_RANGE_8G         0x02  /* ±8g range */
#define ADXL345_RANGE_16G        0x03  /* ±16g range */

/* Function prototypes */
HAL_StatusTypeDef ADXL345_Init(void);
HAL_StatusTypeDef ADXL345_ReadXYZ(int16_t *x, int16_t *y, int16_t *z);

#endif  /* ADXL345_I2C_H */
