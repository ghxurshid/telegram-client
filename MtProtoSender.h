#pragma once
#include "Session.h" 

static Session* session;

void Send(ByteArray packet);
ByteArray Receive();





