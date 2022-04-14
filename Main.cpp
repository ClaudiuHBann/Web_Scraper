#include "BTimer.hpp"

#include <iostream>

int main() {
	BTimer bt(true, "Test");

	

	std::cout << std::endl << bt.GetElapsedTimeAsInt("Test") << std::endl;

	return 0;
}

/*
	some static methods?

	webscraper and his callback (async methods and multithreads support)
	callback --> when maxprogress is 0 don't print anything

	examples?

	BUGS:
		the blocking shit problem (after some requests the urldownloadtofile blocks)

	Optimizations? :
		"Read page content from file pointer don't load the entire content in a std string"
*/