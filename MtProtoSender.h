#pragma once
#include "Session.h" 

static Session* session;

void Mt_Send(ByteArray packet);
ByteArray Mt_Receive();





