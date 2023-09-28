#include "RSA.h"
#include "SHA1.h"
#include "ByteArray.h"

RSAServerKey CreateRSAServerKey()
{

}

ByteArray Encrypt()

ByteArray RSA_Encrypt(ByteArray key, ByteArray data)
{
    static RSAServerKey serverKey = CreateRSAServerKey();

    /*using (MemoryStream buffer = new MemoryStream(255))
        using (BinaryWriter writer = new BinaryWriter(buffer))*/

    ByteArray buffer = CreateByteArray(255);

     
    ByteArray hashsum = SHA1_ComputeHash(data, offset, length);
    writer.Write(hashsum);
     

    buffer.Write(data, offset, length);
    if (length < 235)
    {
        byte[] padding = new byte[235 - length];
        new Random().NextBytes(padding);
        buffer.Write(padding, 0, padding.Length);
    }

    byte[] ciphertext = new BigInteger(1, buffer.ToArray()).ModPow(e, m).ToByteArrayUnsigned();

    if (ciphertext.Length == 256)
    {
        return ciphertext;
    }
    else {
        byte[] paddedCiphertext = new byte[256];
        int padding = 256 - ciphertext.Length;
        for (int i = 0; i < padding; i++)
        {
            paddedCiphertext[i] = 0;
        }
        ciphertext.CopyTo(paddedCiphertext, padding);
        return paddedCiphertext;
    }
    

    return ByteArray();

}
