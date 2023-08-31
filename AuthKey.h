#pragma once
#include <stdint.h> 

struct AuthKey
{
    uint8_t* key;

    uint64_t keyId;

    uint64_t auxHash;
};

