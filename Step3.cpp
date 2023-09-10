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

ByteArray Step3RequestToBytes(Step3Request& request, Step2Response& response)
{
    request.newNonce = ByteArrarClone(response.NewNonce);
    /*AESKeyData key = AES.GenerateKeyDataFromNonces(serverNonce, newNonce);
    byte[] buffer = AES.DecryptAES(key, encryptedAnswer);
    int num2;
    BigInteger m;
    BigInteger bigInteger;
    using (MemoryStream input = new MemoryStream(buffer))
    {
        using BinaryReader binaryReader = new BinaryReader(input);
        byte[] array = binaryReader.ReadBytes(20);
        uint num = binaryReader.ReadUInt32();
        if (num != 3045658042u)
        {
            throw new InvalidOperationException($"invalid dh_inner_data code: {num}");
        }

        byte[] first = binaryReader.ReadBytes(16);
        if (!first.SequenceEqual(nonce))
        {
            throw new InvalidOperationException("invalid nonce in encrypted answer");
        }

        byte[] first2 = binaryReader.ReadBytes(16);
        if (!first2.SequenceEqual(serverNonce))
        {
            throw new InvalidOperationException("invalid server nonce in encrypted answer");
        }

        num2 = binaryReader.ReadInt32();
        m = new BigInteger(1, Serializers.Bytes.Read(binaryReader));
        bigInteger = new BigInteger(1, Serializers.Bytes.Read(binaryReader));
        int num3 = binaryReader.ReadInt32();
        timeOffset = num3 - (int)(Convert.ToInt64((DateTime.UtcNow - new DateTime(1970, 1, 1)).TotalMilliseconds) / 1000);
    }

    BigInteger exponent = new BigInteger(2048, new Random());
    BigInteger bigInteger2 = BigInteger.ValueOf(num2).ModPow(exponent, m);
    _gab = bigInteger.ModPow(exponent, m);
    byte[] plaintext;
    using (MemoryStream memoryStream = new MemoryStream())
    {
        using BinaryWriter binaryWriter = new BinaryWriter(memoryStream);
        binaryWriter.Write(1715713620);
        binaryWriter.Write(nonce);
        binaryWriter.Write(serverNonce);
        binaryWriter.Write(0L);
        Serializers.Bytes.Write(binaryWriter, bigInteger2.ToByteArrayUnsigned());
        using MemoryStream memoryStream2 = new MemoryStream();
        using BinaryWriter binaryWriter2 = new BinaryWriter(memoryStream2);
        using SHA1 sHA = new SHA1Managed();
        binaryWriter2.Write(sHA.ComputeHash(memoryStream.GetBuffer(), 0, (int)memoryStream.Position));
        binaryWriter2.Write(memoryStream.GetBuffer(), 0, (int)memoryStream.Position);
        plaintext = memoryStream2.ToArray();
    }

    byte[] data = AES.EncryptAES(key, plaintext);
    using MemoryStream memoryStream3 = new MemoryStream();
    using BinaryWriter binaryWriter3 = new BinaryWriter(memoryStream3);
    binaryWriter3.Write(4110704415u);
    binaryWriter3.Write(nonce);
    binaryWriter3.Write(serverNonce);
    Serializers.Bytes.Write(binaryWriter3, data);
    return memoryStream3.ToArray();*/
    return ByteArray();
}

Step3Response Step3ResponseFromBytes(Step3Request& request, Packet& packet)
{
    /*using MemoryStream input = new MemoryStream(response);
    using BinaryReader binaryReader = new BinaryReader(input);
    uint num = binaryReader.ReadUInt32();
    switch (num)
    {
    case 1003222836u:
    {
        byte[] array = binaryReader.ReadBytes(16);
        byte[] array2 = binaryReader.ReadBytes(16);
        byte[] first = binaryReader.ReadBytes(16);
        AuthKey authKey = new AuthKey(_gab);
        byte[] second = authKey.CalcNewNonceHash(newNonce, 1);
        if (!first.SequenceEqual(second))
        {
            throw new InvalidOperationException("invalid new nonce hash");
        }

        return new Step3_Response
        {
            AuthKey = authKey,
            TimeOffset = timeOffset
        };
    }
    case 1188831161u:
        throw new NotImplementedException("dh_gen_retry");
    case 2795351554u:
        throw new NotImplementedException("dh_gen_fail");
    default:
        throw new InvalidOperationException($"dh_gen unknown: {num}");
    }*/
    return Step3Response();
}
