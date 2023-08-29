#pragma once
#include "ByteArray.h"
#include "TcpMessage.h"
 
void Connect();

void Disconnect();

unsigned long AvailableBytes();

void TcpSend(ByteArray data);

TcpMessage TcpReceive();
 
