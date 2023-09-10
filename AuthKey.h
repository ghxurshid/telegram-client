#pragma once
#include <stdint.h> 
#include "ByteArray.h"

struct AuthKey
{
    ByteArray key;
    uint64_t keyId;
    uint64_t auxHash;
};

AuthKey CreateAuthKey(ByteArray data);
void ClearAuthKey(AuthKey& obj);

ByteArray CalcNewNonceHash(AuthKey* authKey, ByteArray newNonce, int number);

