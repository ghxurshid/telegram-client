#pragma once
struct TLContact
{
	uint32_t UserId = 0;
	bool Mutual = false;
};

struct TLContacts
{
	uint32_t size = 0;
	TLContact* data = nullptr;
};

TLContacts CreateContacts(uint32_t size);
void ClearContacts(TLContacts& contacts);

