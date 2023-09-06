#pragma once
#include "ByteArray.h"

struct Packet
{
	int bodySize;
	int currentIdx;	
	ByteArray body;
};

Packet CreatePacket(int bodySz);
void ClearPacket(Packet& packet);

 





