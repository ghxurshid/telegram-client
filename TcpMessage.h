#pragma once
#include "ByteArray.h"
struct TcpMessage
{
	uint32_t SequanceNumber;
	ByteArray Body;
};

ByteArray Encode(TcpMessage message);
TcpMessage Decode(ByteArray body);

void ClearTcpMessage(TcpMessage& message);

