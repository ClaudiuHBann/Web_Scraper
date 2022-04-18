#pragma once

#include <iterator>
#include <fstream>

#include <string>

#include <sys/stat.h>

/**
 * A class which contains helper methods
 */
class BMiscellaneous {
public:
	BMiscellaneous();
	~BMiscellaneous();

	/**
	 * Checks if the file exists
	 *
	 * @param[in] the file path
	 *
	 * @return true if the file exists else false
	 */
	static inline bool FileExists(const std::string& file) {
		struct stat buffer;
		return (stat(file.c_str(), &buffer) == 0);
	}

	/**
	 * Enters the contents of the file in the string and returns it
	 *
	 * @param[in] the file path
	 *
	 * @return the contents of the file as a string
	 */
	static inline std::string FileAsString(const std::string& file) {
		std::string str("");
		FileAsString(file, str);
		return str;
	}

	/**
	 * Enters the contents of the file in the string ref
	 *
	 * @param[in] the file path
	 * @param[out] the string which will contain the file data
	 */
	static void FileAsString(const std::string& file, std::string& str);

	/**
	 * Calculates the percentage of x from y
	 *
	 * @param[in] part number
	 * @param[in] total number
	 * @param[in] the precision
	 *
	 * @return a pair containing the whole number of the percentage (first) and the percentage decimals (second)
	 */
	static inline std::pair<uint64_t, uint64_t> Percentage(const double x, const double y, const uint8_t decimals = 0) {
		double percentage = x / y * 100.;
		uint64_t precision = (uint64_t)pow(10, decimals);
		return std::pair<uint64_t, uint64_t>((uint64_t)percentage, (uint64_t)(percentage * precision) % precision);
	}
};