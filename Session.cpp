#include <iostream>
#include <stdio.h>

#include "Session.h"
 
ByteArray ToBytes(Session* session)
{
    return CreateByteArray(5);
}

Session* FromBytes(ByteArray buffer)
{
    return nullptr;
}

void Save()
{
    FILE* file = fopen("session.dat", "wb");
     
}

Session* TryLoadOrCreateNew()
{
    return nullptr;
}

unsigned long GenerateRandomUlong()
{
    return 0;
} 