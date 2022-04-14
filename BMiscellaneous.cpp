#include "BMiscellaneous.hpp"

Miscellaneous::Miscellaneous() {

}

Miscellaneous::~Miscellaneous() {

}

inline bool Miscellaneous::FileExists(const std::string& file) {
	struct stat buffer;
	return (stat(file.c_str(), &buffer) == 0);
}

inline std::string Miscellaneous::FileAsString(const std::string& file) {
	std::string str("");
	FileAsString(file, str);
	return str;
}

inline void Miscellaneous::FileAsString(const std::string& file, std::string& str) {
	if(!FileExists(file)) {
		return;
	}

	std::ifstream ifs(file);
	str.assign((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
}