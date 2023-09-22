#include <stdio.h>
#include "Api.h"
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

static uint8_t rndMask[] = {255, 127, 63, 31, 15, 7, 3, 1};

BigInteger CreateBIFromRand(int sizeInBits)
{
    if (sizeInBits < 0)
    {
        printf("sizeInBits must be non-negative\n");
        return BigInteger();
    }
    
    BigInteger bi;

    bi.nBits = -1;
    bi.nBitLength = -1;

    if (sizeInBits == 0)
    {
        //				this.sign = 0;
        bi.magnitude = (int*)ZeroMagnitude;
        return bi;
    }

    int nBytes = GetByteLength(sizeInBits);
    ByteArray b = CreateByteArray(nBytes);
    for (int i = 0; i < nBytes; i++)
    {
        b.data[i] = Rand8();
    }   

    // strip off any excess bits in the MSB
    b.data[0] &= rndMask[BitsPerByte * nBytes - sizeInBits];

    bi.magnitude = MakeMagnitude(b, bi.magLen, 0, nBytes);
    bi.sign = bi.magLen < 1 ? 0 : 1;
    return BigInteger();
}

void ClearBiInteger(BigInteger& bigInteger)
{
}

int GetByteLength(int nBits)
{
    return (nBits + BitsPerByte - 1) / BitsPerByte;
}

ByteArray ToByteArray(BigInteger bi, bool _unsigned = false)
{
    if (bi.sign == 0)
        return _unsigned ? CreateByteArray(0) : CreateByteArray(1);

    int nBits = (_unsigned && bi.sign > 0)
        ? bi.nBitLength
        : bi.nBitLength + 1;

    int nBytes = GetByteLength(nBits);
    ByteArray bytes = CreateByteArray(nBytes);
     

    int magIndex = bi.magLen;
    int bytesIndex = bytes.size;

    if (bi.sign > 0)
    {
        while (magIndex > 1)
        {
            uint32_t mag = (uint32_t)bi.magnitude[--magIndex];
            bytes.data[--bytesIndex] = (uint8_t)mag;
            bytes.data[--bytesIndex] = (uint8_t)(mag >> 8);
            bytes.data[--bytesIndex] = (uint8_t)(mag >> 16);
            bytes.data[--bytesIndex] = (uint8_t)(mag >> 24);
        }

        uint32_t lastMag = (uint32_t)bi.magnitude[0];
        while (lastMag > 255)
        {
            bytes.data[--bytesIndex] = (uint8_t)lastMag;
            lastMag >>= 8;
        }

        bytes.data[--bytesIndex] = (uint8_t)lastMag;
    }
    else // sign < 0
    {
        bool carry = true;

        while (magIndex > 1)
        {
            uint32_t mag = ~((uint32_t)bi.magnitude[--magIndex]);

            if (carry)
            {
                carry = (++mag == 0);
            }

            bytes.data[--bytesIndex] = (uint8_t)mag;
            bytes.data[--bytesIndex] = (uint8_t)(mag >> 8);
            bytes.data[--bytesIndex] = (uint8_t)(mag >> 16);
            bytes.data[--bytesIndex] = (uint8_t)(mag >> 24);
        }

        uint32_t lastMag = (uint32_t)bi.magnitude[0];

        if (carry)
        {
            // Never wraps because magnitude[0] != 0
            --lastMag;
        }

        while (lastMag > 255)
        {
            bytes.data[--bytesIndex] = (uint8_t)~lastMag;
            lastMag >>= 8;
        }

        bytes.data[--bytesIndex] = (uint8_t)~lastMag;

        if (bytesIndex > 0)
        {
            bytes.data[--bytesIndex] = 255;
        }
    }

    return bytes;
}

ByteArray BI_ToByteArrayUnsigned(BigInteger bi)
{
    return ToByteArray(bi, true);
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

int CompareNoLeadingZeroes(int xIndx, BigInteger x, int yIndx, BigInteger y)
{
    int diff = (x.magLen - y.magLen) - (xIndx - yIndx);

    if (diff != 0)
    {
        return diff < 0 ? -1 : 1;
    }

    // lengths of magnitudes the same, test the magnitude values

    while (xIndx < x.magLen)
    {
        uint32_t v1 = (uint32_t)x.magnitude[xIndx++];
        uint32_t v2 = (uint32_t)y.magnitude[yIndx++];

        if (v1 != v2)
            return v1 < v2 ? -1 : 1;
    }

    return 0;
}

int CompareTo(BigInteger bi1, BigInteger bi2)
{
    return bi1.sign < bi2.sign ? -1
        : bi1.sign > bi2.sign ? 1
        : bi1.sign == 0 ? 0
        : bi1.sign * CompareNoLeadingZeroes(0, bi1, 0, bi2);
}

BigInteger BI_Min(BigInteger bi1, BigInteger bi2)
{
    return CompareTo(bi1, bi2) < 0 ? bi1 : bi2;    
}

BigInteger BI_Max(BigInteger bi1, BigInteger bi2)
{
    return CompareTo(bi1, bi2) > 0 ? bi1 : bi2;
}

BigInteger BI_ModPow(BigInteger bi, BigInteger& exponent, BigInteger& m)
{
    return BigInteger(); //TODO
}
