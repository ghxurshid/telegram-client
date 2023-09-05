#pragma once
#include "ByteArray.h"

struct Step1Request
{
};

struct Step1Response
{
};

Step1Request* CreateStep1Request();

void ClearStep1Request(Step1Request* request); 
void ClearStep1Response(Step1Response* response);

ByteArray Step1RequestToBytes(Step1Request* request);
Step1Response* Step1ResponseFromBytes(ByteArray bytes);

