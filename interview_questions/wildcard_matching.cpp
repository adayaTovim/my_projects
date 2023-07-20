// Given an input string (s) and a pattern (p), implement wildcard pattern matching with support for '?' and '*' where:

// '?' Matches any single character.
// '*' Matches any sequence of characters (including the empty sequence).
// The matching should cover the entire input string (not partial).



// Example 1:

// Input: s = "aa", p = "a"
// Output: false
// Explanation: "a" does not match the entire string "aa".
// Example 2:

// Input: s = "aa", p = "*"
// Output: true
// Explanation: '*' matches any sequence.
// Example 3:

// Input: s = "cb", p = "?a"
// Output: false
// Explanation: '?' matches 'c', but the second letter is 'a', which does not match 'b'.

#include <iostream>

bool isMatch(std::string a_string, std::string a_pattern)
{
	int i = 0;
	int j = 0;

	for(i; i < a_string.size(); ++i) {
		for(j; j < a_pattern.size(); ++j) {
			if(a_string[i] == '*' || a_pattern[j] == '*') {
				return true;
			}

			else if(a_string[i] == '?' && a_pattern[j] != ' ' || a_string[i] != ' ' && a_pattern[j] == '?'  )  {
				++i;
				continue;
			}
			else if(a_string[i] == a_pattern[j])  {
				++i;
				continue;
			}
			else {
				return false;
			}
		}
	}

	if(i != j) {
		return false;
	}

	return true;
}


int main()
{
	std::string s = "cb?";
	std::string p = "?b*";
	bool result = isMatch(s, p);
	if (!result) {
		std::cout << p << " does not match the entire string " << s << std::endl;
	}
	else {
		std::cout << p << " match the entire string " << s << std::endl;
	}

	return 0;
}
