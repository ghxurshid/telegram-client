#pragma once
#include "ByteArray.h"
struct TcpMessage
{
	int SequanceNumber;
	ByteArray Body;
};

ByteArray Encode(TcpMessage message);
TcpMessage Decode(ByteArray body);

