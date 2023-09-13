#include "Api.h"
#include "RSA.h"
#include "Utils.h"
#include "Step2.h"

Step2Request CreateStep2Request()
{
    Step2Request request{};
    request.newNonce = CreateByteArray(32);

    for (int i = 0; i < 32; i++)
    {
        request.newNonce.data[i] = i;// Rand8();
    }

    return request;
}

void ClearStep2Request(Step2Request& request)
{
    ClearByteArray(request.newNonce);
}

void ClearStep2Response(Step2Response& response)
{
    ClearByteArray(response.Nonce);
    ClearByteArray(response.ServerNonce);
    ClearByteArray(response.NewNonce);
    ClearByteArray(response.EncryptedAnswer);
}

Packet Step2RequestToBytes(Step2Request& request, Step1Response& response)
{ 
    Packet packet = CreatePacket(255);
    FactorizedPair factorizedPair = Factorize(response.Pq); //TODO realize Factorize
     
    PacketWriteUint32(packet, 2211011308u);
    PacketWriteLongArray(packet, BI_ToByteArrayUnsigned(response.Pq)); 
    PacketWriteLongArray(packet, BI_ToByteArrayUnsigned(factorizedPair.p));
    PacketWriteLongArray(packet, BI_ToByteArrayUnsigned(factorizedPair.q));
    PacketWriteArray(packet, response.Nonce);
    PacketWriteArray(packet, response.ServerNonce);
    PacketWriteArray(packet, request.newNonce);
    
    ByteArray array{};
    ByteArray buffer{};

    for(int i = 0; i < response.Fingerprints.count; i ++)
    {         
        ReplaceByteArrayFromSign(response.Fingerprints.arr[i]);
        ByteArray key = response.Fingerprints.arr[i];
        array = RSA_Encrypt(key, PacketGetBuffer(packet));

        if (array.size > 0)
        {
            buffer = key;
            break;
        }         
    }

    ClearPacket(packet);

    if (array.size == 0)
    {
        printf("Step2RequestToBytes: not found valid key for fingerprints\n");
    }

    packet = CreatePacket(1024);
    PacketWriteUint32(packet, 3608339646u);
    PacketWriteArray(packet, response.Nonce);
    PacketWriteArray(packet, response.ServerNonce); 
    PacketWriteLongArray(packet, BI_ToByteArrayUnsigned(factorizedPair.p));
    PacketWriteLongArray(packet, BI_ToByteArrayUnsigned(factorizedPair.q));
    PacketWriteArray(packet, buffer);
    PacketWriteLongArray(packet, array);
     
    return packet;
}

Step2Response Step2ResponseFromBytes(Step2Request& request, Packet& packet)
{     
    uint32_t num = PacketReadUint32(packet);
    Step2Response response;

    switch (num)
    {
        case 2043348061u:
            printf("Step2ResponseFromBytes: server_DH_params_fail: TODO\n");
        default:
            printf("Step2ResponseFromBytes: invalid response code: %i\n", num);
        case 3504867164u:
        {
            response.Nonce = PacketReadArray(packet, 16);
            response.ServerNonce = PacketReadArray(packet, 16);
            response.EncryptedAnswer = PacketReadLongArray(packet);
            response.NewNonce = request.newNonce;            
        }
    }

    return response;
}
