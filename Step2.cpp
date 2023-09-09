#include "Api.h"
#include "Step2.h"

Step2Request CreateStep2Request()
{
    Step2Request request{};
    request.newNonce = CreateByteArray(32);

    for (int i = 0; i < 32; i++)
    {
        request.newNonce.data[i] = Rand8();
    }

    return request;
}

void ClearStep2Request(Step2Request& request)
{
    ClearByteArray(request.newNonce);
}

void ClearStep2Response(Step2Response& response)
{
}

Packet Step2RequestToBytes(Step2Request& request, Step1Response& response)
{ 
    FactorizedPair factorizedPair = Factorizator.Factorize(pq);
    using MemoryStream memoryStream = new MemoryStream(255);
    using BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
    binaryWriter.Write(2211011308u);
    Serializers.Bytes.Write(binaryWriter, pq.ToByteArrayUnsigned());
    Serializers.Bytes.Write(binaryWriter, factorizedPair.Min.ToByteArrayUnsigned());
    Serializers.Bytes.Write(binaryWriter, factorizedPair.Max.ToByteArrayUnsigned());
    binaryWriter.Write(nonce);
    binaryWriter.Write(serverNonce);
    binaryWriter.Write(newNonce);
    byte[] array = null;
    byte[] buffer = null;
    foreach(byte[] fingerprint in fingerprints)
    {
        array = RSA.Encrypt(BitConverter.ToString(fingerprint).Replace("-", string.Empty), memoryStream.GetBuffer(), 0, (int)memoryStream.Position);
        if (array != null)
        {
            buffer = fingerprint;
            break;
        }
    }

    if (array == null)
    {
        throw new InvalidOperationException(string.Format("not found valid key for fingerprints: {0}", string.Join(", ", fingerprints)));
    }

    using MemoryStream memoryStream2 = new MemoryStream(1024);
    using BinaryWriter binaryWriter2 = new BinaryWriter(memoryStream2);
    binaryWriter2.Write(3608339646u);
    binaryWriter2.Write(nonce);
    binaryWriter2.Write(serverNonce);
    Serializers.Bytes.Write(binaryWriter2, factorizedPair.Min.ToByteArrayUnsigned());
    Serializers.Bytes.Write(binaryWriter2, factorizedPair.Max.ToByteArrayUnsigned());
    binaryWriter2.Write(buffer);
    Serializers.Bytes.Write(binaryWriter2, array);
    return memoryStream2.ToArray();
    return Packet();
}

Step2Response Step2ResponseFromBytes(Packet& packet)
{
    using MemoryStream input = new MemoryStream(response, writable: false);
    using BinaryReader binaryReader = new BinaryReader(input);
    uint num = binaryReader.ReadUInt32();
    switch (num)
    {
    case 2043348061u:
        throw new InvalidOperationException("server_DH_params_fail: TODO");
    default:
        throw new InvalidOperationException($"invalid response code: {num}");
    case 3504867164u:
    {
        byte[] nonce = binaryReader.ReadBytes(16);
        byte[] serverNonce = binaryReader.ReadBytes(16);
        byte[] encryptedAnswer = Serializers.Bytes.Read(binaryReader);
        return new Step2_Response
        {
            EncryptedAnswer = encryptedAnswer,
            ServerNonce = serverNonce,
            Nonce = nonce,
            NewNonce = newNonce
        };
    }
    }
}
