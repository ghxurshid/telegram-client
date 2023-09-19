#include <stdint.h>
#include "Api.h"
#include "Factorizator.h"

int64_t GCD(int64_t a, int64_t b)
{
    while (a != 0 && b != 0)
    {
        while ((b & 1) == 0)
        {
            b >>= 1;
        }
        while ((a & 1) == 0)
        {
            a >>= 1;
        }
        if (a > b)
        {
            a -= b;
        }
        else {
            b -= a;
        }
    }
    return b == 0 ? a : b;
}

int64_t findSmallMultiplierLopatin(int64_t what)
{
    long g = 0;
    for (int i = 0; i < 3; i++)
    {
        int q = ((Rand8() % 128) & 15) + 17;
        int64_t x = Rand32() % (1000000000) + 1, y = x;
        int lim = 1 << (i + 18);
        for (int j = 1; j < lim; j++)
        {
            long a = x, b = x, c = q;
            while (b != 0)
            {
                if ((b & 1) != 0)
                {
                    c += a;
                    if (c >= what)
                    {
                        c -= what;
                    }
                }
                a += a;
                if (a >= what)
                {
                    a -= what;
                }
                b >>= 1;
            }
            x = c;
            int64_t z = x < y ? y - x : x - y;
            g = GCD(z, what);
            if (g != 1)
            {
                break;
            }
            if ((j & (j - 1)) == 0)
            {
                y = x;
            }
        }
        if (g > 1)
        {
            break;
        }
    }

    int64_t p = what / g;
    return p < g ? p : g;
}


FactorizedPair Factorize(BigInteger pq)
{
    if (pq.nBitLength < 64)
    {
        int64_t pqlong = LongValue(pq);
        int64_t divisor = findSmallMultiplierLopatin(pqlong);

        FactorizedPair pair;
        pair.p = CreateBIFromLong(divisor);
        pair.q = CreateBIFromLong(pqlong / divisor);
        return pair;
    }
    else
    {
        return FactorizedPair();
    }
}