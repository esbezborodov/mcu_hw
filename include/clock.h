/**
 * @file  clock.h
 * @brief System clock configuration.
 */
#ifndef CLOCK_H
#define CLOCK_H

#define SYSCLK_HZ 64000000UL

/**
 * @brief Switch SYSCLK to the PLL driven by HSI/2: 8 MHz / 2 * 16 = 64 MHz.
 *
 * AHB and APB2 run at SYSCLK, APB1 at SYSCLK / 2 (32 MHz, its maximum is 36 MHz).
 */
void clock_init(void);

#endif /* CLOCK_H */
