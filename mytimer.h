#pragma once
#include "driverlib/driverlib.h"
#include "hal_LCD.h"
#include "distance.h"
#include "constants.h"

void setup_timer_interrupts();
void handle_sensor_distance();
unsigned int read_uv();
