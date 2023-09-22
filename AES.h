#pragma once
#include "ByteArray.h"

struct AES
{
};

struct AESKeyData
{
	ByteArray key;
	ByteArray iv;
};

ByteArray  AES_Encrypt(AESKeyData key, ByteArray plain_text);
ByteArray  AES_Decrypt(AESKeyData key, ByteArray ciphertext);
AESKeyData AES_GenerateKeyDataFromNonces(ByteArray serverNonce, ByteArray newNonce);

