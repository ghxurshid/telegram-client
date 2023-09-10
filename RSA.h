#pragma once
#include "ByteArray.h"
#include "Packets.h"

struct RSA
{
};

ByteArray RSA_Encrypt(ByteArray key, ByteArray data);

