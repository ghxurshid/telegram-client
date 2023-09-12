#pragma once
#include <stdio.h>
#include "ByteArray.h"

ByteArray ReadBytes(FILE* fp);

void  WriteBytes(ByteArray data, FILE* fp);

char* ReadBytesFromArray(char* bytes, int offset, int& count);

bool CompareArray(ByteArray arr1, ByteArray arr2);

void ReplaceByteArrayFromSign(ByteArray& arr);


