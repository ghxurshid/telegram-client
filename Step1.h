#pragma once
#include "ByteArray.h"
#include "Packets.h"
#include "BigInteger.h"

struct Step1Request
{
	ByteArray nonce;
};

struct Step1Response
{
    ByteArray Nonce;
    ByteArray ServerNonce;
    BigInteger Pq;
    ByteArrayList Fingerprints;     
};

Step1Request CreateStep1Request();

void ClearStep1Request(Step1Request& request); 
void ClearStep1Response(Step1Response& response);

Packet Step1RequestToBytes(Step1Request& request);
Step1Response Step1ResponseFromBytes(Step1Request& request, Packet& packet);

