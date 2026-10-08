/**
 * @file  main.c
 * @brief Rotary encoder selects a hex digit (0..F) shown on a seven-segment display.
 */
#include <stdint.h>

#include "clock.h"
#include "encoder.h"
#include "seg7.h"

static uint8_t clamp_digit(int32_t value)
{
    if (value < 0) {
        return 0U;
    }
    if (value > (int32_t)SEG7_HEX_MAX) {
        return SEG7_HEX_MAX;
    }
    return (uint8_t)value;
}

int main(void)
{
    uint8_t digit = 0U;

    clock_init();
    seg7_init();
    encoder_init();

    seg7_show_hex(digit);

    for (;;) {
        int16_t delta = encoder_read_delta();
        if (delta == 0) {
            continue;
        }

        uint8_t next = clamp_digit((int32_t)digit + delta);
        if (next != digit) {
            digit = next;
            seg7_show_hex(digit);
        }
    }
}
