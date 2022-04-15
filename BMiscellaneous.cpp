#include "BMiscellaneous.hpp"

BMiscellaneous::BMiscellaneous() {

}

BMiscellaneous::~BMiscellaneous() {

}

void BMiscellaneous::FileAsString(const std::string& file, std::string& str) {
	if(!FileExists(file)) {
		return;
	}

	std::ifstream ifs(file);
	str.assign((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());
}