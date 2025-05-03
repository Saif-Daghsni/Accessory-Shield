// ds3231.h
#ifndef DS3231_H
#define DS3231_H

#include <stdint.h>

// DS3231 time structure (all fields in normal decimal, not BCD)
typedef struct {
    uint8_t second;   // 0-59
    uint8_t minute;   // 0-59
    uint8_t hour;     // 0-23
    uint8_t day;      // 1-7 (day of week, e.g. 1=Monday)
    uint8_t date;     // 1-31 (day of month)
    uint8_t month;    // 1-12
    uint8_t year;     // 0-99 (year since 2000)
} DS3231_Time;

/**
 * @brief Set the RTC time.
 * @param hours    Hours (0-23)
 * @param minutes  Minutes (0-59)
 * @param seconds  Seconds (0-59)
 * @param day      Day of week (1-7, e.g. 1=Monday)
 * @param date     Date (1-31)
 * @param month    Month (1-12)
 * @param year     Year (00-99, last two digits)
 */
void DS3231_SetTime(uint8_t hours, uint8_t minutes, uint8_t seconds,
                    uint8_t day, uint8_t date, uint8_t month, uint8_t year);

/**
 * @brief Get the current RTC time.
 * @return DS3231_Time struct with second, minute, hour, day, date, month, year filled in.
 */
DS3231_Time DS3231_GetTime(void);

#endif // DS3231_H
