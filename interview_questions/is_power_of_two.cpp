#include <iostream>

bool isPowerOfTwo(int a_num)
{
	if(a_num <= 0) {
		return false;
	}

	return ((a_num & (a_num - 1)) == 0);
}

int main()
{
	int num = 16;
	if (isPowerOfTwo(num)) {
		std::cout << num << " is a power of two." << std::endl;
	} else {
		std::cout << num << " is not a power of two." << std::endl;
	}

	return 0;
}
