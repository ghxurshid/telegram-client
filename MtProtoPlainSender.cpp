#include <iostream>
#include "MtProtoPlainSender.h"
#include "TcpTransport.h"
#include "Helper.h"
 
uint32_t timeOffset;
uint64_t lastMessageId;
  
void MtPlain_Send(Packet packet)
{
	int size = packet.body.size;
	uint8_t* data = packet.body.data;
	
	if (size < 32)
	{
		printf("MtPlain_Send: data size is less than 32\n");
		return;
	}

	int idx = 8; //index 8 dan boshlanishining sababi oldingi baytlari keyingi funksiyalarda to`ldiriladi, bu mikrokontroller joyni ekanom qilish uchun shunday qilingan

	for (int i = 0; i < 8; i++)
	{
		data[idx ++] = 0;		 
	}

	uint64_t id = GetNewMessageId(timeOffset, lastMessageId);

	for (int i = 0; i < 8; i++)
	{
		data[idx ++] = (id >> (i * 8)) & 0xFF;
	}
	
	for (int i = 0; i < 4; i++)
	{
		data[idx++] = (packet.bodySize >> (i * 8)) & 0xFF;
	}
 
	TcpSend(packet);

	ClearPacket(packet);
}

Packet MtPlain_Receive()
{
	return TcpReceive();
}
