#pragma once
#include "ByteArray.h"
#include "TcpMessage.h"
 
void TcpConnect();

void TcpDisconnect();

uint64_t AvailableBytes();

void TcpSend(ByteArray data);

ByteArray TcpReceive();
 
