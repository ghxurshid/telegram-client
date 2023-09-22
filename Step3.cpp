#include <stdio.h>
#include "Api.h"
#include "AES.h"
#include "SHA1.h"
#include "Utils.h"
#include "Step3.h"

Step3Request CreateStep3Request()
{
    Step3Request request;
    return request;
}

void ClearStep3Request(Step3Request& obj)
{
    ClearBiInteger(obj._gab);
    ClearByteArray(obj.newNonce);
}

void ClearStep3Response(Step3Response& obj)
{
    ClearAuthKey(obj.AuthKey);
}

Packet Step3RequestToBytes(Step3Request& request, Step2Response& response)
{
    int g;
    BigInteger dhPrime;
    BigInteger ga;

    request.newNonce = ByteArrarClone(response.NewNonce);
    AESKeyData key = AES_GenerateKeyDataFromNonces(response.ServerNonce, response.NewNonce);
    ByteArray plaintextAnswer = AES_Decrypt(key, response.EncryptedAnswer);    
     
    Packet packet;
    packet.currentIdx = 0;
    packet.bodySize = plaintextAnswer.size;
    packet.body = plaintextAnswer;

    ByteArray hashsum = PacketReadArray(packet, 20);   
    uint32_t  code    = PacketReadUint32(packet);

    if (code != 3045658042u)
    {
       printf("invalid dh_inner_data code: {%i}\n", code);
       return Packet();
    }

    ByteArray nonce = PacketReadArray(packet, 16);
     
    if (!CompareArray(nonce, response.Nonce))
    {
        printf("invalid nonce in encrypted answer\n");
        return Packet();
    }

    ByteArray serverNonce = PacketReadArray(packet, 16);
 
    if (!CompareArray(serverNonce, response.ServerNonce))
    {
        printf("invalid server nonce in encrypted answer\n");
        return Packet();
    }

    g = PacketReadUint32(packet);
    dhPrime = CreateBIFromBytes(1, PacketReadLongArray(packet));
    ga = CreateBIFromBytes(1, PacketReadLongArray(packet));
    int serverTime = PacketReadUint32(packet);
     
    BigInteger b = CreateBIFromRand(2048);
    BigInteger gb = BI_ModPow(CreateBIFromLong(g), b, dhPrime);

    request._gab = BI_ModPow(ga, b, dhPrime);
    request.timeOffset = serverTime - (int)(millis() / 1000);

    Packet clientDHInnerDataBytes = CreatePacket(128);
    clientDHInnerDataBytes.currentIdx += 20;
     
    PacketWriteUint32(clientDHInnerDataBytes, 0x6643b654);// clientDhInnerDataWriter.Write(0x6643b654); // client_dh_inner_data
    PacketWriteArray(clientDHInnerDataBytes, nonce);
    PacketWriteArray(clientDHInnerDataBytes, serverNonce);
    PacketWriteUint64(clientDHInnerDataBytes, 0); // TODO: retry_id
    PacketWriteArray(clientDHInnerDataBytes, BI_ToByteArrayUnsigned(gb)); 
        
    ByteArray buff = PacketGetBuffer(clientDHInnerDataBytes);
    ByteArray hash = SHA1_ComputeHash(buff);

    int currIndx = clientDHInnerDataBytes.currentIdx;
    clientDHInnerDataBytes.currentIdx = 28;
    PacketWriteArray(clientDHInnerDataBytes, hash);
    clientDHInnerDataBytes.currentIdx = currIndx;
      
    ByteArray clientDhInnerDataEncryptedBytes = AES_Encrypt(key, PacketGetBuffer(clientDHInnerDataBytes));  
    Packet setclientDhParamsBytes = CreatePacket(36 + clientDhInnerDataEncryptedBytes.size);
    
    PacketWriteUint32(setclientDhParamsBytes, 0xf5045f1f);
    PacketWriteArray(setclientDhParamsBytes, nonce);
    PacketWriteArray(setclientDhParamsBytes, serverNonce);
    PacketWriteLongArray(setclientDhParamsBytes, clientDhInnerDataEncryptedBytes);
 
    return setclientDhParamsBytes;     
}

Step3Response Step3ResponseFromBytes(Step3Request& request, Packet& packet)
{     
    uint32_t code = PacketReadUint32(packet); 

    if (code == 0x3bcbf734)
    {   // dh_gen_ok    
        ByteArray nonceFromServer = PacketReadArray(packet, 16);          
        ByteArray serverNonceFromServer = PacketReadArray(packet, 16);         
        ByteArray newNonceHash1 = PacketReadArray(packet, 16);
        AuthKey* _authKey = CreateAuthKey(request._gab);

        ByteArray newNonceHashCalculated = CalcNewNonceHash((*_authKey), request.newNonce, 1);

        if (!CompareArray(newNonceHash1, newNonceHashCalculated))
        {
            printf("invalid new nonce hash\n");
            return Step3Response();
        }
  
        Step3Response resp;
        
        resp.AuthKey = _authKey;
        resp.TimeOffset = request.timeOffset;
        
        return resp;
    }
    else if (code == 0x46dc1fb9)
    {   // dh_gen_retry
        printf("dh_gen_retry\n");
    }
    else if (code == 0xa69dae02)
    {   // dh_gen_fail
        printf("dh_gen_fail\n");
    }
    else
    {
        printf("dh_gen unknown: {%i}\n", code);
    }

    return Step3Response();
}
