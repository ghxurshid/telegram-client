#include <stdio.h>
#include "Api.h"
#include "Utils.h"
#include "Step1.h"

Step1Request CreateStep1Request()
{
    Step1Request request{};
    request.nonce = CreateByteArray(16);

    for (int i = 0; i < 16; i++)
    {
        request.nonce.data[i] = i;// Rand8();
    }

    return request;
}

void ClearStep1Request(Step1Request& request)
{
    ClearByteArray(request.nonce);     
}

void ClearStep1Response(Step1Response& response)
{
    ClearByteArray(response.Nonce);
    ClearByteArray(response.ServerNonce);
    ClearBiInteger(response.Pq);
    ClearByteArrayList(response.Fingerprints);
}
 
Packet Step1RequestToBytes(Step1Request& request)
{
    Packet packet = CreatePacket(20);
    int beginIndex = packet.currentIdx;
    uint32_t constructor = 1615239032;

    PacketWriteUint32(packet, constructor);
    PacketWriteArray(packet, request.nonce);
       
    return packet;
}

Step1Response Step1ResponseFromBytes(Step1Request& request, Packet& packet)
{ 
    uint32_t num = PacketReadUint32(packet);

    Step1Response response{};
   
    if (num != 85337187)
    {
        printf("DoAuthentication: incorrect value of 'num' = %i\n", num);
        return response;
    }

    ByteArray nonce = PacketReadArray(packet, 16);
    if (!CompareArray(nonce, request.nonce))
    {
        printf("Step1ResponseFromBytes: invalid nonce from server\n");
    }

    ByteArray serverNonce = PacketReadArray(packet, 16);
    ByteArray bytes       = PacketReadLongArray(packet);

    BigInteger pq = CreateBIFromBytes(1, bytes);
    uint32_t num2 = PacketReadUint32(packet);

    if (num2 != 481674261)
    {
        printf("Step1ResponseFromBytes: Invalid vector constructor number %i\n", num2);
    }

    int fingerPrintCount = PacketReadUint32(packet);
    ByteArrayList list = CreateByteArrayList(fingerPrintCount);

    for (int i = 0; i < fingerPrintCount; i++)
    {
        ByteArray item = PacketReadArray(packet, 8);

        list.arr[i] = new ByteArray();
        list.arr[i]->size = item.size;
        list.arr[i]->data = item.data;
    }

    ClearPacket(packet);
    ClearStep1Request(request); 
 
    response.Pq = pq;
    response.Nonce = nonce;
    response.Fingerprints = list;
    response.ServerNonce = serverNonce;

    return response;
}
