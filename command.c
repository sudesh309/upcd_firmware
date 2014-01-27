#include <stdint.h>
#include <stdbool.h>
#include "driverlib/flash.h"
#include "driverlib/gpio.h"
#include "peripheral_desc.h"
#include "map.h"

extern peripheral_desc desc;
uint32_t mask;
uint32_t mask1 = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3;

uint32_t CmdHandler(uint8_t *data, uint32_t size)
{
   switch(data[0]) {
       case 'R':
           mask = GPIO_PIN_1;
           break;
        case 'B':
           mask = GPIO_PIN_2;
           break;
        case 'G':
           mask = GPIO_PIN_3;
           break;
        default:
           mask = MapPin(data[1] - '0');
   }

   data[0] = data[1];

	return size;
}
