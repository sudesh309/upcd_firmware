#include <stdint.h>
#include <stdbool.h>
#include "driverlib/flash.h"
#include "peripheral_desc.h"

#define FLASH_ADDR 0x0003FF00

extern peripheral_desc desc;

void SaveConfig(void)
{
    FlashErase(FLASH_ADDR);
    FlashProgram(&desc, FLASH_ADDR, sizeof(desc));
}
