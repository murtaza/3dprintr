#include "uart.h"

volatile char instructions[50];
volatile uint8_t char_count = 0;

volatile point points[50];
volatile int num_points = 0;

typedef enum State
{
    INIT,
    NOT_DONE,
    DONE,
    EXECUTE,
} State;

State state = INIT;

/* EUSCI A0 UART ISR - Echoes data back to PC host */
#pragma vector = USCI_A0_VECTOR
__interrupt void EUSCIA0_ISR(void)
{
    uint8_t RxStatus = EUSCI_A_UART_getInterruptStatus(EUSCI_A0_BASE, EUSCI_A_UART_RECEIVE_INTERRUPT_FLAG);

    EUSCI_A_UART_clearInterrupt(EUSCI_A0_BASE, RxStatus);

    if (RxStatus)
    {
        uint8_t receiveData = EUSCI_A_UART_receiveData(EUSCI_A0_BASE);
        EUSCI_A_UART_transmitData(EUSCI_A0_BASE, receiveData);
        if (receiveData == 13)
        {
            // Enter char
            state = DONE;
        }
        else if (receiveData == 71)
        {
            state = EXECUTE;
        }
        else
        {
            instructions[char_count] = (char)receiveData;
            char_count++;
        }
    }
}

int is_valid(char *point, uint8_t len)
{
    uint8_t i = 0;
    while (point[i] != '\0')
    {
        if (point[i] < '0' || point[i] > '9')
        {
            return 0;
        }
        i++;
    }
    return 1;
}

void print_all_points()
{
    printString("\r\nHere are your points:\n\r");

    uint8_t i;
    for (i = 0; i < num_points; i++)
    {
        printPoint(points[i]);
        sleep(1500);
    }
}

void run_dont_stop()
{
    while (1)
    {
        switch (state)
        {
        case INIT:
            printString("Please enter your points (X Y): \r\n");
            state = NOT_DONE;
            break;
        case DONE:
            if (parse_instructions() < 0)
            {
                printString("Error: Invalid points given. Enter X Y \r\n");
            }
            char_count = 0;
            state = NOT_DONE;
            break;
        case NOT_DONE:
            break;
        case EXECUTE:
            print_all_points();
            execute_instructions();
            state = INIT;
            num_points = 0;
            break;
        default:
            // stuff is on fire.
            printString("Error: Terrible\n");
        }
    }
}

int parse_instructions()
{

    uint8_t i = 0;
    char x[10];
    char y[10];
    int x_len = 0;
    int y_len = 0;
    // Get x
    while (instructions[i] != ' ')
    {
        x[x_len] = instructions[i];
        i++;
        x_len++;
    }
    x[x_len] = '\0';
    x_len++;
    if (!is_valid(x, x_len))
    {
        return -1;
    }

    // Get y
    i++;
    while ((i < char_count) && (instructions[i] != ' '))
    {
        y[y_len] = instructions[i];
        y_len++;
        i++;
    }
    y[y_len] = '\0';
    y_len++;

    if (!is_valid(y, y_len))
    {
        return -1;
    }

    points[num_points].y = atoi(y);
    points[num_points].x = atoi(x);
    printPoint(points[num_points]);
    num_points++;
    return 0;
}

void execute_instructions()
{
    printString("Now executing instructions.\n\r");
    printString("Current position is: \n\r");
    printPoint(curr_pos);
    uint8_t i;
    for (i = 0; i < num_points; i++)
    {
        if (points[i].x > curr_pos.x)
        {
            // +x
            if (!move_x_motor(points[i].x - curr_pos.x, DIR_CLKWISE, X_PLUS))
            {
                printString("Abort: Edge detected (+X) \r\n");
                break;
            }
        }
        else
        {
            // -x
            if (!move_x_motor(curr_pos.x - points[i].x, DIR_COUNTER_CLKWISE, X_MINUS))
            {
                printString("Abort: Edge detected (-X) \r\n");
                break;
            }
        }

        if (points[i].y > curr_pos.y)
        {
            // +y
            if (!move_y_motor(points[i].y - curr_pos.y, DIR_CLKWISE, Y_PLUS))
            {
                printString("Abort: Edge detected (+Y) \r\n");
                break;
            }
        }
        else
        {
            // -y
            if (!move_y_motor(curr_pos.y - points[i].y, DIR_COUNTER_CLKWISE, Y_MINUS))
            {
                printString("Abort: Edge detected (-Y) \r\n");
                break;
            }
        }
    }
}

void printPoint(point p)
{
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

void printCurrPos(point p)
{
    char dig_arr[10];
    printString("CurrPos: ");

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
    uint8_t ret = 1;
    while (num /= 10)
        ret++;
    return ret;
}

void seperateDigits(char *arr, uint8_t num)
{
    uint8_t digits = countDigits(num);
    uint8_t pos = digits;
    while (pos--)
    {
        arr[pos] = num % 10 + '0';
        num /= 10;
    }
    arr[digits] = '\0';
}

uint8_t stringToInt(char *string)
{
    return (uint8_t)atoi(string);
}
