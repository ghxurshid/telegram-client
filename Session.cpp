#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Session.h"
#include "Utils.h"

const int   ConnectionPort    = 443;
const char* ConnectionAddress = "149.154.175.100";

Session* CreateSession()
{
    return new Session();
}
 
ByteArray ToBytes(Session* session)
{
    return CreateByteArray(5);
}

Session* FromBytes(ByteArray buffer)
{
    return nullptr;
}

void Save(Session& session)
{
    FILE* fp;
    int ret = fopen_s(&fp, "session.dat", "wb");
    if (fp == nullptr) return;

    fwrite((void*)session.Id, sizeof(uint64_t), 1, fp);
    fwrite((void*)session.Sequence, sizeof(uint32_t), 1, fp);
    fwrite((void*)session.Salt, sizeof(uint64_t), 1, fp);
    fwrite((void*)session.LastMessageId, sizeof(uint64_t), 1, fp);
    fwrite((void*)session.TimeOffset, sizeof(uint32_t), 1, fp);
    /*WriteBytes((char*)ConnectionAddress, sizeof(ConnectionAddress), fp);
    fwrite((void*)ConnectionPort, sizeof(uint32_t), 1, fp);*/

    if (session.User != nullptr)
    {
        fwrite((void*)1, sizeof(uint32_t), 1, fp); 
        fwrite((void*)session.SessionExpires, sizeof(uint32_t), 1, fp); 
        UserWriteBytes(session.User, fp);
    }
    else
    {
        fwrite((void*)0, sizeof(uint8_t), 1, fp);
    }

    WriteBytes((char*)(session.authKey->key), sizeof(session.authKey->key), fp);     
}

Session Load()
{
    FILE* fp;
    int ret = fopen_s(&fp, "session.dat", "rb");
    if (fp == nullptr) return Session();

    rewind(fp);
    uint64_t id = 0;            fread(&id, sizeof(uint64_t), 1, fp);
    uint32_t sequence = 0;      fread(&sequence, sizeof(uint32_t), 1, fp);
    uint64_t salt = 0;          fread(&salt, sizeof(uint64_t), 1, fp);
    int64_t lastMessageId = 0;  fread(&lastMessageId, sizeof(int64_t), 1, fp);
    uint32_t timeOffset = 0;    fread(&timeOffset, sizeof(uint32_t), 1, fp);    
    /*char* address =             ReadBytes(fp);
    uint32_t port = 0;          fread(&port, sizeof(uint32_t), 1, fp);*/
    uint32_t flagBuff;          fread(&flagBuff, sizeof(uint32_t), 1, fp);

    bool flag = (flagBuff == 1 ? true : false);
    uint32_t sessionExpires = 0;
    TLUser* tLUser = nullptr;

    if (flag)
    {
        sessionExpires = fread(&sessionExpires, sizeof(uint32_t), 1, fp);
        tLUser = UserReadBytes(fp);
    }

    char* data = ReadBytes(fp);    

    Session session;      
    session.authKey = CreateAuthKey(data);
    session.Id = id;
    session.Salt = salt;
    session.Sequence = sequence;
    session.LastMessageId = lastMessageId;
    session.TimeOffset = timeOffset;
    session.SessionExpires = sessionExpires;
    session.User = tLUser;
    session.SessionUserId = CreateByteArray(8);        
    session.SessionUserId.data = (uint8_t*)"session";
    
    return session;
}

Session TryLoadOrCreateNew()
{
    Session session = Load();

    if (session.authKey == nullptr)
    {
        session = CreateSession();
        session.Id = GenerateRandomUlong();              
        session.SessionUserId = CreateByteArray(8);
        session.SessionUserId.data = (uint8_t*)"session";
    }

    return session;
}

uint64_t GenerateRandomUlong()
{
    srand(time(0));
    return  rand();    
}