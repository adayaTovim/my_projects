// You are given a string text. You should split it to k substrings (subtext1, subtext2, ..., subtextk) such that:

// subtexti is a non-empty string.
// The concatenation of all the substrings is equal to text (i.e., subtext1 + subtext2 + ... + subtextk == text).
// subtexti == subtextk - i + 1 for all valid values of i (i.e., 1 <= i <= k).
// Return the largest possible value of k.

// Example 1:
// Input: text = "ghiabcdefhelloadamhelloabcdefghi"
// Output: 7
// Explanation: We can split the string on "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)".

// Example 2:
// Input: text = "merchant"
// Output: 1
// Explanation: We can split the string on "(merchant)".

// Example 3:
// Input: text = "antaprezatepzapreanta"
// Output: 11
// Explanation: We can split the string on "(a)(nt)(a)(pre)(za)(tep)(za)(pre)(a)(nt)(a)".

#include <string>
#include <iostream>

int longestDecomposition(std::string text) {
    int size = text.size();
    int result = 0;
    std::string left = "";
    std::string right = "";

    for (int i = 0; i < size; ++i) {
        left += text[i];
        right = text[size - 1 - i] + right;

        if (left == right) {
            ++result;
            left = "";
            right = "";
        }
    }

    return result;
}

int main()
{
    std::string str1 = "ghiabcdefhelloadamhelloabcdefghi";
    std::cout<<longestDecomposition(str1)<<"\n";

    std::string str2 = "merchant";
    std::cout<<longestDecomposition(str2)<<"\n";

    std::string str3 = "antaprezatepzapreanta";
    std::cout<<longestDecomposition(str3)<<"\n";


    return 0;
}
