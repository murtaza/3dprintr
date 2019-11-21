#include "uart.h"

volatile char instructions[50];
volatile uint8_t char_count = 0;

volatile int run_instructions = 0;
volatile int point_finished = 0;
volatile int direction_value = 0;
volatile int reset = 1;

volatile int parse_x = 1;
volatile uint8_t curr_x;
volatile uint8_t curr_y;

volatile int num_points = 0;
volatile point curr_pos = { 0, 0 };
volatile point points[50];

/* EUSCI A0 UART ISR - Echoes data back to PC host */
#pragma vector=USCI_A0_VECTOR
__interrupt
void EUSCIA0_ISR(void)
{
    uint8_t RxStatus = EUSCI_A_UART_getInterruptStatus(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);

    EUSCI_A_UART_clearInterrupt(EUSCI_A0_BASE, RxStatus);

    if (RxStatus)
    {
        uint8_t receiveData = EUSCI_A_UART_receiveData(EUSCI_A0_BASE);
        EUSCI_A_UART_transmitData(EUSCI_A0_BASE, receiveData);
        if (receiveData == 13)
        {
            point_finished = 1;
        }
        else if (receiveData == 71)
        {
            run_instructions = 1;
        }
        else if (receiveData == 32)
        {
            direction_value = 1;
        }
        else
        {
            instructions[char_count] = (char)receiveData;
            char_count++;
        }
    }
}

void store_direction_value() {
    if (parse_x)
    {
         curr_x = 0;
         instructions[char_count] = '\0';
         uint8_t value = stringToInt(instructions);
         curr_x = value;

         char_count = 0;
         parse_x = 0;
     }
     else
     {
         curr_y = 0;
         instructions[char_count] = '\0';
         uint8_t value = stringToInt(instructions);
         curr_y = value;

         char_count = 0;
         parse_x = 1;
     }
     direction_value = 0;
}

void store_point() {
    point p = { curr_x, curr_y };
    points[num_points] = p;
    num_points++;

    point_finished = 0;
    printPoint(p);
    parse_x = 1;
}

void print_all_points() {
    printString("Here are your points\n\r");

    uint8_t i;
    for (i = 0; i < num_points; i++) {
        printPoint(points[i]);
        sleep(1500);
    }
}

void handle_uart_flags() {

    if (reset) {
        printString("Type in point in for x y, space separated, press enter for new point or type G for GO\n\r");
        reset = 0;
    }

    if (direction_value) {
        store_direction_value();
    }

    if (point_finished) {
        store_point();
    }

    if (run_instructions) {
        //print_all_points();
        execute_instructions();
        /* Reset */
        num_points = 0;
        run_instructions = 0;
        reset = 1;
    }

}

void execute_instructions() {
    printString("Now executing instructions.\n\r");
    printString("Current position is: \n\r");
    printPoint(curr_pos);
    uint8_t i;
    for (i = 0; i < num_points; i++) {
        if (points[i].x > curr_pos.x) {
            move_x_motor(points[i].x - curr_pos.x, DIR_CLKWISE);
        } else {
            move_x_motor(curr_pos.x - points[i].x, DIR_COUNTER_CLKWISE);
        }

        if (points[i].y > curr_pos.y) {
            move_y_motor(points[i].y - curr_pos.y, DIR_CLKWISE);
        } else {
            move_y_motor(curr_pos.y - points[i].y, DIR_COUNTER_CLKWISE);
        }

        curr_pos = points[i];
        printPoint(curr_pos);
    }
}

void printPoint(point p) {
    char dig_arr[10];

    printString("X=");
    seperateDigits(dig_arr, p.x);
    printString(dig_arr);

    printChar(' ');

    printString("Y=");
    seperateDigits(dig_arr, p.y);
    printString(dig_arr);
    printString("\n\r");
}

uint8_t countDigits(int num)
{
    uint8_t ret=1;
    while (num/=10) ret++;
    return ret;
}

void seperateDigits(char *arr, uint8_t num) {
    uint8_t digits = countDigits(num);
    uint8_t pos = digits;
    while (pos--) {
        arr[pos] = num % 10 + '0';
        num /= 10;
    }
    arr[digits] = '\0';
}

uint8_t stringToInt(char * string)
{
    return (uint8_t)atoi(string);
}
