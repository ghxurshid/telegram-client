#include <iostream>
#include "MtProtoPlainSender.h"
#include "TcpTransport.h"
#include "Helper.h"
 
 
uint32_t timeOffset;
uint64_t lastMessageId;
  
void MtPlain_Send(ByteArray data)
{
	if (data.size < 32)
	{
		printf("MtPlain_Send: data size is less than 32");
		return;
	}

	int idx = 8; //index 8 dan boshlanishining sababi oldingi baytlari keyingi funksiyalarda to`ldiriladi, bu mikrokontroller joyni ekanom qilish uchun shunday qilingan

	for (int i = 0; i < 8; i++)
	{
		data.data[idx ++] = 0;		 
	}
	uint64_t id = GetNewMessageId(timeOffset, lastMessageId);
	for (int i = 0; i < 8; i++)
	{
		data.data[idx ++] = (id >> (i*8)) & 0xFF;
	}
	
	for (int i = 0; i < 4; i++)
	{
		data.data[idx++] = (data.size >> (i * 8)) & 0xFF;
	}
 
	TcpSend(data); 
}

ByteArray MtPlain_Receive()
{
	TcpMessage message = TcpReceive();
	return message.Body;
}
