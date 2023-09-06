#pragma once
#include "ByteArray.h"
#include "Packets.h"
#include "BigInteger.h"

struct Step1Request
{
	uint8_t* nonce;
};

struct Step1Response
{
    uint8_t* Nonce;

    uint8_t* ServerNonce;

    BigInteger Pq;

    public List<byte[]> Fingerprints{ get; set; }
};

Step1Request CreateStep1Request();

void ClearStep1Request(Step1Request& request); 
void ClearStep1Response(Step1Response& response);

int Step1RequestToBytes(Step1Request request, Packet& packet);
Step1Response Step1ResponseFromBytes(Packet& packet);

