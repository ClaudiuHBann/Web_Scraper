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
};