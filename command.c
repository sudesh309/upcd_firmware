#include <stdint.h>
#include <stdbool.h>
#include "driverlib/flash.h"
#include "driverlib/gpio.h"
#include "peripheral_desc.h"
#include "map.h"

extern peripheral_desc desc;

uint32_t CmdHandler(uint8_t *data, uint32_t size)
{
   switch(data[0]) {
       case 'R':
           desc.ioPin[0].pin = 1;
           break;
        case 'B':
           desc.ioPin[0].pin = 2;
           break;
        case 'G':
           desc.ioPin[0].pin = 3;
           break;
        default:
           desc.ioPin[0].pin = MapPin(data[1] - '0');
   }

   SaveConfig();

	return size;
}
