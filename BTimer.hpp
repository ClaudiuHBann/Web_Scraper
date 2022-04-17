#pragma once

#include <map>
#include <string>

#include <chrono>

/**
 * Implementation of a basic timer
 */
class BTimer {
public:
	BTimer();

	/**
	 * Creates a timer with the id "name" and starts counting if "initTimer" is true
	 *
	 * @param[in] start timer
	 * @param[in] the id of the timer
	 */
	BTimer(const bool initTimer, const std::string& name = "");

	~BTimer();

	/**
	 * Counts the timers that have been created
	 * 
	 * @return the number of timers created
	 */
	inline uint64_t Count() {
		return bTimersCount;
	}

	/**
	 * Creates a timer and starts counting
	 *
	 * @param[in] the id of the timer
	 */
	void Create(const std::string& name = "");

	/**
	 * Removes a timer by his id
	 *
	 * @param[in] the id of the timer
	 */
	inline void Remove(const std::string& name) {
		bTimers.erase(name);
	}

	/**
	 * Resets the timer to 0 and continues counting
	 *
	 * @param[in] the id of the timer
	 */
	void Reset(const std::string& name);

	/**
	 * Gets the elapsed time of a timer as std::chrono::nanoseconds
	 *
	 * @param[in] the id of the timer
	 */
	std::chrono::nanoseconds GetElapsedTime(const std::string& name);

	/**
	 * Gets the elapsed time of a timer as nanoseconds
	 *
	 * @param[in] the id of the timer
	 */
	inline int64_t GetElapsedTimeAsInt(const std::string& name) {
		return GetElapsedTime(name).count();
	}

protected:
	uint64_t bTimersCount = 0;
	std::map<std::string, std::chrono::steady_clock::time_point> bTimers;
};