/**
 * @file  encoder.h
 * @brief Quadrature encoder decoded in hardware by TIM1.
 */
#ifndef ENCODER_H
#define ENCODER_H

#include <stdint.h>

/**
 * @brief Configure the encoder pins and put TIM1 into encoder mode.
 */
void encoder_init(void);

/**
 * @brief Return the number of steps since the previous call.
 *
 * The hardware counter is never written after initialization, so no steps
 * are lost; the 16-bit wrap-around is handled by modular arithmetic as long
 * as the function is called more often than every 32767 steps.
 */
int16_t encoder_read_delta(void);

#endif /* ENCODER_H */
