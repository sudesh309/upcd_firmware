#ifndef __PERIPHERAL_DESC_H__
#define __PERIPHERAL_DESC_H__

#include <stdint.h>

typedef struct {
    unsigned int port : 3;
    unsigned int pin : 3;
    unsigned int mode : 1;
} ioPin_t;

typedef struct {
    ioPin_t ioPin[35];
} peripheral_desc;

#endif
