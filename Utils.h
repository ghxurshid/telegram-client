#pragma once
#include <stdio.h>

char* ReadBytes(FILE* fp);
void  WriteBytes(char* bytes, int count, FILE* fp);

char* ReadBytesFromArray(char* bytes, int offset, int& count);

bool CompareArray(ByteArray arr1, ByteArray arr2);

void ReplaceByteArrayFromSign(ByteArray& arr);


