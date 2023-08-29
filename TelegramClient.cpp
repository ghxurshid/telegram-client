#include "TelegramClient.h"
#include "Step3_Response.h"
#include "Authenticator.h"
#include "TLRequestGetConfig.h"

TelegramClient* CreateTelegramClient(int apiId, char* apiHash)
{     
    TelegramClient* client = new TelegramClient();
    
    client->apiId = apiId;
    client->apiHash = apiHash;
    client->session = TryLoadOrCreateNew(); 
}

bool Connect(TelegramClient* client, bool reconnect = false)
{
	Session* session = client->session;	 

	if (session->AuthKey == nullptr || reconnect)
	{
		Step3_Response result = DoAuthentication();
		session->AuthKey = result.AuthKey;
		session->TimeOffset = result.TimeOffset;
	}

	 
    TLRequestGetConfig* config = new TLRequestGetConfig();
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
    await sender.Receive(invokewithLayer, token).ConfigureAwait(continueOnCapturedContext: false);
    dcOptions = ((TLConfig)invokewithLayer.Response).DcOptions.ToList();
	
}

void DoAuthentication()
{

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
