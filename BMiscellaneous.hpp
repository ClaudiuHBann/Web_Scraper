#pragma once

#include <iterator>
#include <fstream>

#include <string>

#include <sys/stat.h>

class Miscellaneous {
public:
	Miscellaneous();
	~Miscellaneous();

	inline bool FileExists(const std::string& file);
	inline std::string FileAsString(const std::string& file);
	inline void FileAsString(const std::string& file, std::string &str);
};