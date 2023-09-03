#pragma once
#include <stdint.h> 
#include "ByteArray.h"

struct AuthKey
{
    uint8_t* key;

    uint64_t keyId;

    uint64_t auxHash;
};

AuthKey* CreateAuthKey(char* data);

ByteArray CalcNewNonceHash(AuthKey* authKey, ByteArray newNonce, int number);

