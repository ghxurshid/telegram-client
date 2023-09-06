#pragma once
#include "Packets.h"
#include "TcpMessage.h"
 
void TcpConnect();

void TcpDisconnect();

uint64_t AvailableBytes();

void TcpSend(Packet data);

Packet TcpReceive();
 
