
#include "Utils.h"
#include "Step1.h"
#include "TelegramClient.h"
#include "MtProtoPlainSender.h"
 
TelegramClient* CreateTelegramClient(uint32_t apiId, char* apiHash)
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

	if (session->authKey == nullptr || reconnect)
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

Step3Response DoAuthentication()
{     
    Step1Request stp1Req = CreateStep1Request(); Packet stp1ReqPacket = Step1RequestToBytes(stp1Req); 
    MtPlain_Send(stp1ReqPacket); Packet stp1ResPacket = MtPlain_Receive();
    Step1Response step1Res = Step1ResponseFromBytes(stp1Req, stp1ResPacket); 

    Step2Request stp2Req = CreateStep2Request(); Packet stp2ReqPacket = Step2RequestToBytes(stp2Req, step1Res);
    MtPlain_Send(stp2ReqPacket); Packet stp2ResPacket = MtPlain_Receive();
    Step2Response step2Res = Step2ResponseFromBytes(stp2Req, stp2ResPacket);

    Step3Request stp3Req = CreateStep3Request(); Packet stp3ReqPacket = Step3RequestToBytes(stp3Req, step2Res);
    MtPlain_Send(stp3ReqPacket); Packet stp3ResPacket = MtPlain_Receive();
    return Step3ResponseFromBytes(stp3Req, stp3ResPacket);    
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
        client->session->User == nullptr) return false;
     
    return true;
}