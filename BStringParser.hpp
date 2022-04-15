#pragma once

#include <vector>
#include <string>

class BStringParser {
public:
	BStringParser();
	~BStringParser();

	inline std::vector<size_t> FindAllOccurrences(const std::string& data, const std::string& query) {
		std::vector<size_t> occurancesPoss;
		FindAllOccurrences(data, query, occurancesPoss);
		return occurancesPoss;
	}
	void FindAllOccurrences(const std::string& data, const std::string& query, std::vector<size_t>& occurancesPoss);

	std::string RemoveStringLead(std::string& data, const std::string& until, const bool inclusive = false, const bool useCopy = true);
	std::string StringLead(const std::string& data, const std::string& until, const bool inclusive = false);

	std::string RemoveStringTrail(std::string& data, const std::string& until, const bool inclusive = false, const bool useCopy = true);
	std::string StringTrail(std::string data, const std::string& until, const bool inclusive = false);

	inline std::string AttributeValue(const std::string& data, const std::string& attribute, const size_t offset = 0) {
		std::string value("");
		AttributeValue(data, attribute, value, offset);
		return value;
	}
	void AttributeValue(const std::string& data, const std::string& attribute, std::string& dest, const size_t offset = 0);

	inline std::vector<std::string> Split(const std::string& data, const std::string& delimiter) {
		std::vector<std::string> dest;
		Split(data, delimiter, dest);
		return dest;
	}
	void Split(const std::string& data, const std::string& delimiter, std::vector<std::string>& dest); // I have a bad feeling about this :(
};