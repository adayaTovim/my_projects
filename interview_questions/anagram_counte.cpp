/*
You are given a string s containing one or more words. Every consecutive pair of words is separated by a single space ' '.

A string t is an anagram of string s if the ith word of t is a permutation of the ith word of s.

For example, "acb dfe" is an anagram of "abc def", but "def cab" and "adc bef" are not.
Return the number of distinct anagrams of s. Since the answer may be very large, return it modulo 109 + 7.



Example 1:

Input: s = "too hot"
Output: 18
Explanation: Some of the anagrams of the given string are "too hot", "oot hot", "oto toh", "too toh", and "too oht".
Example 2:

Input: s = "aa"
Output: 1
Explanation: There is only one anagram possible for the given string.
*/

#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <vector>

const int MOD = 1000000007;

int numDistinctAnagrams(const std::string& s) {
    std::vector<std::string> words;
    std::string currentWord;

    // Split the string into words
    for (char c : s) {
        if (c == ' ') {
            words.push_back(currentWord);
            currentWord.clear();
        } else {
            currentWord += c;
        }
    }
    words.push_back(currentWord); // Add the last word

    std::unordered_set<std::string> anagrams;

    for (const std::string& word : words) {
        std::string key = word;
        std::sort(key.begin(), key.end()); // Sort the characters of the word to create a key
        anagrams.insert(key);
    }

    int result = 1;

    for (int i = 0; i < anagrams.size(); i++) {
        result = (result * words.size()) % MOD;
    }

    return result;
}

int main() {
    std::string s = "abc def abc def";
    int distinctAnagrams = numDistinctAnagrams(s);
    std::cout << "Number of distinct anagrams: " << distinctAnagrams << std::endl;

    return 0;
}
