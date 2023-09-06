#include "Api.h"
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
    {
        Step1Request stp1Reqs = CreateStep1Request();

        ByteArray data = CreateByteArray(52);
        uint32_t constructor = 1615239032;
        int idx = 28;
 
        for (int i = 0; i < 4; i++)
        {
            data.data[idx++] = (constructor >> (i * 8)) & 0xFF;
        }

        for (int i = 0; i < 16; i++)
        {
            data.data[idx++] = Rand8();
        }

        MtPlain_Send(data);
        ClearByteArray(data);
    }
    
    char* nonce;
    char* servernonce;

    int count = 0;
    char* pqBytes;

    uint32_t num3 = 0;
    char** fingerPrint;

    {
        int idx = 28;
        ByteArray recvData = MtPlain_Receive();
        
        uint8_t* data = recvData.data;
        uint32_t num =  (data[idx++] << 0)  |
                        (data[idx++] << 8)  |
                        (data[idx++] << 16) |
                        (data[idx++] << 24) ;

        if (num != 85337187)
        {
            printf("DoAuthentication: incorrect value of 'num' = %i\n", num);
            return;
        }

        nonce = new char[16];
        for (int i = 0; i < 16; i++)
        {
            nonce[i] = data[idx++];
        }

        servernonce = new char[16];
        for (int i = 0; i < 16; i++)
        {
            servernonce[i] = data[idx++];
        }

        count = 0;
        pqBytes = ReadBytesFromArray((char*)data, idx, count);
        idx += count;

        uint32_t num2 = (data[idx++] << 0)  |
                        (data[idx++] << 8)  |
                        (data[idx++] << 16) |
                        (data[idx++] << 24) ;
                
        if (num2 != 481674261)
        {
            printf("DoAuthentication: Invalid vector constructor number %i\n", num2);
            return;
        }

        num3 = (data[idx++] << 0)  |
                        (data[idx++] << 8)  |
                        (data[idx++] << 16) |
                        (data[idx++] << 24) ;

        fingerPrint = new char* [num3];
        for (int i = 0; i < num3; i++)
        {
            fingerPrint[i] = new char[8];
            for (int j = 0; j < 8; j++)
            {
                fingerPrint[i][j] = data[idx++];
            }
        }
    }

    {




        delete[] nonce;
        delete[] servernonce;
        delete[] pqBytes;
        for (int i = 0; i < num3; i++) delete[] fingerPrint[i];
        delete[] fingerPrint;
    }
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