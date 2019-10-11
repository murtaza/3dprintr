#include <stdio.h>
#include "driverlib/driverlib.h"
#include "string.h"

#pragma once
typedef uint8_t PORT;
typedef uint16_t PIN;

// Scuffed way to sleep.
// Sleeps the program for n us.
// Max value is: 268435455 approximately 268 seconds.
void sleep(volatile uint32_t us);
void printChar(char c);
void printString(char *string);