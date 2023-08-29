#include "MtProtoPlainSender.h"

long GetNewMessageId()
{
	return 1;
}

void MtPlain_Send(ByteArray data)
{
	unsigned int lenght = 20 + data.size;
	ByteArray packet = CreateByteArray(lenght);
	unsigned char* _data = packet.data;

	int idx = 0;

	for (int i = 0; i < 8; i++)
	{
		_data[idx ++] = 0;		 
	}
	long id = GetNewMessageId();
	for (int i = 0; i < 8; i++)
	{
		_data[idx ++] = (id >> (i*8)) & 0xFF;		 
	}
	
	for (int i = 0; i < 4; i++)
	{
		_data[idx++] = (data.size >> (i * 8)) & 0xFF;
	}

	for (int i = 0; i < data.size; i++)
	{
		_data[idx++] = data.data[i];
	}


}

ByteArray MtPlain_Receive()
{

}
