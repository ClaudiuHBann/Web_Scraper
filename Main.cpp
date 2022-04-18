#include "BMiscellaneous.hpp"
#include "BStringParser.hpp"
#include "BWebScraper.hpp"
#include "BTimer.hpp"

#include <iostream>
#include <thread>

// Counters for all gifs what need to be downloaded and how many were downloaded
size_t gifsTotal = 0, gifsCurrent = 0;

// Derived class from BWebScraper with wrapper for BWebScraper::URLToFileAsync to check for file existence and increase current gif counter (+ print stage)
class WebScraper: public BWebScraper {
public:
	static void URLToFileAsync(const std::string& url, const std::string& file) {
		if(!BMiscellaneous::FileExists(file)) {
			BWebScraper::URLToFileAsync(url, file, false);
		}

		std::cout << ++gifsCurrent << " of " << gifsTotal << std::endl;
	}
};

// Fucntion for a ph thread
void PHThread(const size_t page, char** argv) {
	// Create file path base for the gifs and the page url
	std::string pathBase(BStringParser::RemoveStringTrail(argv[0], "\\") + "GIFS");
	std::string phPageURL("https://www.pornhub.com/gifs?o=mv&t=a&page=" + std::to_string(page));

	// Take all the attribute values "data-gif-url" from the ph page url
	std::vector<std::string> gifsUrls = WebScraper::URLToAttributeValues(phPageURL, "data-gif-url", false);
	// Increase total gifs counter
	gifsTotal += gifsUrls.size();
	for(size_t i = 0; i < gifsUrls.size(); i++) {
		// Remove compression bullshit from the gif url
		gifsUrls[i] = BStringParser::RemoveStringTrail(BStringParser::RemoveStringTrail(gifsUrls[i], "/") + BStringParser::StringTrail(gifsUrls[i], ")"), ".") + "webm";
		// Create the gif path from path base + page + current gif from page + extension, finally download the file asynchronously
		WebScraper::URLToFileAsync(gifsUrls[i], pathBase + "\\" + std::to_string(page) + std::to_string(i) + BStringParser::StringTrail(gifsUrls[i], ".", true));
	}
}

int main(int argc, char** argv) {
	// Create a timer
	BTimer bt(true, "Test");

	// Create a thread for every ph page and detach it
	for(size_t page = 1; page <= 10; page++) {
		std::thread([page, argv] { PHThread(page, argv); }).detach();
	}

	// Wait until all the gifs were downloaded
	std::this_thread::sleep_for(std::chrono::seconds(3));
	while(gifsTotal != gifsCurrent) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	// Print the elapsed time of "Test" timer as nanoseconds and wait for enter key in console
	std::cout << std::endl << bt.GetElapsedTimeAsInt("Test") << std::endl;
	std::cin.get();

	return 0;
}

/*
	if UNICODE ?

	Optimizations? :
		"Read page content from file pointer don't load the entire content in a std string"
*/