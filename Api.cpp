#include <stdlib.h>
#include <ctime>
#include <ctime>
#include <random>
#include <chrono> 
#include "Api.h"

uint8_t Rand8()
{
	srand(time(0));
	return (uint8_t)(rand() % 256);
}

uint16_t Rand16()
{
	return (uint16_t)(rand() % (256 * 256));
}

uint32_t Rand32()
{
	return (uint32_t)rand();
}

uint64_t Rand64()
{
	return ((uint64_t)rand() | (uint64_t)rand() << 32);
}

uint64_t millis()
{
	return std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
}
