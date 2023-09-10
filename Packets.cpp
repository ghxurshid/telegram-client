#include "Packets.h"
#include "Utils.h"

Packet CreatePacket(int bodySz)
{
    Packet packet;
    packet.currentIdx = 28;
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

int PacketWriteLongArray(Packet& packet, ByteArray arr)
{
    int num;    
    int count = arr.size;
    int beginIndex = packet.currentIdx;
    if (count < 254)
    {
        num = (count + 1) % 4;
        if (num != 0)
        {
            num = 4 - num;
        }

        PacketWriteUint8(packet, (uint8_t)count);
        PacketWriteArray(packet, arr);
    }
    else
    {
        num = count % 4;
        if (num != 0)
        {
            num = 4 - num;
        }

        PacketWriteUint8(packet, (uint8_t)254); 
        PacketWriteUint8(packet, (uint8_t)count); 
        PacketWriteUint8(packet, (uint8_t)(count >> 8)); 
        PacketWriteUint8(packet, (uint8_t)(count >> 16)); 
        PacketWriteArray(packet, arr); 
    }

    for (int i = 0; i < num; i++)
    {
        PacketWriteUint8(packet, (uint8_t)0);
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

ByteArray PacketReadArray(Packet& packet, int count)
{
    return ByteArray();
}

ByteArray PacketReadLongArray(Packet& packet)
{
    
    uint8_t b = PacketReadUint8(packet);

    int num;
    int num2;
    if (b == 254)
    {
        uint8_t b0 = PacketReadUint8(packet);
        uint8_t b1 = PacketReadUint8(packet);
        uint8_t b2 = PacketReadUint8(packet);

        num = b0 | b1 << 8 | b2 << 16;
        num2 = num % 4;
    }
    else
    {
        num = b;
        num2 = (num + 1) % 4;
    }

    ByteArray arr = PacketReadArray(packet, num);
     

    if (num2 > 0)
    {
        num2 = 4 - num2;
        PacketReadArray(packet, num2);
    }
     
    return arr;     
}

ByteArray PacketGetBuffer(Packet& packet)
{
    ByteArray buff;

    if (packet.body.size > 32)
    {
        buff.size = packet.bodySize;
        buff.data = packet.body.data + 28;
    }
    
    return buff;
}

char* ReadBytesFromArray(char* buffer, int offset, int& count)
{
    
}

bool CompareArray(ByteArray arr1, ByteArray arr2)
{
    if (arr1.size != arr2.size) return false;

    for (int i = 0; i < arr1.size; i++)
    {
        if (arr1.data[i] != arr2.data[i])
            return false;
    }

    return true;
}

void ReplaceByteArrayFromSign(ByteArray& arr)
{
    for (int i = 0; i < arr.size; i++)
    {
        if (arr.data[i] == '-')
        {
            for (int j = i; j < arr.size - 1; j++) arr.data[j] = arr.data[j + 1];
            arr.size -= 1;
            i--;
        }
    }
}

