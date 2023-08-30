#pragma once
#include "MtProtoSender.h"
#include "TcpTransport.h"
#include "Session.h"
#include "TLContact.h"

struct TelegramClient
{
    char* apiHash;
    int apiId = 0;
    Session* session;
};

TelegramClient* CreateTelegramClient(int apiId, char* apiHash);
bool Connect(TelegramClient* client, bool reconnect);
void DoAuthentication();
char* SendCodeRequest(TelegramClient* client, char phoneNumber[12]);
TLUser* MakeAuth(TelegramClient* client, char phoneNumber[12], char* hash, char* code);
TLContacts GetContacts(TelegramClient* client);
void ReadFromChat(TelegramClient* client);
bool IsUserAuthorized(TelegramClient* client);

