#include "graph.h"

void init_graph()
{
    // TODO: Clem
}

void graph(direction_t d, int movement)
{
    const lcdbat_tuple_t x_segments[] = {{0, 0x01}, {0, 0x03}, {0x20, 0x03}, {0x20, 0x07}, {0x60, 0x07}, {0x60, 0x0F}, {0xE0, 0x0F}, {0xF0, 0x0F}};
    const char y_segments[8][6] =
        {
            {0x02, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x03, 0x00, 0x00, 0x00, 0x00, 0x00},
            {0x03, 0x02, 0x00, 0x00, 0x00, 0x00},
            {0x03, 0x03, 0x00, 0x00, 0x00, 0x00},
            {0x03, 0x03, 0x02, 0x00, 0x00, 0x00},
            {0x03, 0x03, 0x03, 0x00, 0x00, 0x00},
            {0x03, 0x03, 0x03, 0x02, 0x00, 0x00},
            {0x03, 0x03, 0x03, 0x03, 0x00, 0x00}};
    int i = 0;
    if (d == DIRECTION_X)
    {
        int limit = graph_x + movement;
        if (movement > 0)
        {
            for (i = graph_x + 1; i <= limit; i++)
            {
                LCDMEM[12] = x_segments[i].lcdmem_12;
                LCDMEM[13] = x_segments[i].lcdmem_13;
                __delay_cycles(200000);
            }
            graph_x = graph_x + movement;
        }
        else if (movement < 0)
        {
            i = graph_x - 1;
            int limit = graph_x + movement;
            for (i = graph_x - 1; i >= limit; i--)
            {
                LCDMEM[12] = x_segments[i].lcdmem_12;
                LCDMEM[13] = x_segments[i].lcdmem_13;
                __delay_cycles(200000);
            }
            graph_x = graph_x + movement;
        }
    }
    else if (d == DIRECTION_Y)
    {
        int digit_locations[] = {2, 3, 4, 5, 1, 9};
        int limit = graph_y + movement;
        if (movement > 0)
        {
            for (i = graph_y + 1; i <= limit; i++)
            {
                int j = 0;
                for (; j < 5; j++)
                {
                    LCDMEMW[digit_locations[j]] = y_segments[i][j];
                }
                __delay_cycles(200000);
            }
            graph_y = graph_y + movement;
        }
        else if (movement < 0)
        {
            for (i = graph_y - 1; i >= limit; i--)
            {
                int j = 0;
                for (; j < 5; j++)
                {
                    LCDMEMW[digit_locations[j]] = y_segments[i][j];
                }
                __delay_cycles(200000);
            }
            graph_y = graph_y + movement;
        }
    }
}
