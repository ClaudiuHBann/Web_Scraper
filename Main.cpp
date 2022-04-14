#include "BTimer.hpp"

#include <iostream>

int main() {
	BTimer bTimer(true, "Test");
	std::cout << bTimer.GetElapsedTimeAsInt("Test");

	return 0;
}