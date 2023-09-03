#include "TcpMessage.h"

ByteArray Encode(TcpMessage message)
{
	return CreateByteArray(5);
}

TcpMessage Decode(ByteArray body)
{
	return TcpMessage();
}

void ClearTcpMessage(TcpMessage& message)
{
	message.SequanceNumber = 0;
	ClearByteArray(message.Body);
}