#pragma once
#include "ByteArray.h"

struct BigInteger
{
    int sign = 0;

    int magLen = 0;
    int* magnitude;

    int nBits = -1;

    int nBitLength = -1;

    int64_t mQuote = -1L;
};

BigInteger CreateBIFromLong(int64_t value);
BigInteger CreateBIFromRand(int sizeInBits);
BigInteger CreateBIFromBytes(int sign, ByteArray bytes);

void ClearBiInteger(BigInteger& bigInteger);
ByteArray BI_ToByteArrayUnsigned(BigInteger bi); 
int* MakeMagnitude(ByteArray bytes, int& magLen, int offset, int length);
int64_t LongValue(BigInteger bi);

BigInteger BI_Min(BigInteger bi1, BigInteger bi2);
BigInteger BI_Max(BigInteger bi1, BigInteger bi2);

BigInteger BI_ModPow(BigInteger bi, BigInteger& exponent, BigInteger& m);
