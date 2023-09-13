#include <ctime>
#include <random>
#include <chrono> 
#include "Helper.h"

uint64_t GetNewMessageId(uint32_t timeOffset, uint64_t& lastMessageId)
{
	return 0x58EDC52187458C75; //TODO
	uint64_t num = std::chrono::duration_cast<std::chrono::milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();

	uint64_t num2 = (num / 1000 + timeOffset) << 32 | (num % 1000) << 22 | (static_cast<uint64_t>(rand() % 524288)) << 2;
	if (lastMessageId >= num2) {
		num2 = lastMessageId + 4;
	}

	lastMessageId = num2;
	return num2;
}
