#pragma once
#include <stdint.h>

struct ByteArray
{
	uint16_t size = 0;
	uint8_t* data = nullptr;
};

struct ByteArrayList
{
	uint16_t count = 0;
	ByteArray** arr = nullptr;
};

ByteArray CreateByteArray(uint16_t size);
void ClearByteArray(ByteArray& obj);

ByteArrayList CreateByteArrayList(uint16_t count);
void ClearByteArrayList(ByteArrayList& obj);

ByteArray Add2ByteArray(ByteArray arr1, ByteArray arr2);

ByteArray ByteArrarClone(ByteArray arr);

