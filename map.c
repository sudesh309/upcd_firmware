#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "peripheral_desc.h"
#include "driverlib/gpio.h"

uint32_t MapPin(uint8_t pin)
{
    switch(pin) {
        case 0:
            return GPIO_PIN_0;
        case 1: 
            return GPIO_PIN_1;
        case 2:
            return GPIO_PIN_2;
        case 3: 
            return GPIO_PIN_3;
        case 4:
            return GPIO_PIN_4;
        case 5: 
            return GPIO_PIN_5;
        case 6:
            return GPIO_PIN_6;
        case 7: 
            return GPIO_PIN_7;
        default:
            return 0x00000000;
    }
}

uint32_t MapPort(uint8_t port)
{
    switch(port) {
        case 1:
            return GPIO_PORTA_BASE;
        case 2: 
            return GPIO_PORTB_BASE;
        case 3:
            return GPIO_PORTC_BASE;
        case 4: 
            return GPIO_PORTD_BASE;
        case 5:
            return GPIO_PORTE_BASE;
        case 6: 
            return GPIO_PORTF_BASE;
        default:
            return 0x00000000;
    }
}


