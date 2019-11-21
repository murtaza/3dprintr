#ifndef UART_H
#define UART_H

#include "driverlib/driverlib.h"
#include "util.h"
#include "motor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define DIR_COUNTER_CLKWISE 1
#define DIR_CLKWISE 0

typedef struct {
    uint8_t x;
    uint8_t y;
} point;

void handle_uart_flags();
void execute_instructions();
void printPoint(point p);
uint8_t stringToInt(char * string);
void seperateDigits(char *arr, uint8_t num);
uint8_t countDigits(int num);

#endif
