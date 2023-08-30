#include "MtProtoPlainSender.h"
#include "TcpTransport.h"
#include "Helper.h"
 
int timeOffset;
long lastMessageId;
  
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
	long id = GetNewMessageId(timeOffset, lastMessageId);
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

	TcpSend(packet);
}

ByteArray MtPlain_Receive()
{
	TcpMessage message = TcpReceive();
	return message.Body;
}
