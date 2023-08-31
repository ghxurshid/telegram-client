#include "ByteArray.h"

ByteArray CreateByteArray(uint16_t size)
{
	ByteArray byteArray{};
	byteArray.size = size;
	byteArray.data = new uint8_t[size];

	return byteArray;
}

void DeleteByteArray(ByteArray& obj)
{
	delete[] obj.data;
	obj.size = 0;
}

ByteArray Add2ByteArray(ByteArray arr1, ByteArray arr2)
{
	uint16_t sum = arr1.size + arr2.size;
	ByteArray newArr = CreateByteArray (sum);

	uint16_t offset = 0;

	for (uint16_t i = 0; i < arr1.size; i++)
	{
		newArr.data[offset + i] = arr1.data[i];
	}

	offset = arr1.size;

	for (uint16_t i = 0; i < arr2.size; i++)
	{
		newArr.data[offset + i] = arr2.data[i];
	}

	DeleteByteArray(arr1);
	DeleteByteArray(arr2);

	return newArr;
}