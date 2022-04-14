#include "BTimer.hpp"

BTimer::BTimer() {

}

BTimer::BTimer(const bool initTimer, const std::string& name/* = ""*/) {
	if(!initTimer) {
		return;
	}

	Create(name);
}

BTimer::~BTimer() {

}

inline uint64_t BTimer::Count() {
	return bTimersCount;
}

void BTimer::Create(const std::string& name/* = ""*/) {
	auto begin = std::chrono::steady_clock::now();
	if(name.empty()) {
		bTimers[std::to_string(++bTimersCount)] = begin;
	} else {
		bTimers[name] = begin;
		bTimersCount++;
	}
}

void BTimer::Reset(const std::string& name) {
	if(bTimers.find(name) != bTimers.end()) {
		bTimers[name] = std::chrono::steady_clock::now();
	}
}

std::chrono::nanoseconds BTimer::GetElapsedTime(const std::string& name) {
	std::chrono::nanoseconds tp {};

	if(bTimers.find(name) != bTimers.end()) {
		tp = std::chrono::steady_clock::now() - bTimers[name];
	}

	return tp;
}

int64_t BTimer::GetElapsedTimeAsInt(const std::string& name) {
	return GetElapsedTime(name).count();
}

void BTimer::Remove(const std::string& name) {
	bTimers.erase(name);
}