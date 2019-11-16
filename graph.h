#pragma once
#include "hal_LCD.h"

typedef enum
{
    DIRECTION_X,
    DIRECTION_Y,
    DIRECTION_Z,

} direction_t;

// Globals to define current position.
unsigned int graph_x = 0;
unsigned int graph_y = 0;
unsigned int graph_z = 0;

typedef struct
{
    int lcdmem_12;
    int lcdmem_13;
} lcdbat_tuple_t;

typedef struct
{
    char letter;
    int pos;
} lcdchar_tuple_t;

/*
MF: Sample code to run this.
    init_graph();
    direction_t dx = DIRECTION_X;
    direction_t dy = DIRECTION_Y;
    direction_t dz = DIRECTION_Z;

    __delay_cycles(200000);
    graph(dx, -3);
    __delay_cycles(200000);
    graph(dy, -3);
    __delay_cycles(200000);
    graph(dx, 7);
    __delay_cycles(200000);
    graph(dy, 7);
*/
