#include "Core.h"

#pragma region Methods
bool Connect(TelegramClient* client, bool reconnect = false)
{
	if (client->session->AuthKey == nullptr || reconnect)
	{

	}
}

void SendCodeRequest(TelegramClient* client, char phoneNumber[12])
{

}

void MakeAuth(TelegramClient* client, char phoneNumber[12], char* hash, char* code)
{

}
void GetContacts(TelegramClient* client)
{

}
void ReadFromChat(TelegramClient* client)
{

}
#pragma endregion
