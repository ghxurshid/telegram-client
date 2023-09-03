#include "CRC.h"

uint32_t hash;
uint32_t seed = 0xffffffff;
uint8_t  table[256];

ByteArray HashValue;

uint32_t polynomial = 3988292384u;

#pragma region Private
uint32_t CalculateHash(uint8_t* table, uint32_t seed, uint8_t* buffer, int start, int size)
{
    uint32_t num = seed;
    for (int i = start; i < start + size; i++)
    {
        num = (num >> 8) ^ table[buffer[i] ^ (num & 0xFF)];
    }

    return num;
}

void HashCore(uint8_t* buffer, int offset, int count)
{
    hash = CalculateHash(table, hash, buffer, offset, count);
}

ByteArray HashFinal()
{

}

void Initialize()
{
    hash = seed;
}

void InitializeTable()
{  
    for (int i = 0; i < 256; i++)
    {
        uint32_t num = (uint32_t)i;
        for (int j = 0; j < 8; j++)
        {
            num = (((num & 1) != 1) ? (num >> 1) : ((num >> 1) ^ polynomial));
        }

        table[i] = num;
    } 
}

ByteArray CaptureHashCodeAndReinitialize()
{
    HashValue = HashFinal(); 
  
    Initialize();
    return HashValue; 
}
#pragma endregion

#pragma region Public
ByteArray ComputeHash(uint8_t* buffer, int offset, int count)
{
    HashCore(buffer, offset, count);
    return CaptureHashCodeAndReinitialize();     
}
#pragma endregion

