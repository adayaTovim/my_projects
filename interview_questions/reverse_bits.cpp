#include <iostream>
#include <bitset>

/*Write a function that reverses the bits in an integer,
so that the most significant bit and the least significant bit are swapped,
second bit and the bit before the MSB are swapped and so on.
1100101 --> 1010011*/

unsigned int reverseBits(unsigned int a_num)
{
    unsigned int size = sizeof(a_num) * 8;

    for (unsigned int i = 0; i < size / 2; ++i) {
        unsigned int rightBit = a_num & (1 << i);
        unsigned int leftBit = a_num & (1 << (size - i - 1));
        if (leftBit != 0 && rightBit == 0 || leftBit == 0 && rightBit != 0) {
			a_num ^= (1 << i);
			a_num ^= 1 << (size - i - 1);
        }
    }

    return a_num;
}

int main()
{
    unsigned int num = 101;
    std::bitset<sizeof(unsigned int) * 8> binary(num);  // convert integer to binary representation
    std::cout << num << " before reverse bits " << binary << std::endl;

    unsigned int result = reverseBits(num);
    std::bitset<sizeof(unsigned int) * 8> binary2(result);
    std::cout << result << " after reverse bits " << binary2 << std::endl;

    return 0;
}

