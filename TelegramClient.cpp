#include "TelegramClient.h"
 
TelegramClient* CreateTelegramClient(int apiId, char* apiHash)
{     
    TelegramClient* client = new TelegramClient();
    
    client->apiId = apiId;
    client->apiHash = apiHash;
    client->session = TryLoadOrCreateNew();

    return client;
}

bool Connect(TelegramClient* client, bool reconnect = false)
{
	Session* session = client->session;	 

	if (session->AuthKey == nullptr || reconnect)
	{
		 DoAuthentication();		 
	}
	 
    /*TLRequestGetConfig* config = new TLRequestGetConfig();
    TLRequestInitConnection request = new TLRequestInitConnection
    {
        ApiId = apiId,
        AppVersion = "1.0.0",
        DeviceModel = "PC",
        LangCode = "en",
        Query = config,
        SystemVersion = "Win 10.0"
    };
    TLRequestInvokeWithLayer invokewithLayer = new TLRequestInvokeWithLayer
    {
        Layer = 66,
        Query = request
    };
    await sender.Send(invokewithLayer, token).ConfigureAwait(continueOnCapturedContext: false);
    await sender.Receive(invokewithLayer, token).ConfigureAwait(continueOnCapturedContext: false);*/
    //dcOptions = ((TLConfig)invokewithLayer.Response).DcOptions.ToList();

    return true;
}

void DoAuthentication()
{

}

char* SendCodeRequest(TelegramClient* client, char phoneNumber[12])
{
    return new char[1];//TODO
}

TLUser* MakeAuth(TelegramClient* client, char phoneNumber[12], char* hash, char* code)
{
    return new TLUser();
}

TLContacts GetContacts(TelegramClient* client)
{
    return CreateContacts(5);
}

void ReadFromChat(TelegramClient* client)
{

}

bool IsUserAuthorized(TelegramClient* client)
{
    if (client == nullptr || 
        client->session == nullptr ||
        client->session->TLUser == nullptr) return false;
     
    return true;
}