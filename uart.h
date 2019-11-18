#ifndef UART_H
#define UART_H

#include "driverlib/driverlib.h"
#include "util.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    uint8_t x;
    uint8_t y;
} point;

void handle_uart_flags();
void printPoint(uint8_t x, uint8_t y);
uint8_t stringToInt(char * string);
void seperateDigits(char *arr, uint8_t num);
uint8_t countDigits(int num);

#endif
