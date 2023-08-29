#pragma once
#include "MtProtoSender.h"
#include "TcpTransport.h"
#include "Session.h"

struct TelegramClient
{
    char* apiHash;

    int apiId = 0;

    Session* session;
};

TelegramClient* CreateTelegramClient(int apiId, char* apiHash);
bool Connect(TelegramClient* client, bool reconnect);
void DoAuthentication();
void SendCodeRequest(TelegramClient* client, char phoneNumber[12]);
void MakeAuth(TelegramClient* client, char phoneNumber[12], char* hash, char* code);
void GetContacts(TelegramClient* client);
void ReadFromChat(TelegramClient* client);

