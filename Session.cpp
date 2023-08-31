#include <stdio.h>
#include "Session.h"

const int   ConnectionPort    = 443;
const char* ConnectionAddress = "149.154.175.100";

void WriteBytes(char* bytes, int count, FILE* fp);
 
ByteArray ToBytes(Session* session)
{
    return CreateByteArray(5);
}

Session* FromBytes(ByteArray buffer)
{
    return nullptr;
}

void Save(Session* session)
{
    FILE* fp;
    int ret = fopen_s(&fp, "session.dat", "w");
    if (fp == nullptr || session == nullptr) return;

    fwrite((void*)session->Id, sizeof(uint64_t), 1, fp);
    fwrite((void*)session->Sequence, sizeof(uint32_t), 1, fp);
    fwrite((void*)session->Salt, sizeof(uint64_t), 1, fp);
    fwrite((void*)session->LastMessageId, sizeof(uint64_t), 1, fp);
    fwrite((void*)session->TimeOffset, sizeof(uint32_t), 1, fp);
    WriteBytes((char*)ConnectionAddress, sizeof(ConnectionAddress), fp);
    fwrite((void*)ConnectionPort, sizeof(uint32_t), 1, fp);
    if (session->User != nullptr)
    {

    }
    else
    {
        fwrite((void*)0, sizeof(uint8_t), 1, fp);
    }

   
    fwrite((void*)session->Id, sizeof(uint64_t), 1, fp);
     
}

Session* TryLoadOrCreateNew()
{
    return nullptr;
}

uint64_t GenerateRandomUuint64_t()
{
    return 0;
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