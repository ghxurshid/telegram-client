#include "CRC.h"

uint32_t hash;
uint32_t seed;
uint8_t  table[256];
ByteArray HashValue;
uint32_t polynomial;
bool initialized = false;
 
void Init()
{
    if (initialized) return;

    seed = 0xffffffff;
    hash = seed;
    polynomial = 3988292384u;

    for (int i = 0; i < 256; i++)
    {
        uint32_t num = (uint32_t)i;
        for (int j = 0; j < 8; j++)
        {
            num = (((num & 1) != 1) ? (num >> 1) : ((num >> 1) ^ polynomial));
        }

        table[i] = num;
    }

    initialized = true;
}

uint32_t ComputeCRC(uint8_t* buffer, int offset, int count)
{
    if (!initialized) Init();
    
    uint32_t num = seed;
    for (int i = offset; i < offset + count; i++)
    {
        num = (num >> 8) ^ table[buffer[i] ^ (num & 0xFF)];
    }

    hash = num;

    uint32_t finalHash = ~hash;
    hash = seed;
    return finalHash;
}
 