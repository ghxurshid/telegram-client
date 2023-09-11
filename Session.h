#pragma once
#include <stdint.h>
#include "TLUser.h"
#include "AuthKey.h"
#include "ByteArray.h"


/// <summary>
/// Bu struct sessia haqida informatsiyani saqlaydi
/// </summary>
struct Session
{
    ByteArray SessionUserId;

    AuthKey* authKey;

    uint64_t Id; //8 bayt

    uint32_t Sequence; //4 bayt

    uint64_t Salt; //8 bayt

    uint32_t TimeOffset; //4 bayt

    uint64_t LastMessageId; //8 bayt

    uint32_t SessionExpires; //4 bayt

    TLUser* User;
};

Session CreateSession();
 
void Save(Session& session);
Session Load();
Session TryLoadOrCreateNew();
uint64_t GenerateRandomUlong();
 



