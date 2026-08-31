#ifndef TARGET_PARSER_H

#define TARGET_PARSER_H
#include <stdint.h>

typedef struct{
    int16_t x_pos; // [mm]
    int16_t y_pos; // [mm]
    int16_t speed; // [cm/s]
    uint16_t pixel_distance_value; // [mm]
} target_t;

#endif

