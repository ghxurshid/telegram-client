#pragma once
#include "ByteArray.h"

long GetNewMessageId();
void MtPlain_Send(ByteArray data);
ByteArray MtPlain_Receive();