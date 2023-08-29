#pragma once
#include "ByteArray.h"
#include "TcpMessage.h"

namespace TcpTransport
{
	void Connect();

	void Disconnect();

	unsigned long AvailableBytes();

	void Send(ByteArray data);

	TcpMessage Receive();
}
