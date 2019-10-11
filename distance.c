#pragma once
#include <string.h>

#include "distance.h"
#include "util.h"
#include "driverlib/driverlib.h"
#include "hal_LCD.h"

// Assumes setup has been called for the distance_sensors.
void ISR_routine(distance_sensor *sensors, int num_sensors)
{
    int i = 0;
    for (; i < num_sensors; i++)
    {
        read_distance_v2(sensors + i);
    }
}

// Call setup for every sensor and return the sensors object.
void setup_sensors(distance_sensor *sensors, PORT *trigger_ports, PIN *trigger_pins, PORT *echo_ports, PIN *echo_pins, int num_sensors)
{
    size_t i = 0;
    for (; i < num_sensors; i++)
    {
        sensors[i].trigger_port = trigger_ports[i];
        sensors[i].trigger_pin = trigger_pins[i];
        sensors[i].echo_port = echo_ports[i];
        sensors[i].echo_pin = echo_pins[i];
        _setup_sensor(sensors + i);
    }
}

// Cleanup a list of distance_sensors.
//void cleanup_sensors(distance_sensor *ds, int num_sensors)
//{
//    for (; i < num_sensors; i++)
//    {
//        free(ds[i]);
//    }
//    // Set ds to NULL.
//    *ds = 0;
//    return
//}

void itoa(uint16_t x)
{
    // 16 bit integer
    uint16_t temp;
    unsigned char out[17];
    volatile int i = 15;
    for (; i > -1; i--)
    {
        temp = (x >> i) & 0x0001;
        if (temp != 0)
        {
            out[15 - i] = '1';
        }
        else
        {
            out[15 - i] = '0';
        }
    }
    out[16] = '\0';
    displayScrollText(out);
}

// Trigger sends a 3v3 (should be 5V) pulse to the the trigger pin for 10us
void _trigger_sensor(distance_sensor *ds)
{
    // use timer compare feature to modify pin (once).
    GPIO_setOutputHighOnPin(ds->trigger_port, ds->trigger_pin);
    // sleep for 10 us.
    sleep(10);
    GPIO_setOutputLowOnPin(ds->trigger_port, ds->trigger_pin);
}

// Sets the echo pins to input and trigger to output.
void _setup_sensor(distance_sensor *ds)
{
    GPIO_setAsInputPin(ds->echo_port, ds->echo_pin);
    GPIO_setAsOutputPin(ds->trigger_port, ds->trigger_pin);

    // Ensure Trigger is set to low, and wait a bit.
    GPIO_setOutputLowOnPin(ds->trigger_port, ds->trigger_pin);
    sleep(100);
    displayScrollText("SENSOR SETUP");
}

void read_distance_v2(distance_sensor *ds)
{

    displayScrollText("DIST");
    _trigger_sensor(ds);
    volatile int status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
    volatile int curr_status = status;
    unsigned int cycles = 0;

    // While it's low, wait.
    while (curr_status == 0)
    {
        curr_status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
    }

    // Now it's high! Start counting cycles.
    while (curr_status == 1)
    {
        cycles += 3;
        curr_status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
    }

    showHex(cycles);
    __delay_cycles(10000000);
}

// Reads the distance given a distance_sensor.
// Assumes the user has setup the sensor.
void read_distance(distance_sensor *ds)
{
    // First we trigger the sensor.
    _trigger_sensor(ds);
    volatile int initial_status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
    volatile int curr_status = initial_status;

    // While it is already high or low.
    while (curr_status == initial_status)
    {
        curr_status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
    }

    volatile uint16_t wait_time = 0;
    if (curr_status == 1)
    {
        while (curr_status == 1)
        {
            wait_time++;
            curr_status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
        }
    }
    else
    {
        while (curr_status == 0)
        {
            curr_status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
        }
        while (curr_status == 1)
        {
            wait_time++;
            curr_status = GPIO_getInputPinValue(ds->echo_port, ds->echo_pin);
        }
    }
    itoa(wait_time);
    displayScrollText("UV SENSOR DONE");
}
