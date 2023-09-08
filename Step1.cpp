#include <stdio.h>
#include "Api.h"
#include "Step1.h"

Step1Request CreateStep1Request()
{
    Step1Request request;
    request.nonce = CreateByteArray(16);

    for (int i = 0; i < 16; i++)
    {
        request.nonce.data[i] = Rand8();
    }

    return request;
}

void ClearStep1Request(Step1Request& request)
{
    ClearByteArray(request.nonce);     
}

void ClearStep1Response(Step1Response& response)
{

}
 
int Step1RequestToBytes(Step1Request request, Packet& packet)
{
    int beginIndex = packet.currentIdx;
    uint32_t constructor = 1615239032;

    PacketWriteUint32(packet, constructor);
    PacketWriteArray(packet, request.nonce);

    ClearStep1Request(request);
         
    return packet.currentIdx - beginIndex;
}

Step1Response Step1ResponseFromBytes(Step1Request request, Packet& packet)
{ 
    uint32_t num = PacketReadUint32(packet);

    Step1Response response;
   
    if (num != 85337187)
    {
        printf("DoAuthentication: incorrect value of 'num' = %i\n", num);
        return response;
    }

    Packet

    nonce = new char[16];
    for (int i = 0; i < 16; i++)
    {
        nonce[i] = data[idx++];
    }

    servernonce = new char[16];
    for (int i = 0; i < 16; i++)
    {
        servernonce[i] = data[idx++];
    }

    count = 0;
    pqBytes = ReadBytesFromArray((char*)data, idx, count);
    idx += count;

    uint32_t num2 = (data[idx++] << 0) |
        (data[idx++] << 8) |
        (data[idx++] << 16) |
        (data[idx++] << 24);

    if (num2 != 481674261)
    {
        printf("DoAuthentication: Invalid vector constructor number %i\n", num2);
        return;
    }

    num3 = (data[idx++] << 0) |
        (data[idx++] << 8) |
        (data[idx++] << 16) |
        (data[idx++] << 24);

    fingerPrint = new char* [num3];
    for (int i = 0; i < num3; i++)
    {
        fingerPrint[i] = new char[8];
        for (int j = 0; j < 8; j++)
        {
            fingerPrint[i][j] = data[idx++];
        }
    }

    ClearPacket(packet);
}
