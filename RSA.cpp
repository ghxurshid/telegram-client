#include "Api.h"
#include "RSA.h"
#include "SHA1.h"
#include "ByteArray.h"

RSAServerKey CreateRSAServerKey()
{
    RSAServerKey serverkey;
    serverkey.fingerprint;
    serverkey.e.sign 
}
 
ByteArray RSA_Encrypt(ByteArray key, ByteArray data)
{
    static RSAServerKey serverKey = CreateRSAServerKey();
  
    ByteArray buffer = CreateByteArray(255);       
    ByteArray hashsum = SHA1_ComputeHash(data, 0, data.size);

    int idx = 0;
    for (int i = 0; i < hashsum.size; i++)
    {
        buffer.data[idx++] = hashsum.data[i];
    }
        
    for (int i = 0; i < data.size; i++)
    {
        buffer.data[idx++] = data.data[i];
    }

    while (idx < 255)
    {
        buffer.data[idx++] = Rand8();
    }
      
    BigInteger bi = CreateBIFromBytes(1, buffer);
    BigInteger bi_pow = BI_ModPow(bi, serverKey.e, serverKey.m);

    ByteArray ciphertext = BI_ToByteArrayUnsigned(bi_pow);

    if (ciphertext.size == 256)
    {
        return ciphertext;
    }
    else {
        ByteArray paddedCiphertext = CreateByteArray(256);
         
        for (int i = 0; i < 256; i++)
        {
            paddedCiphertext.data[i] = i < ciphertext.size ? ciphertext.data[i] : 0;
        }
        ClearByteArray(ciphertext);
        return paddedCiphertext;
    }   
}
