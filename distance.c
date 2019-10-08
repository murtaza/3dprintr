#pragma once
#include "util.h"
#include "driverlib/driverlib.h"
#include "hal_LCD.h"


typedef struct distance_sensor{

    PORT trigger_port;  // Trigger port (OUTPUT)
    PIN trigger_pin;    // Trigger pin (OUTPUT)

    PORT echo_port;   // Echo port (INPUT)
    PIN echo_pin;     // Echo pin (INPUT)

} distance_sensor;


void itoa(uint16_t x)
{
    // 16 bit integer
    uint16_t temp;
    unsigned char out[17];
    volatile int i = 15;
    for (; i > -1; i--){
        temp = (x >> i) & 0x0001;
        if (temp != 0){
            out[15 - i] = '1';
        } else {
            out[15 - i] = '0';
        }
    }
    out[16] = '\0';
    displayScrollText(out);
}


// Trigger sends a 3v3 (should be 5V) pulse to the the trigger pin for 10us
void trigger_sensor(distance_sensor *ds)
{
    // use timer compare feature to modify pin (once).
    GPIO_setOutputHighOnPin(ds->trigger_port, ds->trigger_pin);
    // sleep for 10 us.
    sleep(10);
    GPIO_setOutputLowOnPin(ds->trigger_port, ds->trigger_pin);
}

// Sets the echo pins to input and trigger to output.
void setup_sensor(distance_sensor *ds)
{
    GPIO_setAsInputPin(ds->echo_port, ds->echo_pin);
    GPIO_setAsOutputPin(ds->trigger_port, ds->trigger_pin);

    // Ensure Trigger is set to low, and wait a bit.
    GPIO_setOutputLowOnPin(ds->trigger_port, ds->trigger_pin);
    sleep(100);
}


void read_distance_v2(distance_sensor *ds)
{

    displayScrollText("DIST");
    trigger_sensor(ds);
    volatile int status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
    volatile int curr_status = status;
    unsigned int cycles = 0;

    // While it's low, wait.
    while (curr_status == 0){
        curr_status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
    }

    // Now it's high! Start counting cycles.
    while (curr_status == 1)
    {
        cycles += 3;
        curr_status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
    }

    showHex((cycles & 0xFFFF0000) >> 16);
    showHex(cycles & 0x0000FFFF);
    __delay_cycles(10000000);
}

// Reads the distance given a distance_sensor.
// Assumes the user has setup the sensor.
void read_distance(distance_sensor *ds)
{
    // First we trigger the sensor.
    trigger_sensor(ds);
    volatile int initial_status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
    volatile int curr_status = initial_status;

    // While it is already high or low.
    while (curr_status == initial_status) {
        curr_status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
    }

    volatile uint16_t wait_time = 0;
    if (curr_status == 1){
        while (curr_status == 1){
            wait_time++;
            curr_status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
        }
    } else {
        while (curr_status == 0){
            curr_status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
        }
        while(curr_status == 1){
            wait_time++;
            curr_status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
        }
    }
    itoa(wait_time);
    displayScrollText("UV SENSOR DONE");
}
