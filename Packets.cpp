#include "Packets.h"

Packet CreatePacket(int bodySz)
{
    Packet packet;
    packet.bodySize = bodySz;
    packet.currentIdx = 0;
    if (bodySz > 0) packet.body = CreateByteArray(bodySz + 32);

    return packet;
}
 
void ClearPacket(Packet& packet)
{
    ClearByteArray(packet.body);
    packet.bodySize = 0;
    packet.currentIdx = 0;
}
