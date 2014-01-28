#include <stdint.h>
#include <stdbool.h>
#include "driverlib/flash.h"
#include "driverlib/gpio.h"
#include "peripheral_desc.h"
#include "inc/hw_memmap.h"
#include "map.h"

extern peripheral_desc desc;

void GPIOWrite(uint8_t index, uint8_t value)
{
    if(value == '0')
        GPIOPinWrite(GPIO_PORTF_BASE, 0xFF, 0x00);
    else
        GPIOPinWrite(GPIO_PORTF_BASE, 0xFF, MapPin(desc.ioPin[0].pin));
}
uint32_t CmdHandler(uint8_t *data, uint32_t size)
{
   uint8_t index;
   uint8_t pinval;
   switch(data[0]) {
       case 'P':
           index = data[1] - '0';
           desc.ioPin[index].port = data[2] - '0';
           desc.ioPin[index].pin = data[3] - '0';
           desc.ioPin[index].mode = data[4] - '0';
           break;

        case 'I':
           index = data[1] - '0';
           GPIOPinWrite(GPIO_PORTF_BASE,MapPin(desc.ioPin[index].pin),MapPin(desc.ioPin[index].pin));
           break;

        case 'i':
           index = data[1] - '0';
           GPIOPinWrite(GPIO_PORTF_BASE,MapPin(desc.ioPin[index].pin),0x00);
           break;


        default:
           desc.ioPin[0].pin = data[3] - '0';
   }

   SaveConfig();

	return size;
}
