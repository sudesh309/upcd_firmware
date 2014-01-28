#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/timer.h"
#include "driverlib/usb.h"
#include "driverlib/flash.h"
#include "usblib/usblib.h"
#include "usblib/device/usbdevice.h"
#include "upcd.h"
#include "peripheral_desc.h"
#include "map.h"

#define RED_LED   GPIO_PIN_1
#define BLUE_LED  GPIO_PIN_2
#define GREEN_LED GPIO_PIN_3
#define SYSTICKS_PER_SECOND 100
#define SYSTICK_PERIOD_MS (1000/SYSTICKS_PER_SECOND)
#define FLASH_ADDR 0x0003FF00

uint32_t sysTick;

void SysTickIntHandler(void)
{
	sysTick++;
}
	
extern upcd_device UPCDDev;

peripheral_desc desc;

int
main(void)
{
    
    
    
    SysCtlClockSet(SYSCTL_SYSDIV_4|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|
                    SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);
    GPIOPinTypeUSBAnalog(GPIO_PORTD_BASE, GPIO_PIN_4 | GPIO_PIN_5 );

    SysTickPeriodSet(SysCtlClockGet()/SYSTICKS_PER_SECOND);

    SysTickIntEnable();
    SysTickEnable();
    
    USBStackModeSet(0,eUSBModeForceDevice,0);

  // desc.ioPin[0].pin = 3;

  // SaveConfig();

     peripheral_desc *fptr = (peripheral_desc *)FLASH_ADDR;
     desc = *fptr;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, RED_LED|BLUE_LED|GREEN_LED);

    UPCDInit(0,&UPCDDev);


    while(1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, 0xFF, MapPin(desc.ioPin[0].pin));
        SysCtlDelay(5000000);
        GPIOPinWrite(GPIO_PORTF_BASE, 0xFF,0x00);
        SysCtlDelay(5000000);
    }
}
