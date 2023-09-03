#pragma once
#include <stdint.h>
#include <stdio.h>

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

    uint32_t Flags;

    bool Self;
    bool Contact;
    bool MutualContact;
    bool Deleted;
    bool Bot;
    bool BotChatHistory;
    bool BotNochats;
    bool Verified;
    bool Restricted;
    bool Min;
    bool BotInlineGeo;

    uint32_t Id;
    uint64_t AccessHash;

    char* FirstName;
    char* LastName;
    char* Username;
    char* Phone;

    TLAbsUserProfilePhoto* Photo;
    TLAbsUserStatus* Status;

    uint32_t BotInfoVersion;
    char* RestrictionReason;
    char* BotInlinePlaceholder;
    char* LangCode;
};

void UserWriteBytes(TLUser* user, FILE* fp);
TLUser* UserReadBytes(FILE* fp);
void ComputeFlags(TLUser* user);

