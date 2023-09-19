#include "ByteArray.h"

ByteArray CreateByteArray(uint16_t size)
{
	ByteArray byteArray{};
	byteArray.size = size;
	byteArray.data = new uint8_t[size];

	return byteArray;
}

void ClearByteArray(ByteArray& obj)
{
	obj.size = 0;
	if (obj.data != nullptr) delete[] obj.data;	
}

ByteArrayList CreateByteArrayList(uint16_t count)
{
	ByteArrayList list;
	list.count = count;
	list.arr = new ByteArray*[count];
	return list;
}

void ClearByteArrayList(ByteArrayList& obj)
{
	for (int i = 0; i < obj.count; i++) ClearByteArray((*obj.arr[i]));
	
	obj.count = 0;
	delete[] obj.arr;
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

	ClearByteArray(arr1);
	ClearByteArray(arr2);

	return newArr;
}

ByteArray ByteArrarClone(ByteArray arr)
{
	ByteArray clone = CreateByteArray(arr.size);
	if (clone.size > 0)
	{
		for (int i = 0; i < clone.size; i++)
		{
			clone.data[i] = arr.data[i];
		}
	}
	return clone;
}
