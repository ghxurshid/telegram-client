#pragma once
#include "BigInteger.h"

struct FactorizedPair
{
	BigInteger p;
	BigInteger q;
};

FactorizedPair Factorize(BigInteger pq);

