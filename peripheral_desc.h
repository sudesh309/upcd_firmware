#ifndef __PERIPHERAL_DESC_H__
#define __PERIPHERAL_DESC_H__

#include <stdint.h>

typedef struct {
    unsigned int port : 3;
    unsigned int pin : 3;
    unsigned int mode : 1;
} ioPin_t;

typedef struct {
    ioPin_t fPin;
    ioPin_t rPin;
    ioPin_t pwmPin[2];
    uint16_t dutyCycle;
} mtrCtl_t;

typedef struct {
    ioPin_t ioPin[36];
    mtrCtl_t mtrCtl[4];  
} peripheral_desc;

#endif
