#include "BMiscellaneous.hpp"
#include "BStringParser.hpp"
#include "BWebScraper.hpp"
#include "BTimer.hpp"

#include <iostream>
#include <thread>

int main(int argc, char** argv) {
	// Create a timer
	BTimer bt(true, "Test");

	

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