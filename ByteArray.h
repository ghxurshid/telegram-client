#pragma once
#include <stdint.h>

struct ByteArray
{
	uint16_t size;
	uint8_t* data;
};

ByteArray CreateByteArray(uint16_t size);
void ClearByteArray(ByteArray& obj);

ByteArray Add2ByteArray(ByteArray arr1, ByteArray arr2);

