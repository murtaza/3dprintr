#pragma once

#include "driverlib/driverlib.h"
#include "util.h"

#define NUM_DIST_SENSORS 4

// Ultrasonic sensors:
// 2.5 This is the common port to trigger all the sensors.
extern const PORT TRIG_PORT;
extern const PORT TRIG_PIN;

// 8.1, 2.7, 8.0, 5.1
extern const PORT U_SENSOR1_PORT;
extern const PIN U_SENSOR1_PIN;

extern const PORT U_SENSOR2_PORT;
extern const PIN U_SENSOR2_PIN;

extern const PORT U_SENSOR3_PORT;
extern const PIN U_SENSOR3_PIN;

extern const PORT U_SENSOR4_PORT;
extern const PIN U_SENSOR4_PIN;

// MOTOR 1
// 1.5, 1.4, 1.3, 5.3
extern const PORT MOTOR1_PORT1;
extern const PIN MOTOR1_PIN1;

extern const PORT MOTOR1_PORT2;
extern const PIN MOTOR1_PIN2;

extern const PORT MOTOR1_PORT3;
extern const PIN MOTOR1_PIN3;

extern const PORT MOTOR1_PORT4;
extern const PIN MOTOR1_PIN4;
