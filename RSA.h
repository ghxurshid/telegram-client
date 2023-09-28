#pragma once
#include "ByteArray.h"
#include "Packets.h"
#include "BigInteger.h"

struct RSAServerKey
{
	ByteArray fingerprint;
	BigInteger m;
	BigInteger e;
};

ByteArray RSA_Encrypt(ByteArray key, ByteArray data);

