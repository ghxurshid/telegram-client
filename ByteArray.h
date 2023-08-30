#pragma once
struct ByteArray
{
	unsigned int size;
	unsigned char* data;
};

ByteArray CreateByteArray(unsigned int size);
void DeleteByteArray(ByteArray& obj);

ByteArray Add2ByteArray(ByteArray arr1, ByteArray arr2);

