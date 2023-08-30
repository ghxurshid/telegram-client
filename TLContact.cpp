#include "TLContact.h"

TLContacts CreateContacts(int size)
{
	TLContacts contacts{ size, new TLContact[size] };
	return contacts;
}

void ClearContacts(TLContacts& contacts)
{
	delete[] contacts.data;
	contacts.size = 0;
}
