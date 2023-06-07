#include <iostream>

/* Write a function that given an int will return number of identical bit pairs.
0110011 → has 3 pairs
0001010 → has 2 pair
0111011 → has 3 pair
0001110 → has 4 pair */

int countBitPairs(int a_num)
{
	if(a_num < 0) {
		throw std::invalid_argument("Input cannot be negative");
	}

	bool prevIsOn;
	bool isFirstBit = true;
	int counter = 0;
	// 	int size = sizeof(a_num) * 8; if i want to check all

	for(int i = 0; i < 8; ++i) {
		bool currIsOn = a_num & 1;

		a_num >>= 1;

		if(!isFirstBit && prevIsOn == currIsOn) {
			++counter;
		}

		isFirstBit = false;
		prevIsOn = currIsOn;
	}

	return counter;
}

int main() {
	try {
		std::cout << countBitPairs(1) << std::endl; //6
		std::cout << countBitPairs(2) << std::endl; //5
		std::cout << countBitPairs(3) << std::endl; //6
		std::cout << countBitPairs(-1) << std::endl; //error
	} catch (const std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
