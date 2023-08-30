#pragma once
#include "ByteArray.h"
#include "TcpMessage.h"
 
void TcpConnect();

void TcpDisconnect();

unsigned long AvailableBytes();

void TcpSend(ByteArray data);

TcpMessage TcpReceive();
 
