# A simple and basic Web Scraper done in C++ with Win32 APIs.

## Example I
**Example on how to download all the gifs from the first 69 [PH](https://www.pornhub.com/gifs?o=mv&t=a&page=1) pages (*On a test I downloaded 2100+ gifs in 1.9 minutes (webms of 5.8GB)*):**
```c++
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

// Function for a ph thread
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
	BTimer bt(true, "GIFS");
	
	// Create a thread for every ph page and detach it
	for(size_t page = 1; page <= 69; page++) {
		std::thread([page, argv] { PHThread(page, argv); }).detach();
	}
	
	// Wait until all the gifs were downloaded
	std::this_thread::sleep_for(std::chrono::seconds(3));
	while(gifsTotal != gifsCurrent) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	
	// Print the elapsed time of "GIFS" timer as nanoseconds and wait for enter key in console
	std::cout << std::endl << bt.GetElapsedTimeAsInt("GIFS") << std::endl;
	std::cin.get();
	
	return 0;
}
```

## Example II
**Example on how to download all the photos from all the albums for the first 10 pages from [PH](https://www.pornhub.com/albums/female-misc-straight?o=mv&verified=1&t=a&page=1) pages (*On a test I downloaded 13.000+ photos in 9.5 minutes (jpgs of 161MB)*):**
```c++
#include "BMiscellaneous.hpp"
#include "BStringParser.hpp"
#include "BWebScraper.hpp"
#include "BTimer.hpp"

#include <iostream>
#include <thread>

// Counters for all photos what need to be downloaded and how many were downloaded
size_t photosTotal = 0, photosCurrent = 0;

// Derived class from BWebScraper with wrapper for BWebScraper::URLToFileAsync to check for file existence and increase current photo counter (+ print stage)
class WebScraper: public BWebScraper {
public:
	static void URLToFileAsync(const std::string& url, const std::string& file) {
		if(!BMiscellaneous::FileExists(file)) {
			BWebScraper::URLToFileAsync(url, file, false);
		}
		
		std::cout << ++photosCurrent << " of " << photosTotal << std::endl;
	}
};

// Function for a ph thread
void PHThread(const std::string album, char** argv) {
	// Create file path base for the photos and the album url
	std::string pathBase(BStringParser::RemoveStringTrail(argv[0], "\\") + "Photos");
	std::string phAlbumURL("https://www.pornhub.com" + album);
	
	// Take all the attribute values "data-bkg" from the ph album url
	std::vector<std::string> gifsUrls = WebScraper::URLToAttributeValues(phAlbumURL, "data-bkg", false);
	// Increase total photos counter - 1 (because there is a comment called "data-bkg") and start from 1 too :(
	photosTotal += gifsUrls.size() - 1;
	for(size_t i = 1; i < gifsUrls.size(); i++) {
		// Create the photo path from path base + album number + current photo from page + extension, finally download the file asynchronously
		WebScraper::URLToFileAsync(gifsUrls[i], pathBase + "\\" + BStringParser::StringTrail(album, "/") + std::to_string(i) + BStringParser::StringTrail(gifsUrls[i], ".", true));
	}
}

int main(int argc, char** argv) {
	// Create a timer
	BTimer bt(true, "Photos");
	
	// Create a thread for every album for every page and detach it
	for(size_t page = 1; page <= 10; page++) {
		// Take all the "href" values from the page
		auto t = BWebScraper::URLToAttributeValues("https://www.pornhub.com/albums/female-misc-straight?o=mv&verified=1&t=a&page=" + std::to_string(page), "href", false);
		for(auto item : t) {
			// Filter the albums from the page
			if(BStringParser::Contains(item, "/album/")) {
				// The thread :O
				std::thread([item, argv] { PHThread(item, argv); }).detach();
			}
		}
	}
	
	// Wait until all the photos were downloaded
	std::this_thread::sleep_for(std::chrono::seconds(3));
	while(photosTotal != photosCurrent) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	
	// Print the elapsed time of "Photos" timer as nanoseconds and wait for enter key in console
	std::cout << std::endl << bt.GetElapsedTimeAsInt("Photos") << std::endl;
	std::cin.get();
	
	return 0;
}
```
