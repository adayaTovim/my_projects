#include <iostream>
#include <bitset>

/*Write a function that swap bit 0 and 1, bit 2 and 3, bit 4 and 5 and so on.*/

unsigned int swapBits(unsigned int a_num) {
	unsigned int size = sizeof(a_num) * 8;

	for(unsigned int i = 0; i < size; i += 2) {
		unsigned int first = a_num & (1 << i);
		unsigned int second = a_num & (1 << (i + 1));

		if(first != second) {
			a_num ^= (1 << i);
			a_num ^= (1 << (i + 1));
		}
	}
	return a_num;
}

int main()
{
	unsigned int num = 101;
	std::bitset<sizeof(unsigned int) * 8> binary(num);  // convert integer to binary representation
    std::cout << num << " before swapBits " << binary << std::endl;

	unsigned int result = swapBits(num);
	std::bitset<sizeof(unsigned int) * 8> binary1(result);  // convert integer to binary representation
    std::cout << result << " after swapBits " << binary1<< std::endl;

	return 0;
}
