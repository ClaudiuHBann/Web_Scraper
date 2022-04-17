#include "BMiscellaneous.hpp"
#include "BStringParser.hpp"
#include "BWebScraper.hpp"
#include "BTimer.hpp"

#include <iostream>

#include <thread>
#include <future>

size_t gifsTotal = 0, gifsCurrent = 0;
std::vector<std::future<void>> as;
std::vector<std::thread> ts;

BStringParser bsp;

inline std::string RemoveCompressionBullshit(std::string& url) {
	BStringParser bsp;
	return bsp.RemoveStringTrail(url, "/") + bsp.StringTrail(url, ")");
}

void PHThread(const size_t page, char** argv) {
	std::string url("https://www.pornhub.com/gifs?o=mv&t=a&page=" + std::to_string(page));
	std::cout << "URL: " << url << std::endl << std::endl;

	std::string pathExe(argv[0]);
	std::string pathBase(bsp.RemoveStringTrail(pathExe, "\\") + "GIFS");
	std::string pathGifs(pathBase + "\\gifs" + std::to_string(page) + ".html");
	std::cout << "Path: " << pathGifs << std::endl << std::endl;

	BWebScraper::URLToFile(url, pathGifs, true);
	std::cout << std::endl;

	std::string attribute("data-gif-url");
	std::string gifsAsString = BMiscellaneous::FileAsString(pathGifs);
	std::vector<size_t> gifsDataWebms = bsp.FindAllOccurrences(gifsAsString, attribute);
	gifsTotal += gifsDataWebms.size();
	std::vector<std::string> gifsUrls(gifsDataWebms.size());
	for(size_t i = 0; i < gifsUrls.size(); i++) {
		gifsUrls[i] = bsp.AttributeValue(gifsAsString, attribute, gifsDataWebms[i]);
		gifsUrls[i] = RemoveCompressionBullshit(gifsUrls[i]);
		gifsUrls[i] = bsp.RemoveStringTrail(gifsUrls[i], ".") + "webm";
		std::cout << gifsUrls[i] << std::endl;
	}
	gifsAsString.clear();
	std::cout << std::endl;

	for(size_t i = 0; i < gifsUrls.size(); i++) {
		std::string gifPath(pathBase + "\\" + std::to_string(page) + std::to_string(i) + bsp.StringTrail(gifsUrls[i], ".", true));
		if(!BMiscellaneous::FileExists(gifPath)) {
			as.push_back(std::async(std::launch::async, [i, gifsUrls, gifPath] {
				BWebScraper::URLToFile(gifsUrls[i], gifPath, true);
				gifsCurrent++;
			}));
		}
	}
}

int main(int argc, char** argv) {
	BTimer bt(true, "Test");

	for(size_t page = 1; page <= 10; page++) {
		ts.push_back(std::thread([page, argv] { PHThread(page, argv); }));
		ts.back().detach();
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

	solve the warnings and infos

	BUGS:
		the blocking shit problem (after some requests the urldownloadtofile blocks)

	Optimizations? :
		"Read page content from file pointer don't load the entire content in a std string"
*/