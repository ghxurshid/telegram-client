#include <stdio.h>
#include "TLUser.h"

void UserWriteBytes(TLUser* user, FILE* fp)
{
	if (user == nullptr)
	{
		printf("UserWriteBytes: user is null!");
		return;
	}

	fwrite((void*)user->Con, sizeof(uint64_t), 1, fp);
}
