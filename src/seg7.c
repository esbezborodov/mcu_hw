/**
 * @file  seg7.c
 * @brief Single-digit seven-segment display driver.
 *
 *      a
 *     ---
 *  f |   | b
 *     -g-
 *  e |   | c
 *     ---
 *      d
 */
#include "seg7.h"

#include "board.h"
#include "gpio.h"

#define SEG_A (1U << 0)
#define SEG_B (1U << 1)
#define SEG_C (1U << 2)
#define SEG_D (1U << 3)
#define SEG_E (1U << 4)
#define SEG_F (1U << 5)
#define SEG_G (1U << 6)

#define SEG7_SEGMENT_COUNT 7U
#define SEG7_ALL_SEGMENTS  ((1U << SEG7_SEGMENT_COUNT) - 1U)

/* Lit segments for each hex digit (bit set = segment on). */
static const uint8_t hex_glyphs[SEG7_HEX_MAX + 1U] = {
    [0x0] = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F,
    [0x1] = SEG_B | SEG_C,
    [0x2] = SEG_A | SEG_B | SEG_D | SEG_E | SEG_G,
    [0x3] = SEG_A | SEG_B | SEG_C | SEG_D | SEG_G,
    [0x4] = SEG_B | SEG_C | SEG_F | SEG_G,
    [0x5] = SEG_A | SEG_C | SEG_D | SEG_F | SEG_G,
    [0x6] = SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
    [0x7] = SEG_A | SEG_B | SEG_C,
    [0x8] = SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
    [0x9] = SEG_A | SEG_B | SEG_C | SEG_D | SEG_F | SEG_G,
    [0xA] = SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G,
    [0xB] = SEG_C | SEG_D | SEG_E | SEG_F | SEG_G,
    [0xC] = SEG_A | SEG_D | SEG_E | SEG_F,
    [0xD] = SEG_B | SEG_C | SEG_D | SEG_E | SEG_G,
    [0xE] = SEG_A | SEG_D | SEG_E | SEG_F | SEG_G,
    [0xF] = SEG_A | SEG_E | SEG_F | SEG_G,
};

static void write_segments(uint8_t lit)
{
    uint32_t high = SEG7_COMMON_ANODE ? (~lit & SEG7_ALL_SEGMENTS) : lit;
    uint32_t low = ~high & SEG7_ALL_SEGMENTS;

    /* BSRR updates only the display pins, atomically, leaving the rest of the port intact. */
    SEG7_PORT->BSRR = (high << SEG7_FIRST_PIN) | (low << (SEG7_FIRST_PIN + 16U));
}

void seg7_init(void)
{
    RCC->APB2ENR |= SEG7_PORT_CLK_EN;

    write_segments(0U);
    for (unsigned i = 0; i < SEG7_SEGMENT_COUNT; i++) {
        gpio_configure(SEG7_PORT, SEG7_FIRST_PIN + i, GPIO_MODE_OUTPUT_PP_2MHZ);
    }
}

void seg7_show_hex(uint8_t digit)
{
    write_segments(digit <= SEG7_HEX_MAX ? hex_glyphs[digit] : 0U);
}
