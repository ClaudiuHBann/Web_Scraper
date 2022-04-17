#pragma once

#include <vector>
#include <string>

/**
 * A basic string parser
 */
class BStringParser {
public:
	BStringParser();
	~BStringParser();

	/**
	 * Finds all the occurrences of "query" and returns the positions relative to the "data" as a vector
	 *
	 * @param[in] the data to be searched
	 * @param[in] the query to be searched for
	 *
	 * @return the positions of the occurrences as a vector
	 */
	inline std::vector<size_t> FindAllOccurrences(const std::string& data, const std::string& query) {
		std::vector<size_t> occurancesPoss;
		FindAllOccurrences(data, query, occurancesPoss);
		return occurancesPoss;
	}

	/**
	 * Finds all the occurrences of "query" and populates the vector with the positions relative to the "data"
	 *
	 * @param[in] the data to be searched
	 * @param[in] the query to be searched for
	 * @param[out] the vector with the positions
	 */
	void FindAllOccurrences(const std::string& data, const std::string& query, std::vector<size_t>& occurancesPoss);

	/**
	 * Removes the lead part of the "data" until "until" and the "until" too if is inclusive,
	 *	after which returns the new string if "useCopy" is true else it changes the "data" itself
	 *
	 * @param[out] the data to be changed or to be copied for the upcoming operations
	 * @param[in] the string until to be removed from "data"
	 * @param[in] remove "until" too or not
	 * @param[in] use copy or the "data" ref for the changes
	 *
	 * @return the new string if "useCopy" is true
	 */
	std::string RemoveStringLead(std::string& data, const std::string& until, const bool inclusive = false, const bool useCopy = true);

	/**
	 * Returns the lead string until "until" and the "until" too if inclusive
	 *
	 * @param[in] the data to be used for the operations
	 * @param[in] the string until to be removed from "data"
	 * @param[in] remove "until" too or not
	 *
	 * @return the string lead
	 */
	std::string StringLead(const std::string& data, const std::string& until, const bool inclusive = false);

	/**
	 * Removes the trail part of the "data" until "until" and the "until" too if is inclusive,
	 *	after which returns the new string if "useCopy" is true else it changes the "data" itself
	 *
	 * @param[out] the data to be changed or to be copied for the upcoming operations
	 * @param[in] the string until to be removed from "data"
	 * @param[in] remove "until" too or not
	 * @param[in] use copy or the "data" ref for the changes
	 *
	 * @return the new string if "useCopy" is true
	 */
	std::string RemoveStringTrail(std::string& data, const std::string& until, const bool inclusive = false, const bool useCopy = true);

	/**
	 * Returns the trail string until "until" and the "until" too if inclusive
	 *
	 * @param[in] the data to be used for the operations
	 * @param[in] the string until to be removed from "data"
	 * @param[in] remove "until" too or not
	 *
	 * @return the string lead
	 */
	std::string StringTrail(const std::string data, const std::string& until, const bool inclusive = false);

	/**
	 * Returns the value of the specified attribute by the "data" and it's "offset"
	 *
	 * @param[in] the data which we are searching
	 * @param[in] the attribute of which we take the value
	 * @param[in] the offset of "data" where "attribute" is located
	 *
	 * @return the value of the attribute
	 */
	inline std::string AttributeValue(const std::string& data, const std::string& attribute, const size_t offset = 0) {
		std::string value("");
		AttributeValue(data, attribute, value, offset);
		return value;
	}

	/**
	 * Populates "dest" with the value of the specified attribute by the "data" and it's "offset"
	 *
	 * @param[in] the data which we are searching
	 * @param[in] the attribute of which we take the value
	 * @param[in] the destination for the value
	 * @param[in] the offset of "data" where "attribute" is located
	 */
	void AttributeValue(const std::string& data, const std::string& attribute, std::string& dest, const size_t offset = 0);

	/**
	 * Splits the "data" by the "delimiter" into a vector of strings
	 *
	 * @param[in] the data to be splitted
	 * @param[in] the delimiter idk :O
	 *
	 * @return a vector with the splitted strings
	 */
	inline std::vector<std::string> Split(const std::string& data, const std::string& delimiter) {
		std::vector<std::string> dest;
		Split(data, delimiter, dest);
		return dest;
	}

	/**
	 * Splits the "data" by the "delimiter" into a vector of strings
	 *
	 * @param[in] the data to be splitted
	 * @param[in] the delimiter idk :O
	 * @param[out] the vector to be populated with the splitted strings
	 */
	void Split(const std::string& data, const std::string& delimiter, std::vector<std::string>& dest); // I have a bad feeling about this :(
};