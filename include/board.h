/**
 * @file  board.h
 * @brief Pin assignment for the NUCLEO-F103RB wiring.
 */
#ifndef BOARD_H
#define BOARD_H

#include "stm32f1xx.h"

/* Seven-segment display: segments a..g on consecutive pins PC0..PC6. */
#define SEG7_PORT        GPIOC
#define SEG7_PORT_CLK_EN RCC_APB2ENR_IOPCEN
#define SEG7_FIRST_PIN   0U

/* Set to 0 for a common-cathode display (segments lit by logic high). */
#define SEG7_COMMON_ANODE 1

/* Quadrature encoder: channel A on PA8 (TIM1_CH1), channel B on PA9 (TIM1_CH2). */
#define ENCODER_PORT        GPIOA
#define ENCODER_PORT_CLK_EN RCC_APB2ENR_IOPAEN
#define ENCODER_PIN_A       8U
#define ENCODER_PIN_B       9U

#endif /* BOARD_H */
