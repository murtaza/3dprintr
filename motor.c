#include "motor.h"

void move_motor()
{
    const int sleep_time = 12;

    const int COUNTER_MAX = 550; // 500 is 90% of a rotation.
    volatile int counter = 0;
    while (counter <= COUNTER_MAX)
    {
        GPIO_setOutputHighOnPin(MOTOR1_PORT1, MOTOR1_PIN1);
        sleep(sleep_time);
        __delay_cycles(20000000);
        GPIO_setOutputLowOnPin(MOTOR1_PORT1, MOTOR1_PIN1);
        sleep(sleep_time);

        GPIO_setOutputHighOnPin(MOTOR1_PORT2, MOTOR1_PIN2);
        sleep(sleep_time);
        GPIO_setOutputLowOnPin(MOTOR1_PORT2, MOTOR1_PIN2);
        sleep(sleep_time);

        GPIO_setOutputHighOnPin(MOTOR1_PORT3, MOTOR1_PIN3);
        sleep(sleep_time);
        GPIO_setOutputLowOnPin(MOTOR1_PORT3, MOTOR1_PIN3);
        sleep(sleep_time);

        GPIO_setOutputHighOnPin(MOTOR1_PORT4, MOTOR1_PIN4);
        sleep(sleep_time);
        GPIO_setOutputLowOnPin(MOTOR1_PORT4, MOTOR1_PIN4);
        sleep(sleep_time);

        counter++;
    }

    displayScrollText("MOTORS DONE");
}
