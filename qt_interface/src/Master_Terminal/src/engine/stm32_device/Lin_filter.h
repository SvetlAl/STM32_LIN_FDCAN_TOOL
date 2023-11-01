#ifndef LIN_FILTER_H
#define LIN_FILTER_H

#include <stdint.h>

typedef struct lin_filter{
    uint8_t id;  // if id == 0, a filter is disabled
    uint8_t msk; // this mask defines what bytes (1st, 2nd, 3rd....) are to be changed
    uint8_t length;
    uint8_t unused;
    uint8_t data[8];
} lin_filter; //creating new type

typedef union lin_filter_raw {
    lin_filter filter;
    uint8_t data[12];
} lin_filter_raw;



#endif // LIN_FILTER_H
