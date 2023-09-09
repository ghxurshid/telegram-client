#pragma once
#include <stdint.h>

struct ByteArray
{
	uint16_t size;
	uint8_t* data;
};

struct ByteArrayList
{
	uint16_t count;
	ByteArray* arr;
};

ByteArray CreateByteArray(uint16_t size);
void ClearByteArray(ByteArray& obj);

ByteArrayList CreateByteArrayList(uint16_t count);
void ClearByteArrayList(ByteArrayList& obj);

ByteArray Add2ByteArray(ByteArray arr1, ByteArray arr2);

