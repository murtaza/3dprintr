#pragma once
#include <string.h>

#include "util.h"
#include "driverlib/driverlib.h"
#include "hal_LCD.h"

typedef struct distance_sensor
{

    PORT trigger_port; // Trigger port (OUTPUT)
    PIN trigger_pin;   // Trigger pin (OUTPUT)

    PORT echo_port; // Echo port (INPUT)
    PIN echo_pin;   // Echo pin (INPUT)

} distance_sensor;

// Eventually will run on an interrupt. Not sure how arguments will be passed then.
// MF TODO: Run this on an interrupt.
void uv_ISR_routine(distance_sensor *sensors, int num_sensors);

void uv_test(PORT trig_port, PIN trig_pin, PORT echo_port, PIN echo_pin);

void itoa(uint16_t x);

// Trigger sends a 3v3 (should be 5V) pulse to the the trigger pin for 10us
void _trigger_sensor(distance_sensor *ds);

// Sets up multiple sensors given a list of ports and pins.
void setup_sensors(distance_sensor *sensors, PORT *trigger_ports, PIN *trigger_pins, PORT *echo_ports, PIN *echo_pins, int num_sensors);

// Sets the echo pins to input and trigger to output.
void _setup_sensor(distance_sensor *ds);

void read_distance_v2(distance_sensor *ds);

// Reads the distance given a distance_sensor.
// Assumes the user has setup the sensor.
void read_distance(distance_sensor *ds);
