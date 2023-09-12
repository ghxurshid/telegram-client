#pragma once
#include <stdint.h>
#include <stdio.h>
#include "ByteArray.h"

struct TLAbsUserProfilePhoto
{
    int32_t Constructor;
};

struct TLAbsUserStatus
{
    int32_t Constructor;
};

struct TLUser
{
    int32_t Constructor = 773059779;
    uint32_t Flags = 0;

    bool Self = false;
    bool Contact = false;
    bool MutualContact = false;
    bool Deleted = false;
    bool Bot = false;
    bool BotChatHistory = false;
    bool BotNochats = false;
    bool Verified = false;
    bool Restricted = false;
    bool Min = false;
    bool BotInlineGeo = false;

    uint32_t Id = 0;
    uint64_t AccessHash = 0;

    ByteArray FirstName;
    ByteArray LastName;
    ByteArray Username;
    ByteArray Phone;

    TLAbsUserProfilePhoto* Photo = nullptr;
    TLAbsUserStatus* Status = nullptr;

    uint32_t  BotInfoVersion = 0;
    ByteArray RestrictionReason;
    ByteArray BotInlinePlaceholder;
    ByteArray LangCode;
};

void UserWriteBytes(TLUser* user, FILE* fp);
TLUser* UserReadBytes(FILE* fp);
void ComputeFlags(TLUser* user);

