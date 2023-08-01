/*
Given two strings s and t of lengths m and n respectively, return the minimum window
substring
 of s such that every character in t (including duplicates) is included in the window. If there is no such substring, return the empty string "".

The testcases will be generated such that the answer is unique.

 Example 1:
Input: s = "ADOBECODEBANC", t = "ABC"
Output: "BANC"
Explanation: The minimum window substring "BANC" includes 'A', 'B', and 'C' from string t.

Example 2:
Input: s = "a", t = "a"
Output: "a"
Explanation: The entire string s is the minimum window.

Example 3:
Input: s = "a", t = "aa"
Output: ""
Explanation: Both 'a's from t must be included in the window.
Since the largest window of s only has one 'a', return empty string.
*/

#include <vector>
#include <string>
#include <climits>
#include <iostream>
#include <unordered_map>

// std::string minWindow(std::string s, std::string t)
// {
//         std::vector<int> map(128,0);
//         for(auto c: t) {
//             map[c]++;
//         }
//         int counter = t.size();
//         int begin = 0;
//         int end = 0;
//         int d = INT_MAX;
//         int head = 0;
//         while(end < s.size()){
// 			char currentCharacter = s[end];
// 			map[currentCharacter]--; // Decrease the count of the current character in the map
// 			if (map[currentCharacter] >= 0) {
// 				counter--; // If the count is still greater than or equal to 0, it means the character is in 't', so decrement the counter.
// 			}
// 			end++; // Move the 'end' pointer to the next character

//             while(counter == 0){
//                 if(end-begin < d) {
//                     head = begin;
//                     d = end-head;
//                 }
//                 char currentCharacter = s[begin];
// 				map[currentCharacter]++; // Increase the count of the current character in the map
// 				if (map[currentCharacter] > 0) {
// 					counter++; // If the count becomes greater than 0, it means the character is no longer in 't', so increment the counter.
// 				}
// 				begin++; // Move the 'begin' pointer to the next character
//         	}
// 		}
//         return d == INT_MAX ? "" : s.substr(head, d);
// }

std::string minWindow(std::string s, std::string t) {
    std::unordered_map<char, int> freq;
    for (char c : t) {
        freq[c]++;
    }

    int left = 0;
    int right = 0;
    int counter = t.size();
    int minLen = INT_MAX;
    int minStart = 0;

    while (right < s.size()) {
        char rightChar = s[right];
        if (freq[rightChar] > 0) {
            counter--;
        }
        freq[rightChar]--;
        right++;

        while (counter == 0) {
            if (right - left < minLen) {
                minLen = right - left;
                minStart = left;
            }

            char leftChar = s[left];
            freq[leftChar]++;
            if (freq[leftChar] > 0) {
                counter++;
            }
            left++;
        }
    }

    return minLen == INT_MAX ? "" : s.substr(minStart, minLen);
}

int main()
{
    std::string s1 = "ADOBECODEBANC";
    std::string t1 = "ABC";
    std::cout << "Test case 1: " << minWindow(s1, t1) << std::endl; // Output: "BANC"

    std::string s2 = "a";
    std::string t2 = "a";
    std::cout << "Test case 2: " << minWindow(s2, t2) << std::endl; // Output: "a"

    std::string s3 = "a";
    std::string t3 = "aa";
    std::cout << "Test case 3: " << minWindow(s3, t3) << std::endl; // Output: ""

    return 0;
}

