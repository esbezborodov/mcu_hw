#ifndef __MAIN_H
#define	__MAIN_H

#include "stm32f1xx.h"
#include "stdbool.h"
#include "string.h"
#include "stdio.h"

typedef struct {
	uint8_t indicator;
	uint8_t counter;
} device_t;

#define PRINT_0  (0b1000000)  // A,B,C,D,E,F
#define PRINT_1  (0b1111001) // B,C
#define PRINT_2  (0b0100100) // A,B,D,E,G
#define PRINT_3  (0b0110000) // A,B,C,D,G
#define PRINT_4  (0b0011001) // B,C,F,G
#define PRINT_5  (0b0010010) // A,C,D,F,G
#define PRINT_6  (0b0000010) // A,C,D,E,F,G
#define PRINT_7  (0b1111000) // A,B,C
#define PRINT_8  (0b0000000) // A,B,C,D,E,F,G
#define PRINT_9  (0b0010000) // A,B,C,D,F,G
#define PRINT_A  (0b0001000) // A,B,C,E,F,G
#define PRINT_B  (0b0000011) // C,D,E,F,G
#define PRINT_C  (0b1000110) // A,D,E,F
#define PRINT_D  (0b0100001) // B,C,D,E,G
#define PRINT_E  (0b0000110) // A,D,E,F,G
#define PRINT_F  (0b0001110) // A,E,F,G

void device_init(device_t* state);
void device_read(device_t* state);
void device_print(device_t* state);

void clk_init(void);

#endif
