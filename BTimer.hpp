#pragma once

#include <map>
#include <string>

#include <chrono>

class BTimer {
public:
	BTimer();
	BTimer(const bool initTimer, const std::string& name = "");
	~BTimer();

	inline uint64_t Count();

	void Create(const std::string& name = "");
	void Remove(const std::string& name);

	void Reset(const std::string& name);
	
	std::chrono::nanoseconds GetElapsedTime(const std::string& name);
	int64_t GetElapsedTimeAsInt(const std::string& name);

protected:
	uint64_t bTimersCount = 0;
	std::map<std::string, std::chrono::steady_clock::time_point> bTimers;
};