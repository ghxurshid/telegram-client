#include <stdio.h>
#include "Utils.h"
#include "TLUser.h"

void UserWriteBytes(TLUser* user, FILE* fp)
{
	if (user == nullptr)
	{
		printf("UserWriteBytes: user is null!\n");
		return;
	}

    if (fp == nullptr)
    {
        printf("UserWriteBytes: fp is null!\n");
        return;
    }

	fwrite((void*)user->Constructor, sizeof(uint32_t), 1, fp);	
	ComputeFlags(user);
    fwrite((void*)user->Flags, sizeof(uint32_t), 1, fp);
    fwrite((void*)user->Id, sizeof(uint32_t), 1, fp);

    if ((user->Flags & (true ? 1u : 0u)) != 0)
    {
        fwrite((void*)user->AccessHash, sizeof(uint64_t), 1, fp);         
    }

    if ((user->Flags & 2u) != 0)
    {
        WriteBytes(user->FirstName, fp);
    }

    if ((user->Flags & 4u) != 0)
    { 
        WriteBytes(user->LastName, fp);
    }

    if ((user->Flags & 8u) != 0)
    {
        WriteBytes(user->Username, fp);
    }

    if ((user->Flags & 0x10u) != 0)
    { 
        WriteBytes(user->Phone, fp);
    }

    if ((user->Flags & 0x20u) != 0)
    {
        fwrite((void*)user->Photo->Constructor, sizeof(uint32_t), 1, fp);
    }

    if ((user->Flags & 0x40u) != 0)
    { 
        fwrite((void*)user->Status->Constructor, sizeof(uint32_t), 1, fp);
    }

    if ((user->Flags & 0x4000u) != 0)
    { 
        fwrite((void*)user->BotInfoVersion, sizeof(uint32_t), 1, fp);
    }

    if ((user->Flags & 0x40000u) != 0)
    {
        WriteBytes(user->RestrictionReason, fp); 
    }

    if ((user->Flags & 0x80000u) != 0)
    { 
        WriteBytes(user->BotInlinePlaceholder, fp);
    }

    if ((user->Flags & 0x400000u) != 0)
    { 
        WriteBytes(user->LangCode, fp);
    }
}

TLUser* UserReadBytes(FILE* fp)
{
    if (fp == nullptr)
    {
        printf("UserReadBytes: fp is null!\n");
        return nullptr;
    }

    TLUser* user = new TLUser();

    fread(&(user->Flags), sizeof(uint32_t), 1, fp);
    user->Self = (user->Flags & 0x400) != 0;
    user->Contact = (user->Flags & 0x800) != 0;
    user->MutualContact = (user->Flags & 0x1000) != 0;
    user->Deleted = (user->Flags & 0x2000) != 0;
    user->Bot = (user->Flags & 0x4000) != 0;
    user->BotChatHistory = (user->Flags & 0x8000) != 0;
    user->BotNochats = (user->Flags & 0x10000) != 0;
    user->Verified = (user->Flags & 0x20000) != 0;
    user->Restricted = (user->Flags & 0x40000) != 0;
    user->Min = (user->Flags & 0x100000) != 0;
    user->BotInlineGeo = (user->Flags & 0x200000) != 0;
     
    fread(&(user->Id), sizeof(uint32_t), 1, fp);
    if ((user->Flags & (true ? 1u : 0u)) != 0)
    { 
        fread(&(user->AccessHash), sizeof(uint64_t), 1, fp);
    }
    else
    {
        user->AccessHash = 0;
    }

    if ((user->Flags & 2u) != 0)
    {
        user->FirstName = ReadBytes(fp);// StringUtil.Deserialize(br);
    }
     
    if ((user->Flags & 4u) != 0)
    {
        user->LastName = ReadBytes(fp);
    }
      
    if ((user->Flags & 8u) != 0)
    {
        user->Username = ReadBytes(fp);
    }
      
    if ((user->Flags & 0x10u) != 0)
    {
        user->Phone = ReadBytes(fp);
    }    

    if ((user->Flags & 0x20u) != 0)
    {
        user->Photo = new TLAbsUserProfilePhoto();
        fread(&(user->Photo->Constructor), sizeof(uint32_t), 1, fp);         
    }     

    if ((user->Flags & 0x40u) != 0)
    {  
        user->Status = new TLAbsUserStatus();
        fread(&(user->Status->Constructor), sizeof(uint32_t), 1, fp);
    }
    else
    {
        user->Status = nullptr;
    }

    if ((user->Flags & 0x4000u) != 0)
    {  
        fread(&(user->BotInfoVersion), sizeof(uint32_t), 1, fp);
    }
    else
    {
        user->BotInfoVersion = 0;
    }

    if ((user->Flags & 0x40000u) != 0)
    {
        user->RestrictionReason = ReadBytes(fp);
    }    

    if ((user->Flags & 0x80000u) != 0)
    {
        user->BotInlinePlaceholder = ReadBytes(fp);
    }     

    if ((user->Flags & 0x400000u) != 0)
    {
        user->LangCode = ReadBytes(fp);
    } 
}

void ComputeFlags(TLUser* user)
{
    user->Flags = 0;
    user->Flags = (user->Self ? (user->Flags | 0x400) : (user->Flags & -1025));
    user->Flags = (user->Contact ? (user->Flags | 0x800) : (user->Flags & -2049));
    user->Flags = (user->MutualContact ? (user->Flags | 0x1000) : (user->Flags & -4097));
    user->Flags = (user->Deleted ? (user->Flags | 0x2000) : (user->Flags & -8193));
    user->Flags = (user->Bot ? (user->Flags | 0x4000) : (user->Flags & -16385));
    user->Flags = (user->BotChatHistory ? (user->Flags | 0x8000) : (user->Flags & -32769));
    user->Flags = (user->BotNochats ? (user->Flags | 0x10000) : (user->Flags & -65537));
    user->Flags = (user->Verified ? (user->Flags | 0x20000) : (user->Flags & -131073));
    user->Flags = (user->Restricted ? (user->Flags | 0x40000) : (user->Flags & -262145));
    user->Flags = (user->Min ? (user->Flags | 0x100000) : (user->Flags & -1048577));
    user->Flags = (user->BotInlineGeo ? (user->Flags | 0x200000) : (user->Flags & -2097153));
    user->Flags = (user->AccessHash > 0 ? (user->Flags | 1) : (user->Flags & -2));
    user->Flags = ((user->FirstName.size > 0) ? (user->Flags | 2) : (user->Flags & -3));
    user->Flags = ((user->LastName.size > 0) ? (user->Flags | 4) : (user->Flags & -5));
    user->Flags = ((user->Username.size > 0) ? (user->Flags | 8) : (user->Flags & -9));
    user->Flags = ((user->Phone.size > 0) ? (user->Flags | 0x10) : (user->Flags & -17));
    user->Flags = ((user->Photo != nullptr) ? (user->Flags | 0x20) : (user->Flags & -33));
    user->Flags = ((user->Status != nullptr) ? (user->Flags | 0x40) : (user->Flags & -65));
    user->Flags = (user->BotInfoVersion > 0 ? (user->Flags | 0x4000) : (user->Flags & -16385));
    user->Flags = ((user->RestrictionReason.size > 0) ? (user->Flags | 0x40000) : (user->Flags & -262145));
    user->Flags = ((user->BotInlinePlaceholder.size > 0) ? (user->Flags | 0x80000) : (user->Flags & -524289));
    user->Flags = ((user->LangCode.size > 0) ? (user->Flags | 0x400000) : (user->Flags & -4194305));
}
