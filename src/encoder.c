/**
 * @file  encoder.c
 * @brief Quadrature encoder decoded in hardware by TIM1.
 */
#include "encoder.h"

#include "board.h"
#include "gpio.h"

/* Input filter: sample at f_CK_INT, 8 consecutive equal samples (IC1F/IC2F = 0011).
 * Suppresses contact bounce of mechanical encoders. */
#define ENCODER_FILTER 0x3UL

static uint16_t last_count;

void encoder_init(void)
{
    RCC->APB2ENR |= ENCODER_PORT_CLK_EN | RCC_APB2ENR_TIM1EN;

    gpio_configure(ENCODER_PORT, ENCODER_PIN_A, GPIO_MODE_INPUT_FLOATING);
    gpio_configure(ENCODER_PORT, ENCODER_PIN_B, GPIO_MODE_INPUT_FLOATING);

    /* CC1/CC2 as inputs mapped on TI1/TI2, both filtered. */
    TIM1->CCMR1 = TIM_CCMR1_CC1S_0 | TIM_CCMR1_CC2S_0 | (ENCODER_FILTER << TIM_CCMR1_IC1F_Pos) |
                  (ENCODER_FILTER << TIM_CCMR1_IC2F_Pos);

    /* Non-inverted polarity on both channels. */
    TIM1->CCER &= ~(TIM_CCER_CC1P | TIM_CCER_CC2P);

    /* Encoder mode 1 (x2 resolution): count edges of one channel, the other gives direction. */
    TIM1->SMCR = (TIM1->SMCR & ~TIM_SMCR_SMS) | TIM_SMCR_SMS_0;

    /* Use the full 16-bit range; the position is tracked as a delta. */
    TIM1->ARR = 0xFFFFU;
    TIM1->CNT = 0U;
    last_count = 0U;

    TIM1->CR1 |= TIM_CR1_CEN;
}

int16_t encoder_read_delta(void)
{
    uint16_t count = (uint16_t)TIM1->CNT;
    int16_t delta = (int16_t)(uint16_t)(count - last_count);

    last_count = count;
    return delta;
}
