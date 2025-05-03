// ds3231.c
#include "ds3231.h"
#include "stm32f4xx_hal.h"

// I2C handle (defined in main code for I2C2)
extern I2C_HandleTypeDef hi2c1;

// DS3231 I2C address (8-bit, write mode = 0x68<<1)
#define DS3231_ADDRESS  (0xD0)
// Register address of the first time byte (seconds)
#define DS3231_REG_TIME 0x00

// Convert a decimal value (0-99) to BCD (e.g. 45 -> 0x45)
static uint8_t decToBcd(uint8_t val) {
    return (uint8_t)(((val / 10) << 4) | (val % 10));
}

// Convert BCD to decimal (e.g. 0x45 -> 45)
static uint8_t bcdToDec(uint8_t val) {
    return (uint8_t)(((val >> 4) * 10) + (val & 0x0F));
}

/**
 * @brief  Set the DS3231 time registers over I2C.
 */
void DS3231_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds,
                    uint8_t day, uint8_t date, uint8_t month, uint8_t year)
{
    // Time and date to write, in BCD
    uint8_t data[7];
    data[0] = decToBcd(seconds);
    data[1] = decToBcd(minutes);
    data[2] = decToBcd(hours);
    data[3] = decToBcd(day);
    data[4] = decToBcd(date);
    data[5] = decToBcd(month);
    data[6] = decToBcd(year);

    // Write 7 bytes starting at register 0x00
    HAL_I2C_Mem_Write(&hi2c1, DS3231_ADDRESS, DS3231_REG_TIME,
                      I2C_MEMADD_SIZE_8BIT, data, 7, HAL_MAX_DELAY);
}

/**
 * @brief  Read the DS3231 time registers and return as DS3231_Time struct.
 */
DS3231_Time DS3231_GetTime(void)
{
    DS3231_Time t;
    uint8_t data[7];

    // Read 7 bytes from register 0x00 (seconds through year)
    HAL_I2C_Mem_Read(&hi2c1, DS3231_ADDRESS, DS3231_REG_TIME,
                     I2C_MEMADD_SIZE_8BIT, data, 7, HAL_MAX_DELAY);

    // Convert BCD to decimal and mask out control bits if any
    t.second = bcdToDec(data[0] & 0x7F);      // bit7 is Oscillator Stop Flag (OSF)
    t.minute = bcdToDec(data[1] & 0x7F);
    t.hour   = bcdToDec(data[2] & 0x3F);      // mask off 12/24h bit (assuming 24h mode)
    t.day    = bcdToDec(data[3] & 0x07);      // day-of-week is 1-7 (ignore upper bits)
    t.date   = bcdToDec(data[4] & 0x3F);      // date (1-31)
    t.month  = bcdToDec(data[5] & 0x1F);      // month (1-12, ignore century bit)
    t.year   = bcdToDec(data[6]);             // year (00-99)
    return t;
}
