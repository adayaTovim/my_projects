/*
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent.
Return the answer in any order.
A mapping of digits to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.

Example 1:
Input: digits = "23"
Output: ["ad","ae","af","bd","be","bf","cd","ce","cf"]

Example 2:
Input: digits = ""
Output: []

Example 3:
Input: digits = "2"
Output: ["a","b","c"]

Constraints:
0 <= digits.length <= 4
digits[i] is a digit in the range ['2', '9'].
*/

#include <vector>
#include <string>
#include <unordered_map>
#include <queue>
#include <iostream>

std::unordered_map<int, std::string> digitsMap = {{2, "abc"}, {3, "def"}, {4, "ghi"}, {5, "jkl"}, {6, "mno"}, {7, "pqrs"},{8, "tuv"}, {9, "wxyz"}};

std::vector<std::string> lettersCombinations(std::string a_num)
{
    std::vector<std::string> result;

    if (a_num.empty()) {
        return result;
    }

    result.push_back(""); // start with an empty string in the result vector

    for (char digit : a_num) {
        int num = digit - '0';
        auto it = digitsMap.find(num);
        if (it != digitsMap.end()) {
            const std::string& letters = it->second;
            std::vector<std::string> tempResult;
            for (char letter : letters) {
                for (const std::string& prev : result) {
                    tempResult.push_back(prev + letter);
                }
            }
            result = std::move(tempResult); // move the updated combinations to the result vector
        }
    }
    return result;
}

void printResult(const std::string& a_digit, const std::vector<std::string>& a_vec)
{
	std::cout << "For digits: " << a_digit << "\nall possible letter combinations:\n[ ";
	for(auto s : a_vec) {
		std::cout << "'" << s << "' ";
	}
	std::cout << "]\n" << std::endl;
}

int main()
{
	std::string digit = "23";
	printResult(digit, lettersCombinations(digit));

	std::string digit2 = "";
	printResult(digit2, lettersCombinations(digit2));


	return 0;
}
