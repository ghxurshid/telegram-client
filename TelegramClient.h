#pragma once
#include "MtProtoSender.h"
#include "TcpTransport.h"
#include "Session.h"
#include "TLContact.h"
#include "Step3.h"

struct TelegramClient
{
    ByteArray apiHash;
    uint32_t apiId = 0;
    Session session;
};

TelegramClient CreateTelegramClient(uint32_t apiId, ByteArray apiHash);
bool Connect(TelegramClient& client, bool reconnect);
Step3Response DoAuthentication();
ByteArray SendCodeRequest(TelegramClient& client, ByteArray phoneNumber);
TLUser* MakeAuth(TelegramClient& client, ByteArray phoneNumber, ByteArray hash, ByteArray code);
TLContacts GetContacts(TelegramClient& client);
void ReadFromChat(TelegramClient& client);
bool IsUserAuthorized(TelegramClient& client);

