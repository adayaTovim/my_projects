#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> belowTwenty = {
	"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine",
	"Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
};

std::vector<std::string> tens = {
	"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
};

std::string numsToString(size_t a_num)
{
    if (a_num < 20) {
        return belowTwenty[a_num];
    }

    std::string result;

    if (a_num >= 1000000) {
        result += belowTwenty[a_num / 1000000] + " Million ";
		std::cout<<result<<std::endl;
        a_num %= 1000000;
    }

    if (a_num >= 1000) {
        result += numsToString(a_num / 1000) + " Thousand ";
		std::cout<<result<<std::endl;
        a_num %= 1000;
    }

    if (a_num >= 100) {
        result += belowTwenty[a_num / 100] + " Hundred ";
		std::cout<<result<<std::endl;
        a_num %= 100;
    }

    if (a_num >= 20) {
        result += tens[a_num / 10] + " ";
		std::cout<<result<<std::endl;
        a_num %= 10;
    }

    if (a_num > 0) {
        result += belowTwenty[a_num];
    }

    return result;
}

int main()
{
	std::cout << "103: " << numsToString(103) << std::endl;
	std::cout << "1234: " << numsToString(1234) << std::endl;
    //std::cout << "12345: " << numsToString(12345) << std::endl;
    //std::cout << "1234567: " << numsToString(1234567) << std::endl;

    return 0;
}

