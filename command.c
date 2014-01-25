#include <stdint.h>

uint32_t CmdHandler(uint8_t *data, uint32_t size)
{
	data[0] = data[0] - 1;
	return size;
}
