#pragma once
struct TLContact
{
	uint32_t UserId;
	bool Mutual;
};

struct TLContacts
{
	uint32_t size;
	TLContact* data;
};

TLContacts CreateContacts(uint32_t size);
void ClearContacts(TLContacts& contacts);

