#pragma once
struct TLContact
{
	int UserId;
	bool Mutual;
};

struct TLContacts
{
	int size;
	TLContact* data;
};

TLContacts CreateContacts(int size);
void ClearContacts(TLContacts& contacts);

