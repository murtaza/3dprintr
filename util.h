#pragma once
#include <stdio.h>
#include <string.h>
#include "driverlib/driverlib.h"

typedef uint8_t PORT;
typedef uint16_t PIN;


typedef enum MOVE_DIRECTION {
    X_PLUS,
    X_MINUS,
    Y_PLUS,
    Y_MINUS
} MOVE_DIRECTION;

typedef struct {
    uint8_t x;
    uint8_t y;
} point;



extern volatile point curr_pos;

// Scuffed way to sleep.
// Sleeps the program for n us.
// Max value is: 268435455 approximately 268 seconds.
void sleep(volatile uint32_t us);
void printChar(char c);
void printString(char *string);
