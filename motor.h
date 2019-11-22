#pragma once
#include "constants.h"
#include "util.h"
#include "uart.h"
#include "distance.h"
#include "hal_lcd.h"

int move_x_motor(uint8_t quarterRotations, uint8_t dir, MOVE_DIRECTION moveDirection);

int move_y_motor(uint8_t quarterRotations, uint8_t dir, MOVE_DIRECTION moveDirection);
