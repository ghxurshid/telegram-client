#pragma once
#include <stdint.h> 
#include "ByteArray.h"

struct AuthKey
{
    ByteArray key;
    uint64_t  keyId = 0;
    uint64_t  auxHash = 0;
};

AuthKey* CreateAuthKey(ByteArray data);
void ClearAuthKey(AuthKey* obj);

ByteArray CalcNewNonceHash(AuthKey& authKey, ByteArray newNonce, int number);

