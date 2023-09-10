#pragma once
struct BigInteger
{
    int sign;

    int magnitude[8];

    int nBits = -1;

    int nBitLength = -1;

    long mQuote = -1L;
};

struct FactorizedPair
{
	BigInteger p;
	BigInteger q;
};

BigInteger CreateBigInteger(int sign, ByteArray bytes);
void ClearBiInteger(BigInteger& bigInteger);

ByteArray BI_ToByteArrayUnsigned(BigInteger bi);

FactorizedPair Factorize(BigInteger pq);