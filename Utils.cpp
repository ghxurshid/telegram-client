#include <stdio.h>
#include <stdint.h>
#include "Utils.h"
  
ByteArray ReadBytes(FILE* fp)
{
    uint8_t b = 0; fread(&b, sizeof(uint8_t), 1, fp);

    int num = 0;
    int num2 = 0;
    if (b == 254)
    {
        uint8_t b0 = 0; fread(&b0, sizeof(uint8_t), 1, fp);
        uint8_t b1 = 0; fread(&b1, sizeof(uint8_t), 1, fp);
        uint8_t b2 = 0; fread(&b2, sizeof(uint8_t), 1, fp);

        num = b0 | b1 << 8 | b2 << 16;
        num2 = num % 4;
    }
    else
    {
        num = b;
        num2 = (num + 1) % 4;
    }

    ByteArray bytes = CreateByteArray(num);
    fread(bytes.data, sizeof(uint8_t), num, fp);

    if (num2 > 0)
    {
        num2 = 4 - num2;
        fseek(fp, num2, SEEK_CUR);
    }

    return bytes;
}

void WriteBytes(ByteArray data, FILE* fp)
{
    int num;

    int   count = data.size;
    char* bytes = (char*)data.data;

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

