/**
 * @file  seg7.h
 * @brief Single-digit seven-segment display driver.
 */
#ifndef SEG7_H
#define SEG7_H

#include <stdint.h>

#define SEG7_HEX_MAX 0xFU

/**
 * @brief Configure the segment pins as outputs and blank the display.
 */
void seg7_init(void);

/**
 * @brief Show a hexadecimal digit. Values above 0xF blank the display.
 */
void seg7_show_hex(uint8_t digit);

#endif /* SEG7_H */
