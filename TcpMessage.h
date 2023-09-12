#pragma once
#include "ByteArray.h"
struct TcpMessage
{
	uint32_t SequanceNumber = 0;
	ByteArray Body;
};

ByteArray Encode(TcpMessage message);
TcpMessage Decode(ByteArray body);

void ClearTcpMessage(TcpMessage& message);

