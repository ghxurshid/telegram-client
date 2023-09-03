#include <stdio.h>
#include <stdint.h>
#include "Utils.h"

char* ReadBytes(FILE* fp)
{
    uint8_t b; fread(&b, sizeof(uint8_t), 1, fp);

    int num;
    int num2;
    if (b == 254)
    {
        uint8_t b0; fread(&b0, sizeof(uint8_t), 1, fp);
        uint8_t b1; fread(&b1, sizeof(uint8_t), 1, fp);
        uint8_t b2; fread(&b2, sizeof(uint8_t), 1, fp);

        num = b0 | b1 << 8 | b2 << 16;
        num2 = num % 4;
    }
    else
    {
        num = b;
        num2 = (num + 1) % 4;
    }

    char* bytes = new char[num];
    fread(bytes, sizeof(uint8_t), num, fp);

    if (num2 > 0)
    {
        num2 = 4 - num2;
        fseek(fp, num2, SEEK_CUR);
    }

    return bytes;
}

void WriteBytes(char* bytes, int count, FILE* fp)
{
    int num;
    if (count < 254)
    {
        num = (count + 1) % 4;
        if (num != 0)
        {
            num = 4 - num;
        }

        fwrite((void*)count, sizeof(uint8_t), 1, fp);
        fwrite((void*)bytes, sizeof(uint8_t), count, fp);
    }
    else
    {
        num = count % 4;
        if (num != 0)
        {
            num = 4 - num;
        }

        fwrite((void*)254, sizeof(uint8_t), 1, fp);
        fwrite((void*)count, sizeof(uint8_t), 1, fp);
        fwrite((void*)(count >> 8), sizeof(uint8_t), 1, fp);
        fwrite((void*)(count >> 16), sizeof(uint8_t), 1, fp);
        fwrite((void*)bytes, sizeof(uint8_t), count, fp);
    }

    for (int i = 0; i < num; i++)
    {
        fwrite((void*)0, sizeof(uint8_t), 1, fp);
    }
}