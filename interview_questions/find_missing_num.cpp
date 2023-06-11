#include <iostream>
#include <fstream>
#include <bitset>


/*Given a file with 4294967296 ints, write an algorithm to generate a number not in the file.
You can use as much disk space as you want, but you are limited to 1 GB DRAM for your stack.*/

int findMissingNum(const std::string a_filename)
{
	std::ifstream file(a_filename);
	if(!file) {
		std::cerr << "Failed to open file " << a_filename << std::endl;
		return 0;
	}

	std::bitset<4294967296> bitset;

	int num;
    while (file >> num) {
		// set the corresponding bit for each number in the file
        bitset.set(num);
    }

    file.close();

    for (int i = 0; i < bitset.size(); ++i) {
        if (!bitset.test(i)) {
			// find the first unset bit, which represents the missing number
            return i;
        }
    }

    return 0;
}


