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


void itoa(uint16_t x);


// Trigger sends a 3v3 (should be 5V) pulse to the the trigger pin for 10us
void trigger_sensor(distance_sensor *ds);

// Sets the echo pins to input and trigger to output.
void setup_sensor(distance_sensor *ds);


void read_distance_v2(distance_sensor *ds);

// Reads the distance given a distance_sensor.
// Assumes the user has setup the sensor.
void read_distance(distance_sensor *ds);
