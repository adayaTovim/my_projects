#include <iostream>
#include <vector>

/*Write a function that given an int will return number of ON bits.
give a solution using bitwise and another one using Look Up Table (LUT)*/

// with LUT table

void fillLUT(std::vector<int>& a_lut) {
    for (int i = 0; i < 256; ++i) {
        int num = i;
        int count = 0;

        while (num != 0) {
            if (num & 1) {
                ++count;
            }
            num >>= 1;
        }

        a_lut.push_back(count);
    }
}

int countSetBits(int a_num, std::vector<int> const& a_lut) {
	if(a_num < 0) {
		throw std::invalid_argument("Input cannot be negative");
	}
	return a_lut[a_num];
}

int main() {
	std::vector<int> lut;
	fillLUT(lut);

	try {
		std::cout<<countSetBits(1, lut)<<std::endl; //1
		std::cout<<countSetBits(56, lut)<<std::endl; //3
		std::cout<<countSetBits(255, lut)<<std::endl; //8
		std::cout<<countSetBits(-2, lut)<<std::endl; //8
	}

	catch (const std::exception& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}
}
