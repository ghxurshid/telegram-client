#include "Api.h"
#include "Step1.h"


Step1Request CreateStep1Request()
{
    Step1Request request;
    request.nonce = new uint8_t[16];

    for (int i = 0; i < 16; i++)
    {
        request.nonce[i] = Rand8();
    }

    return request;
}

void ClearStep1Request(Step1Request& request)
{
    if (request.nonce == nullptr) return;
    delete[] request.nonce;
}

void ClearStep1Response(Step1Response& response)
{

}
 
int Step1RequestToBytes(Step1Request request, Packet& packet)
{
    uint32_t constructor = 1615239032;
    PacketWriteUint32(packet, constructor);
    for (int i = 0; i < 16; i++) PacketWriteUint8(packet, request.nonce[i]);
     
    return ByteArray();
}

Step1Response Step1ResponseFromBytes(Packet& packet)
{
     
}
