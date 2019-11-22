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

//LaunchPad LED2
#define LED2_PORT GPIO_PORT_P4
#define LED2_PIN GPIO_PIN0
//LaunchPad Pushbutton Switch 1
#define SW1_PORT GPIO_PORT_P1
#define SW1_PIN GPIO_PIN2
//LaunchPad Pushbutton Switch 2
#define SW2_PORT GPIO_PORT_P2
#define SW2_PIN GPIO_PIN6

void run_dont_stop();
int parse_instructions();
void execute_instructions();
void printPoint(point p);
uint8_t stringToInt(char *string);
void seperateDigits(char *arr, uint8_t num);
uint8_t countDigits(int num);

#endif
