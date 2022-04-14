#include "BStringParser.hpp"

BStringParser::BStringParser() {

}

BStringParser::~BStringParser() {

}

inline std::vector<size_t> BStringParser::FindAllOccurrences(const std::string& data, const std::string& query) {
	std::vector<size_t> occurancesPoss;
	FindAllOccurrences(data, query, occurancesPoss);
	return occurancesPoss;
}

void BStringParser::FindAllOccurrences(const std::string& data, const std::string& query, std::vector<size_t>& occurancesPoss) {
	size_t pos = data.find(query);
	while(pos != std::string::npos) {
		occurancesPoss.push_back(pos);
		pos = data.find(query, pos + query.size());
	}
}

std::string BStringParser::RemoveStringLead(std::string& data, const std::string& until, const bool inclusive/* = false*/, const bool useCopy/* = true*/) {
	if(until.size() <= data.size()) {
		size_t pos = data.find(until);
		if(pos != std::string::npos) {
			if(useCopy) {
				return data.substr(pos + ((inclusive) ? until.size() : 0));
			} else {
				data.erase(0, pos + ((inclusive) ? until.size() : 0));
			}
		}
	}

	return "";
}

std::string BStringParser::StringLead(const std::string& data, const std::string& until, const bool inclusive/* = false*/) {
	if(until.size() <= data.size()) {
		size_t pos = data.find(until);
		if(pos != std::string::npos) {
			return data.substr(0, pos + ((inclusive) ? until.size() : 0));
		}
	}

	return "";
}

std::string BStringParser::RemoveStringTrail(std::string& data, const std::string& until, const bool inclusive/* = false*/, const bool useCopy/* = true*/) {
	if(until.size() <= data.size()) {
		size_t pos = data.rfind(until);
		if(pos != std::string::npos) {
			if(useCopy) {
				return data.substr(0, pos + ((inclusive) ? 0 : until.size()));
			} else {
				data.erase(pos + ((inclusive) ? 0 : until.size()));
			}
		}
	}

	return "";
}

std::string BStringParser::StringTrail(std::string data, const std::string& until, const bool inclusive/* = false*/) {
	if(until.size() <= data.size()) {
		size_t pos = data.rfind(until);
		if(pos != std::string::npos) {
			return data.substr(pos + ((inclusive) ? 0 : until.size()));
		}
	}

	return "";
}

inline std::string BStringParser::AttributeValue(const std::string& data, const std::string& attribute, const size_t offset/* = 0*/) {
	std::string value("");
	AttributeValue(data, attribute, value, offset);
	return value;
}

void BStringParser::AttributeValue(const std::string& data, const std::string& attribute, std::string& dest, const size_t offset/* = 0*/) {
	size_t valueLength = 0, posValueStart = offset + attribute.size() + 2;
	for(size_t i = posValueStart; i < data.size(); i++) {
		if(data[i] == '"') {
			valueLength = i - posValueStart;
			break;
		}
	}

	dest = data.substr(posValueStart, valueLength);
}

inline std::vector<std::string> BStringParser::Split(const std::string& data, const std::string& delimiter) {
	std::vector<std::string> dest;
	Split(data, delimiter, dest);
	return dest;
}

void BStringParser::Split(const std::string& data, const std::string& delimiter, std::vector<std::string>& dest) {
	std::vector<size_t> occurrences;
	FindAllOccurrences(data, delimiter, occurrences);

	if(occurrences.empty()) {
		return;
	}

	size_t last = 0;
	for(size_t current = 0; current < occurrences.size(); current++) {
		std::string pushable(data.substr(last, occurrences[current] - last));
		if(!pushable.empty()) {
			dest.push_back(pushable);
		}

		last = occurrences[current] + delimiter.size();
	}

	std::string pushable(data.substr(last));
	if(!pushable.empty()) {
		dest.push_back(pushable);
	}
}