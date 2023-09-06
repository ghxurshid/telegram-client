#include "Packets.h"

Packet CreatePacket(int bodySz)
{
    Packet packet;
    packet.currentIdx = 32;
    packet.bodySize = bodySz;    
    if (bodySz > 0) packet.body = CreateByteArray(bodySz + 32);

    return packet;
}
 
void ClearPacket(Packet& packet)
{
    ClearByteArray(packet.body);
    packet.bodySize = 0;
    packet.currentIdx = 0;
}

int PacketWriteUint8(Packet& packet, uint8_t value)
{
    int indx = packet.currentIdx;
    int sizeOf = sizeof(uint8_t);

    if (indx + sizeOf >= packet.body.size) return 0;

    packet.body.data[indx + 0] = (value >> 0) & 0xFF;
    packet.currentIdx += sizeOf;

    return packet.currentIdx - indx;
}

int PacketWriteUint16(Packet& packet, uint16_t value)
{
    int indx = packet.currentIdx;
    int sizeOf = sizeof(uint16_t);

    if (indx + sizeOf >= packet.body.size) return 0;

    packet.body.data[indx + 0] = (value >> 0) & 0xFF;
    packet.body.data[indx + 1] = (value >> 8) & 0xFF;
    packet.currentIdx += sizeOf;

    return packet.currentIdx - indx;
}

int PacketWriteUint32(Packet& packet, uint32_t value)
{ 
    int indx = packet.currentIdx;
    int sizeOf = sizeof(uint32_t);

    if (indx + sizeOf >= packet.body.size) return 0;

    packet.body.data[indx + 0] = (value >> 0 ) & 0xFF;
    packet.body.data[indx + 1] = (value >> 8 ) & 0xFF;
    packet.body.data[indx + 2] = (value >> 16) & 0xFF;
    packet.body.data[indx + 3] = (value >> 24) & 0xFF;
    packet.currentIdx += sizeOf;

    return packet.currentIdx - indx;
}

int PacketWriteUint64(Packet& packet, uint64_t value)
{
    int indx = packet.currentIdx;
    int sizeOf = sizeof(uint64_t);

    if (indx + sizeOf >= packet.body.size) return 0;

    packet.body.data[indx + 0] = (value >> 0) & 0xFF;
    packet.body.data[indx + 1] = (value >> 8) & 0xFF;
    packet.body.data[indx + 2] = (value >> 16) & 0xFF;
    packet.body.data[indx + 3] = (value >> 24) & 0xFF;

    packet.body.data[indx + 4] = (value >> 32) & 0xFF;
    packet.body.data[indx + 5] = (value >> 40) & 0xFF;
    packet.body.data[indx + 6] = (value >> 48) & 0xFF;
    packet.body.data[indx + 7] = (value >> 56) & 0xFF;
    packet.currentIdx += sizeOf;

    return packet.currentIdx - indx;
}

int PacketWriteArray(Packet& packet, ByteArray arr)
{
    int beginIndex = packet.currentIdx;

    for (int i = 0; i < arr.size; i++)
    {
        if (packet.currentIdx >= packet.body.size) break;
        packet.body.data[packet.currentIdx++] = arr.data[i];
    }

    return packet.currentIdx - beginIndex;
}


uint8_t PacketReadUint8(Packet& packet)
{
    int indx = packet.currentIdx;
    int sizeOf = sizeof(uint8_t);

    if (packet.body.size <= indx + sizeOf) return 0;

    packet.currentIdx += sizeOf;

    uint8_t value = (uint8_t)(packet.body.data[indx + 0] << 0);

    return value;
}

uint16_t PacketReadUint16(Packet& packet)
{
    int indx = packet.currentIdx;
    int sizeOf = sizeof(uint16_t);

    if (packet.body.size <= indx + sizeOf) return 0;

    packet.currentIdx += sizeOf;

    uint16_t value = (uint16_t)(packet.body.data[indx + 0] << 0) |
                     (uint16_t)(packet.body.data[indx + 1] << 8) ;

    return value;
}

uint32_t PacketReadUint32(Packet& packet)
{
    int indx = packet.currentIdx;
    int sizeOf = sizeof(uint32_t);

    if (packet.body.size <= indx + sizeOf) return 0;

    packet.currentIdx += sizeOf;

    uint32_t value = (uint32_t)(packet.body.data[indx + 0] << 0 ) |
                     (uint32_t)(packet.body.data[indx + 1] << 8 ) |
                     (uint32_t)(packet.body.data[indx + 2] << 16) |
                     (uint32_t)(packet.body.data[indx + 3] << 24) ;

    return value;
}

uint64_t PacketReadUint64(Packet& packet)
{
    int indx = packet.currentIdx;
    int sizeOf = sizeof(uint64_t);

    if (packet.body.size <= indx + sizeOf) return 0;

    packet.currentIdx += sizeOf;

    uint64_t value = (uint64_t)(packet.body.data[indx + 0] << 0 ) |
                     (uint64_t)(packet.body.data[indx + 1] << 8 ) |
                     (uint64_t)(packet.body.data[indx + 2] << 16) |
                     (uint64_t)(packet.body.data[indx + 3] << 24) |
                     (uint64_t)(packet.body.data[indx + 4] << 32) |
                     (uint64_t)(packet.body.data[indx + 5] << 40) |
                     (uint64_t)(packet.body.data[indx + 6] << 48) |
                     (uint64_t)(packet.body.data[indx + 7] << 56) ;

    return value;
}

