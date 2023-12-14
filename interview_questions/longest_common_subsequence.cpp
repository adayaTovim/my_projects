// Given two strings text1 and text2, return the length of their longest common subsequence.
// If there is no common subsequence, return 0.

// A subsequence of a string is a new string generated from the original string with some characters
// (can be none) deleted without changing the relative order of the remaining characters.

// For example, "ace" is a subsequence of "abcde".
// A common subsequence of two strings is a subsequence that is common to both strings.

// Example 1:
// Input: text1 = "abcde", text2 = "ace"
// Output: 3
// Explanation: The longest common subsequence is "ace" and its length is 3.

// Example 2:
// Input: text1 = "abc", text2 = "abc"
// Output: 3
// Explanation: The longest common subsequence is "abc" and its length is 3.

// Example 3:
// Input: text1 = "abc", text2 = "def"
// Output: 0
// Explanation: There is no such common subsequence, so the result is 0.

// Constraints:
// 1 <= text1.length, text2.length <= 1000
// text1 and text2 consist of only lowercase English characters.

#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>

int longestCommonSubsequence(std::string text1, std::string text2)
{
    std::unordered_map<char, std::queue<size_t>> foundedChar;
    for (auto curChar : text2) {
		while(text1.find(curChar) != std::string::npos) {
        	size_t found = text1.find(curChar);
            foundedChar[curChar].push(found);
			text1[found] = '0';
        }
    }

    bool startCounting = false;
    int counting = 0;
    int maxCounting = 0;
    size_t prevIndex = 0;

    for (auto c : foundedChar) {
        std::queue<size_t> curChar = c.second;
        size_t curIndex = curChar.front();
        if (!startCounting) {
            startCounting = true;
            if(!curChar.empty()) {
                prevIndex = curIndex;
                curChar.pop();
                ++counting;
            }
        } else if (curIndex < prevIndex) {
            ++counting;
            prevIndex = curIndex;
            curChar.pop();
        } else {
            maxCounting = std::max(maxCounting, counting);
            counting = 0;
            prevIndex = 0;
        }
    }

    maxCounting = std::max(maxCounting, counting);

    return maxCounting;
}

int main()
{
    std::string text1 = "abcde";
    std::string text2 = "ace";

    int result1 = longestCommonSubsequence(text1, text2); // Expected 3
    std::cout << "Example 1 - Length of longest common subsequence: " << result1 << std::endl;

    text1 = "abc";
    text2 = "abc";
    int result2 = longestCommonSubsequence(text1, text2); // Expected 3
    std::cout << "Example 2 - Length of longest common subsequence: " << result2 << std::endl;

    text1 = "abc";
    text2 = "def";
    int result3 = longestCommonSubsequence(text1, text2); // Expected 0
    std::cout << "Example 3 - Length of longest common subsequence: " << result3 << std::endl;

    text1 = "abcba";
    text2 = "abcbcba";
    int result4 = longestCommonSubsequence(text1, text2); // Expected 5
    std::cout << "Example 3 - Length of longest common subsequence: " << result4 << std::endl;

    return 0;
}
