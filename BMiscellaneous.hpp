#pragma once

#include <iterator>
#include <fstream>

#include <string>

#include <sys/stat.h>

class BMiscellaneous {
public:
	BMiscellaneous();
	~BMiscellaneous();

	inline bool FileExists(const std::string& file) {
		struct stat buffer;
		return (stat(file.c_str(), &buffer) == 0);
	}
	inline std::string FileAsString(const std::string& file) {
		std::string str("");
		FileAsString(file, str);
		return str;
	}
	void FileAsString(const std::string& file, std::string& str);
};