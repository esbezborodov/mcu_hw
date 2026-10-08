/**
 * @file  gpio.h
 * @brief Minimal helpers for the STM32F1 GPIO configuration registers.
 */
#ifndef GPIO_H
#define GPIO_H

#include "stm32f1xx.h"

/* 4-bit CNF[1:0]:MODE[1:0] values written to GPIOx_CRL / GPIOx_CRH. */
typedef enum {
    GPIO_MODE_INPUT_FLOATING = 0x4U,  /* CNF = 01, MODE = 00 */
    GPIO_MODE_OUTPUT_PP_2MHZ = 0x2U,  /* CNF = 00, MODE = 10 */
    GPIO_MODE_OUTPUT_PP_50MHZ = 0x3U, /* CNF = 00, MODE = 11 */
} gpio_mode_t;

/**
 * @brief Configure a single pin (0..15) of @p port.
 */
static inline void gpio_configure(GPIO_TypeDef *port, unsigned pin, gpio_mode_t mode)
{
    volatile uint32_t *reg = (pin < 8U) ? &port->CRL : &port->CRH;
    unsigned shift = (pin % 8U) * 4U;

    *reg = (*reg & ~(0xFUL << shift)) | ((uint32_t)mode << shift);
}

#endif /* GPIO_H */
