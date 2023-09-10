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

int PacketWriteUint8 (Packet& packet, uint8_t  value);
int PacketWriteUint16(Packet& packet, uint16_t value);
int PacketWriteUint32(Packet& packet, uint32_t value);
int PacketWriteUint64(Packet& packet, uint64_t value);

int PacketWriteArray (Packet& packet, ByteArray arr);
int PacketWriteLongArray(Packet& packet, ByteArray arr);

uint8_t  PacketReadUint8 (Packet& packet);
uint16_t PacketReadUint16(Packet& packet);
uint32_t PacketReadUint32(Packet& packet);
uint64_t PacketReadUint64(Packet& packet);

ByteArray PacketReadArray(Packet& packet, int count);
ByteArray PacketReadLongArray(Packet& packet);

ByteArray PacketGetBuffer(Packet& packet);

 





