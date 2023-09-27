//A binary gap within a positive integer N is any maximal sequence of consecutive zeros that is surrounded by ones at both ends in the binary representation of N.
//For example, number 9 has binary representation 1001 and contains a binary gap of length 2.
//The number 529 has binary representation 1000010001 and contains two binary gaps: one of length 4 and one of length 3.
//The number 20 has binary representation 10100 and contains one binary gap of length 1.
//The number 15 has binary representation 1111 and has no binary gaps.
//The number 32 has binary representation 100000 and has no binary gaps.
#include <algorithm>
#include <iostream>

int solution(int N)
{
    int maxGap = 0;
    int gap = 0;
    bool countingZeros = false;
    while(N > 0) {
        if(N & 1) {
            if(countingZeros) {
                maxGap = std::max(maxGap,gap);
                gap = 0;
            }
            countingZeros = true;
        } else if(countingZeros) {
            ++gap;
        }
        N >>= 1;
    }
    return maxGap;
}


int main()
{
    int num1 = 9;
    std::cout << solution(num1) << std::endl; // 1001
    std::cout << solution(529) << std::endl; // 1000010001
    std::cout << solution(20) << std::endl; // 10100
    std::cout << solution(15) << std::endl; // 1111
    std::cout << solution(32) << std::endl; // 100000

    return 0;
}
