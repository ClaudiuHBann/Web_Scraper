#include "BMiscellaneous.hpp"
#include "BStringParser.hpp"
#include "BWebScraper.hpp"
#include "BTimer.hpp"

#include <iostream>

#include <thread>
#include <future>

size_t gifsTotal = 0, gifsCurrent = 0;
BStringParser bsp;

inline std::string RemoveCompressionBullshit(std::string& url) {
	BStringParser bsp;
	return bsp.RemoveStringTrail(url, "/") + bsp.StringTrail(url, ")");
}

void PHThread(const size_t page, char** argv) {
	std::string url("https://www.pornhub.com/gifs?o=mv&t=a&page=" + std::to_string(page));
	//std::cout << "URL: " << url << std::endl << std::endl;

	std::string pathExe(argv[0]);
	std::string pathBase(bsp.RemoveStringTrail(pathExe, "\\") + "GIFS");
	//std::cout << "Path base: " << pathBase << std::endl << std::endl;

	auto gifsUrls = BWebScraper::URLToAttributeValues(url, "data-gif-url", false);
	gifsTotal += gifsUrls.size();
	for(size_t i = 0; i < gifsUrls.size(); i++) {
		gifsUrls[i] = RemoveCompressionBullshit(gifsUrls[i]);
		gifsUrls[i] = bsp.RemoveStringTrail(gifsUrls[i], ".") + "webm";
		//std::cout << gifsUrls[i] << std::endl << std::endl;
	}

	for(size_t i = 0; i < gifsUrls.size(); i++) {
		std::string gifPath(pathBase + "\\" + std::to_string(page) + std::to_string(i) + bsp.StringTrail(gifsUrls[i], ".", true));
		auto noDiscard = std::async(std::launch::async, [i, gifsUrls, gifPath] {
			if(!BMiscellaneous::FileExists(gifPath)) {
				BWebScraper::URLToFile(gifsUrls[i], gifPath, false);
			}

			auto percentage = BMiscellaneous::Percentage((double)++gifsCurrent, (double)gifsTotal, 2);
			std::cout << percentage.first << '.' << percentage.second << '%' << std::endl;
		});
	}
}

int main(int argc, char** argv) {
	BTimer bt(true, "Test");

	for(size_t page = 1; page <= 69; page++) {
		std::thread([page, argv] { PHThread(page, argv); }).detach();
	}

	std::this_thread::sleep_for(std::chrono::seconds(3));
	while(gifsTotal != gifsCurrent) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}

	std::cout << std::endl << bt.GetElapsedTimeAsInt("Test") << std::endl;
	std::cin.get();

	return 0;
}

/*
	if UNICODE ?

	BUGS:
		the blocking shit problem (after some requests the urldownloadtofile blocks)

	Optimizations? :
		"Read page content from file pointer don't load the entire content in a std string"
*/