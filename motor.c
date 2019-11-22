#include "motor.h"

void TEST_set_all_motor_high(){
    int test = 0;
    GPIO_setOutputHighOnPin(MOTOR1_PORT1, MOTOR1_PIN1);
    GPIO_setOutputHighOnPin(MOTOR1_PORT2, MOTOR1_PIN2);
    GPIO_setOutputHighOnPin(MOTOR1_PORT3, MOTOR1_PIN3);
    GPIO_setOutputHighOnPin(MOTOR1_PORT4, MOTOR1_PIN4);
    GPIO_setOutputHighOnPin(MOTOR2_PORT1, MOTOR2_PIN1);
    GPIO_setOutputHighOnPin(MOTOR2_PORT2, MOTOR2_PIN2);
    GPIO_setOutputHighOnPin(MOTOR2_PORT3, MOTOR2_PIN3);
    GPIO_setOutputHighOnPin(MOTOR2_PORT4, MOTOR2_PIN4);
    while(1)
    {
        test++;
        displayScrollText("SPIN");
    }
}

int move_x_motor(uint8_t quarterRotations, uint8_t dir, MOVE_DIRECTION moveDirection)
{
    const int sleep_time = 12;

    const int COUNTER_MAX = 138; // 500 is 90% of a rotation.
    volatile int counter = 0;
    volatile int step = 0;

    printString("MOTORS X MOVING \r\n");

    int i;
    for (i = 0; i < quarterRotations; i++) {

        if (edge_detect(moveDirection)){
            printString("Abort: X-Edge Reached \r\n");
            break;
        }

        counter = 0;
        while (counter <= COUNTER_MAX)
        {
            switch (step) {
            case 0:
                GPIO_setOutputLowOnPin(MOTOR1_PORT1, MOTOR1_PIN1);
                GPIO_setOutputLowOnPin(MOTOR1_PORT2, MOTOR1_PIN2);
                GPIO_setOutputLowOnPin(MOTOR1_PORT3, MOTOR1_PIN3);
                GPIO_setOutputHighOnPin(MOTOR1_PORT4, MOTOR1_PIN4);
                break;
            case 1:
                GPIO_setOutputLowOnPin(MOTOR1_PORT1, MOTOR1_PIN1);
                GPIO_setOutputLowOnPin(MOTOR1_PORT2, MOTOR1_PIN2);
                GPIO_setOutputHighOnPin(MOTOR1_PORT3, MOTOR1_PIN3);
                GPIO_setOutputHighOnPin(MOTOR1_PORT4, MOTOR1_PIN4);
                break;
            case 2:
                GPIO_setOutputLowOnPin(MOTOR1_PORT1, MOTOR1_PIN1);
                GPIO_setOutputLowOnPin(MOTOR1_PORT2, MOTOR1_PIN2);
                GPIO_setOutputHighOnPin(MOTOR1_PORT3, MOTOR1_PIN3);
                GPIO_setOutputLowOnPin(MOTOR1_PORT4, MOTOR1_PIN4);
                break;
            case 3:
                GPIO_setOutputLowOnPin(MOTOR1_PORT1, MOTOR1_PIN1);
                GPIO_setOutputHighOnPin(MOTOR1_PORT2, MOTOR1_PIN2);
                GPIO_setOutputHighOnPin(MOTOR1_PORT3, MOTOR1_PIN3);
                GPIO_setOutputLowOnPin(MOTOR1_PORT4, MOTOR1_PIN4);
                break;
            case 4:
                GPIO_setOutputLowOnPin(MOTOR1_PORT1, MOTOR1_PIN1);
                GPIO_setOutputHighOnPin(MOTOR1_PORT2, MOTOR1_PIN2);
                GPIO_setOutputLowOnPin(MOTOR1_PORT3, MOTOR1_PIN3);
                GPIO_setOutputLowOnPin(MOTOR1_PORT4, MOTOR1_PIN4);
                break;
            case 5:
                GPIO_setOutputHighOnPin(MOTOR1_PORT1, MOTOR1_PIN1);
                GPIO_setOutputHighOnPin(MOTOR1_PORT2, MOTOR1_PIN2);
                GPIO_setOutputLowOnPin(MOTOR1_PORT3, MOTOR1_PIN3);
                GPIO_setOutputLowOnPin(MOTOR1_PORT4, MOTOR1_PIN4);
                break;
            case 6:
                GPIO_setOutputHighOnPin(MOTOR1_PORT1, MOTOR1_PIN1);
                GPIO_setOutputLowOnPin(MOTOR1_PORT2, MOTOR1_PIN2);
                GPIO_setOutputLowOnPin(MOTOR1_PORT3, MOTOR1_PIN3);
                GPIO_setOutputLowOnPin(MOTOR1_PORT4, MOTOR1_PIN4);
                break;
            case 7:
                GPIO_setOutputHighOnPin(MOTOR1_PORT1, MOTOR1_PIN1);
                GPIO_setOutputLowOnPin(MOTOR1_PORT2, MOTOR1_PIN2);
                GPIO_setOutputLowOnPin(MOTOR1_PORT3, MOTOR1_PIN3);
                GPIO_setOutputHighOnPin(MOTOR1_PORT4, MOTOR1_PIN4);
                break;
            default:
                GPIO_setOutputLowOnPin(MOTOR1_PORT1, MOTOR1_PIN1);
                GPIO_setOutputLowOnPin(MOTOR1_PORT2, MOTOR1_PIN2);
                GPIO_setOutputLowOnPin(MOTOR1_PORT3, MOTOR1_PIN3);
                GPIO_setOutputLowOnPin(MOTOR1_PORT4, MOTOR1_PIN4);
                break;
            }

            sleep(sleep_time);
            if (dir) { //Counter clockwise
                step++;
            } else {
                step--;
            }
            if (step > 7) step = 0;
            if (step < 0) step = 7;

            counter++;
        }

        if (dir == DIR_CLKWISE) {
            curr_pos.x += 1;
        } else {
            curr_pos.x -= 1;
        }

        printPoint(curr_pos);
    }

    printString("MOTORS X DONE\r\n");
    return 1;
}

int move_y_motor(uint8_t quarterRotations, uint8_t dir, MOVE_DIRECTION moveDirection)
{
    const int sleep_time = 12;

    const int COUNTER_MAX = 138; // 500 is 90% of a rotation.
    volatile int counter = 0;
    volatile int step = 0;

    printString("MOTORS Y MOVING \r\n");

    int i;
    for (i = 0; i < quarterRotations; i++) {

        if (edge_detect(moveDirection)){
            printString("Abort: Y-Edge Reached \r\n");
            break;
        }

        counter = 0;
        while (counter <= COUNTER_MAX)
        {
            switch (step) {
            case 0:
                GPIO_setOutputLowOnPin(MOTOR2_PORT1, MOTOR2_PIN1);
                GPIO_setOutputLowOnPin(MOTOR2_PORT2, MOTOR2_PIN2);
                GPIO_setOutputLowOnPin(MOTOR2_PORT3, MOTOR2_PIN3);
                GPIO_setOutputHighOnPin(MOTOR2_PORT4, MOTOR2_PIN4);
                break;
            case 1:
                GPIO_setOutputLowOnPin(MOTOR2_PORT1, MOTOR2_PIN1);
                GPIO_setOutputLowOnPin(MOTOR2_PORT2, MOTOR2_PIN2);
                GPIO_setOutputHighOnPin(MOTOR2_PORT3, MOTOR2_PIN3);
                GPIO_setOutputHighOnPin(MOTOR2_PORT4, MOTOR2_PIN4);
                break;
            case 2:
                GPIO_setOutputLowOnPin(MOTOR2_PORT1, MOTOR2_PIN1);
                GPIO_setOutputLowOnPin(MOTOR2_PORT2, MOTOR2_PIN2);
                GPIO_setOutputHighOnPin(MOTOR2_PORT3, MOTOR2_PIN3);
                GPIO_setOutputLowOnPin(MOTOR2_PORT4, MOTOR2_PIN4);
                break;
            case 3:
                GPIO_setOutputLowOnPin(MOTOR2_PORT1, MOTOR2_PIN1);
                GPIO_setOutputHighOnPin(MOTOR2_PORT2, MOTOR2_PIN2);
                GPIO_setOutputHighOnPin(MOTOR2_PORT3, MOTOR2_PIN3);
                GPIO_setOutputLowOnPin(MOTOR2_PORT4, MOTOR2_PIN4);
                break;
            case 4:
                GPIO_setOutputLowOnPin(MOTOR2_PORT1, MOTOR2_PIN1);
                GPIO_setOutputHighOnPin(MOTOR2_PORT2, MOTOR2_PIN2);
                GPIO_setOutputLowOnPin(MOTOR2_PORT3, MOTOR2_PIN3);
                GPIO_setOutputLowOnPin(MOTOR2_PORT4, MOTOR2_PIN4);
                break;
            case 5:
                GPIO_setOutputHighOnPin(MOTOR2_PORT1, MOTOR2_PIN1);
                GPIO_setOutputHighOnPin(MOTOR2_PORT2, MOTOR2_PIN2);
                GPIO_setOutputLowOnPin(MOTOR2_PORT3, MOTOR2_PIN3);
                GPIO_setOutputLowOnPin(MOTOR2_PORT4, MOTOR2_PIN4);
                break;
            case 6:
                GPIO_setOutputHighOnPin(MOTOR2_PORT1, MOTOR2_PIN1);
                GPIO_setOutputLowOnPin(MOTOR2_PORT2, MOTOR2_PIN2);
                GPIO_setOutputLowOnPin(MOTOR2_PORT3, MOTOR2_PIN3);
                GPIO_setOutputLowOnPin(MOTOR2_PORT4, MOTOR2_PIN4);
                break;
            case 7:
                GPIO_setOutputHighOnPin(MOTOR2_PORT1, MOTOR2_PIN1);
                GPIO_setOutputLowOnPin(MOTOR2_PORT2, MOTOR2_PIN2);
                GPIO_setOutputLowOnPin(MOTOR2_PORT3, MOTOR2_PIN3);
                GPIO_setOutputHighOnPin(MOTOR2_PORT4, MOTOR2_PIN4);
                break;
            default:
                GPIO_setOutputLowOnPin(MOTOR2_PORT1, MOTOR2_PIN1);
                GPIO_setOutputLowOnPin(MOTOR2_PORT2, MOTOR2_PIN2);
                GPIO_setOutputLowOnPin(MOTOR2_PORT3, MOTOR2_PIN3);
                GPIO_setOutputLowOnPin(MOTOR2_PORT4, MOTOR2_PIN4);
                break;
            }

            sleep(sleep_time);
            if (dir) { //Counter clockwise
                step++;
            } else {
                step--;
            }
            if (step > 7) step = 0;
            if (step < 0) step = 7;

            counter++;
        }
        if (dir == DIR_CLKWISE) {
            curr_pos.y += 1;
        } else {
            curr_pos.y -= 1;
        }

        printPoint(curr_pos);

    }
    printString("MOTORS Y DONE\r\n");
    return 1;
}
