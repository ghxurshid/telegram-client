#include <ctime>
#include <random>
#include <chrono>

#include "Helper.h"

long GetNewMessageId(int timeOffset, long& lastMessageId)
{
	long long num = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();

	long long num2 = (num / 1000 + timeOffset) << 32 | (num % 1000) << 22 | (static_cast<long long>(rand() % 524288)) << 2;
	if (lastMessageId >= num2) {
		num2 = lastMessageId + 4;
	}

	lastMessageId = num2;
	return num2;
}
