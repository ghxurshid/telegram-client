#pragma once
#include "ByteArray.h"

struct BigInteger
{
    int sign = 0;

    int magLen = 0;
    int* magnitude;

    int nBits = -1;

    int nBitLength = -1;

    long mQuote = -1L;
};
 
BigInteger CreateBIFromBytes(int sign, ByteArray bytes);
BigInteger CreateBIFromLong(int64_t value);
void ClearBiInteger(BigInteger& bigInteger);
ByteArray BI_ToByteArrayUnsigned(BigInteger bi); 
int* MakeMagnitude(ByteArray bytes, int& magLen, int offset, int length);
int64_t LongValue(BigInteger bi);