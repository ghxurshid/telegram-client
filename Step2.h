#pragma once
#include "Step1.h"
#include "Packets.h" 

struct Step2Request
{
	ByteArray newNonce;
};

struct Step2Response
{
    ByteArray Nonce;
    ByteArray ServerNonce;
    ByteArray NewNonce;
    ByteArray EncryptedAnswer;
};

Step2Request CreateStep2Request();

void ClearStep2Request(Step2Request& request);
void ClearStep2Response(Step2Response& response);

Packet Step2RequestToBytes(Step2Request& request, Step1Response& response);
Step2Response Step2ResponseFromBytes(Step2Request& request, Packet& packet);