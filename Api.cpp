#include <stdlib.h>
#include <ctime>
#include "Api.h"



uint8_t Rand8()
{
	srand(time(0));
	return (uint8_t)(rand() % 256);
}

uint16_t Rand16()
{
	return (uint16_t)(rand() % 256 * 256);
}

uint32_t Rand32()
{
	return (uint32_t)rand();
}

uint64_t Rand64()
{
	return ((uint64_t)rand() | (uint64_t)rand() << 32);
}
