#pragma once
#include "TLUser.h"
#include "AuthKey.h"
#include "ByteArray.h"

/// <summary>
/// Bu struct sessia haqida informatsiyani saqlaydi
/// </summary>
struct Session
{
    ByteArray SessionUserId;

    AuthKey* AuthKey;

    unsigned long Id; //8 bayt

    int Sequence; //4 bayt

    unsigned long Salt; //8 bayt

    int TimeOffset; //4 bayt

    long LastMessageId; //8 bayt

    int SessionExpires; //4 bayt

    TLUser* TLUser;
};

ByteArray ToBytes(Session* session);
Session* FromBytes(ByteArray buffer);
void Save();
Session* TryLoadOrCreateNew();
unsigned long GenerateRandomUlong();
 



