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

    AuthKey* authKey = nullptr;

    uint64_t Id = 0; //8 bayt

    uint32_t Sequence = 0; //4 bayt

    uint64_t Salt = 0; //8 bayt

    uint32_t TimeOffset = 0; //4 bayt

    uint64_t LastMessageId = 0; //8 bayt

    uint32_t SessionExpires = 0; //4 bayt

    TLUser* User = nullptr;
};

Session CreateSession();
 
void Save(Session& session);
Session Load();
Session TryLoadOrCreateNew();
uint64_t GenerateRandomUlong();
 



