//We are given two strings P and Q, each consisting of N lowercase English letters.
//For each position in the strings, we have to choose one letter from either P or Q, in order to construct a new string S,
//such that the number of distinct letters in S is minimal.
//Our task is to find the number of distinct letters in the resulting string S.
//For example, if P = "ca" and Q = "ab", S can be equal to: "ca", "cb", "aa" or "ab". String "aa" has only one distinct letter ('a'), so the answer is 1 (which is minimal among those strings).

// Write a function:

// int solution(string &P, string &Q);

// that, given two strings P and Q, both of length N, returns the minimum number of distinct letters of a string S, that can be constructed from P and Q as described above.

// Examples:

// 1. Given P = "abc", Q = "bcd", your function should return 2. All possible strings S that can be constructed are: "abc", "abd", "acc", "acd", "bbc", "bbd", "bcc", "bcd". The minimum number of distinct letters is 2, which be obtained by constructing the following strings: "acc", "bbc", "bbd", "bcc".

// 2. Given P = "axxz", Q = "yzwy", your function should return 2. String S must consist of at least two distinct letters in this case. We can construct S = "yxxy", where the number of distinct letters is equal to 2, and this is the only optimal solution.

// 3. Given P = "bacad", Q = "abada", your function should return 1. We can choose the letter 'a' in each position, so S can be equal to "aaaaa".

// 4. Given P = "amz", Q = "amz", your function should return 3. The input strings are identical, so the only possible S that can be constructed is "amz", and its number of distinct letters is 3.

// Write an efficient algorithm for the following assumptions:

// N is an integer within the range [1..200,000];
// strings P and Q are both of length N;
// strings P and Q are made only of lowercase letters (a−z);
// strings P and Q contain a total of at most 20 distinct letters.

#include <string>
#include <set>
#include <iostream>

int solution(std::string &P, std::string &Q)
{
    int strSize = P.size();
    std::set<char> distinctLetters;

    for (int i = 0; i < strSize; i++) {
        char charP = P[i];
        char charQ = Q[i];

        if (charP == charQ) {
            distinctLetters.insert(charP);
        } else {
            distinctLetters.insert(charP);
            distinctLetters.insert(charQ);
        }
    }
    int setSize = distinctLetters.size();
    if(setSize < strSize) {
        return 1;
    } else if(setSize == strSize) {
        return strSize;
    } else {
        return setSize - (2* strSize - setSize);
    }
}


int main()
{
    // Test 1
    std::string P1 = "abc";
    std::string Q1 = "bcd";
    int result1 = solution(P1, Q1);
    std::cout << result1 << std::endl; //2

    // Test 2
    std::string P2 = "axxz";
    std::string Q2 = "yzwy";
    int result2 = solution(P2, Q2);
    std::cout << result2 << std::endl; //2

    // Test Case 3
    std::string P3 = "bacad";
    std::string Q3 = "abada";
    int result3 = solution(P3, Q3);
    std::cout << result3 << std::endl; //1

    // Test Case 4
    std::string P4 = "amz";
    std::string Q4 = "amz";
    int result4 = solution(P4, Q4);
    std::cout << result4 << std::endl; //3

    return 0;
}





