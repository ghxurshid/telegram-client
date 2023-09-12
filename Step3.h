#pragma once
#include "Step2.h"
#include "Packets.h"
#include "AuthKey.h"
#include "ByteArray.h"
#include "BigInteger.h"

struct Step3Request
{
    BigInteger _gab;
    ByteArray newNonce;
    int timeOffset = 0;
};

struct Step3Response
{
    AuthKey* AuthKey = nullptr;
    int TimeOffset = 0;
};

Step3Request CreateStep3Request();

void ClearStep3Request(Step3Request& obj);
void ClearStep3Response(Step3Response& obj);

Packet Step3RequestToBytes(Step3Request& request, Step2Response& response);
Step3Response Step3ResponseFromBytes(Step3Request& request, Packet& packet);
