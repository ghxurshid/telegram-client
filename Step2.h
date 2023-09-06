#pragma once
#include "ByteArray.h"

struct Step2Request
{
};

struct Step2Response
{
};

Step2Request CreateStep2Request();

void ClearStep2Request(Step2Request& request);
void ClearStep2Response(Step2Response& response);

ByteArray Step2RequestToBytes(Step2Request request);
Step2Response Step2ResponseFromBytes(ByteArray bytes);