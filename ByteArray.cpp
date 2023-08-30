#include "ByteArray.h"

ByteArray CreateByteArray(unsigned int size)
{
	ByteArray byteArray{};
	byteArray.size = size;
	byteArray.data = new unsigned char[size];

	return byteArray;
}

void DeleteByteArray(ByteArray& obj)
{
	delete[] obj.data;
	obj.size = 0;
}

ByteArray Add2ByteArray(ByteArray arr1, ByteArray arr2)
{
	unsigned int sum = arr1.size + arr2.size;
	ByteArray newArr = CreateByteArray (sum);

	int offset = 0;

	for (int i = 0; i < arr1.size; i++)
	{
		newArr.data[offset + i] = arr1.data[i];
	}

	offset = arr1.size;

	for (int i = 0; i < arr2.size; i++)
	{
		newArr.data[offset + i] = arr2.data[i];
	}

	DeleteByteArray(arr1);
	DeleteByteArray(arr2);

	return newArr;
}