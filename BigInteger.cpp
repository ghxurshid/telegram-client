#include <stdio.h>
#include "ByteArray.h"
#include "BigInteger.h"

static const int* ZeroMagnitude = new int[0];

const int BitsPerByte = 8;
const int BitsPerInt = 32;
const int BytesPerInt = 4;

const int64_t IMASK = 0xffffffffL;

static uint8_t bitCounts[] =
{
    0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1,
    2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4,
    4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3,
    4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5,
    3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2,
    3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3,
    3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6,
    7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6,
    5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5,
    6, 6, 7, 6, 7, 7, 8
};

int BitCount(BigInteger& bi)
{
    int bits = 0;
    if (bi.sign < 0)
    {
        // TODO Optimise this case
        bits = 0;
    }
    else {
        int sum = 0;
        for (int i = 0; i < bi.magLen; i++)
        {
            sum += bitCounts[(uint8_t)bi.magnitude[i]];
            sum += bitCounts[((uint8_t)bi.magnitude[i] >> 8)];
            sum += bitCounts[((uint8_t)bi.magnitude[i] >> 16)];
            sum += bitCounts[((uint8_t)bi.magnitude[i] >> 24)];
        }
        bits = sum;
    }

    return bits;
}

static int BitLen(int w)
{
    // Binary search - decision tree (5 tests, rarely 6)
    return (w < 1 << 15 ? (w < 1 << 7
        ? (w < 1 << 3 ? (w < 1 << 1
            ? (w < 1 << 0 ? (w < 0 ? 32 : 0) : 1)
            : (w < 1 << 2 ? 2 : 3)) : (w < 1 << 5
                ? (w < 1 << 4 ? 4 : 5)
                : (w < 1 << 6 ? 6 : 7)))
        : (w < 1 << 11
            ? (w < 1 << 9 ? (w < 1 << 8 ? 8 : 9) : (w < 1 << 10 ? 10 : 11))
            : (w < 1 << 13 ? (w < 1 << 12 ? 12 : 13) : (w < 1 << 14 ? 14 : 15)))) : (w < 1 << 23 ? (w < 1 << 19
                ? (w < 1 << 17 ? (w < 1 << 16 ? 16 : 17) : (w < 1 << 18 ? 18 : 19))
                : (w < 1 << 21 ? (w < 1 << 20 ? 20 : 21) : (w < 1 << 22 ? 22 : 23))) : (w < 1 << 27
                    ? (w < 1 << 25 ? (w < 1 << 24 ? 24 : 25) : (w < 1 << 26 ? 26 : 27))
                    : (w < 1 << 29 ? (w < 1 << 28 ? 28 : 29) : (w < 1 << 30 ? 30 : 31)))));
}

int BitLength(BigInteger& bi)
{
    if (bi.sign == 0) return 0;

    int indx = 0;

    for (;;)
    {
        if (indx >= bi.magLen)
            return 0;

        if (bi.magnitude[indx] != 0)
            break;

        ++indx;
    }

    // bit length for everything after the first int
    int bitLength = 32 * ((bi.magLen - indx) - 1);

    // and determine bitlength of first int
    int firstMag = bi.magnitude[indx];
    bitLength += BitLen(firstMag);

    // Check for negative powers of two
    if (bi.sign < 0 && ((firstMag & -firstMag) == firstMag))
    {
        do
        {
            if (++indx >= bi.magLen)
            {
                --bitLength;
                break;
            }
        } while (bi.magnitude[indx] == 0);
    }

    return bitLength;
}

BigInteger CreateBIFromBytes(int sign, ByteArray bytes)
{
    BigInteger bi;

    if (sign < -1 || sign > 1)
    {
        printf("Invalid sign value");
        return bi;
    }
    
    if (sign == 0)
    {
        //this.sign = 0;
        bi.magnitude = (int*)ZeroMagnitude;
    }
    else 
    {
        // copy bytes
        int len = 0;
        bi.magnitude = MakeMagnitude(bytes, len, 0, bytes.size);
        bi.magLen = len;
        bi.sign = bi.magLen < 1 ? 0 : sign; 
    }

    bi.nBits = BitCount(bi);
    bi.nBitLength = BitLength(bi);
    
    return bi;
}

BigInteger CreateBIFromLong(int64_t value)
{
    return BigInteger();
}

void ClearBiInteger(BigInteger& bigInteger)
{
}

ByteArray BI_ToByteArrayUnsigned(BigInteger bi)
{
    return ByteArray();
}
 
int* MakeMagnitude(ByteArray bytes, int& magLen, int offset, int length)
{
    int end = offset + length;

    if (end > bytes.size)
    {
        return (int*)ZeroMagnitude;
    }

    // strip leading zeros
    int firstSignificant;
    for (firstSignificant = offset; firstSignificant < end
        && bytes.data[firstSignificant] == 0; firstSignificant++)
    {
    }

    if (firstSignificant >= end)
    {
        return (int*)ZeroMagnitude;
    }

    int nInts = (end - firstSignificant + 3) / BytesPerInt;
    int bCount = (end - firstSignificant) % BytesPerInt;

    if (bCount == 0)
    {
        bCount = BytesPerInt;
    }

    if (nInts < 1)
    {
        return (int*)ZeroMagnitude;
    }

    int* mag = new int[nInts];  

    int v = 0;
    int magnitudeIndex = 0;
    for (int i = firstSignificant; i < end; ++i)
    {
        v <<= 8;
        v |= bytes.data[i] & 0xff;
        bCount--;
        if (bCount <= 0)
        {
            mag[magnitudeIndex] = v;
            magnitudeIndex++;
            bCount = BytesPerInt;
            v = 0;
        }
    }

    if (magnitudeIndex < nInts)
    {
        mag[magnitudeIndex] = v;
    }

    magLen = nInts;
    return mag;
}

int64_t LongValue(BigInteger bi)
{     
    if (bi.sign == 0)
        return 0;

    int64_t v;
    if (bi.magLen > 1)
    {
        v = ((int64_t)bi.magnitude[bi.magLen - 2] << 32)
            | (bi.magnitude[bi.magLen - 1] & IMASK);
    }
    else {
        v = (bi.magnitude[bi.magLen - 1] & IMASK);
    }

    return bi.sign < 0 ? -v : v;     
}
