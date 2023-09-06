#pragma once
#include "ByteArray.h"

struct Step3Request
{
};

struct Step3Response
{
};

Step3Request CreateStep3Request();

void ClearStep3Request(Step3Request& request);
void ClearStep3Response(Step3Response& responce);

ByteArray Step3RequestToBytes(Step3Request request);
Step3Response Step3ResponseFromBytes(ByteArray bytes);
