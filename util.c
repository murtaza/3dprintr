#include "util.h"

typedef uint8_t PORT;
typedef uint16_t PIN;

// Scuffed way to sleep.
// Sleeps the program for n us.
// Max value is: 268435455 approximately 268 seconds.
void sleep(volatile uint32_t us)
{
    // 16 cycles per microsecond, assuming each loop iteration takes 2 cycles (compare, increment).
    us = us * 8;
    while (us != 0)
    {
        us--;
    }
}

void printChar(char c)
{
    EUSCI_A_UART_transmitData(EUSCI_A0_BASE, (uint8_t)c);
}

void printString(char *string)
{
    unsigned int i = 0;
    for (i = 0; i < strlen(string); i++)
    {
        printChar(string[i]);
    }
}
