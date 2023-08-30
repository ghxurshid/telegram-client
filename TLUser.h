#pragma once
struct TLUser
{
    int Flags;

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
    int Id;
    long AccessHash;

    char* FirstName;
    char* LastName;
    char* Username;
    char* Phone;

    /*TLAbsUserProfilePhoto Photo;
    TLAbsUserStatus Status;*/

    int BotInfoVersion;
    char* RestrictionReason;
    char* BotInlinePlaceholder;
    char* LangCode;
};

