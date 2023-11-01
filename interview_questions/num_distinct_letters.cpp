#include <iostream>
#include <string>
#include <unordered_set>
#include <set>

void findAllNumLettersOfAllPossibleCombinations(const std::string& P, const std::string& Q, std::set<size_t>& minUniqueLettersSet) {
    int size = P.size();
    int possibilities = 1 << size; //The number of possible combinations
	std::unordered_set<char> uniqueLetterInString;

    for (int i = 0; i < possibilities; ++i) {
        std::string S = Q;
        for (int j = 0; j < size; ++j) {
            if (i & (1 << j)) { // this line check if the character is in the same index if it's not its true value
                S[j] = P[j];
            }
        }

		uniqueLetterInString.clear(); // / clear the set before using it again

		//find the unique letter in the string
		for(auto c : S) {
        	uniqueLetterInString.insert(c);
    	}

		// insert the num of unique letters to the set
		minUniqueLettersSet.insert(uniqueLetterInString.size());
    }
}

int minCount(std::string& P, std::string& Q)
{
	std::set<size_t> minUniqueLettersSet;
	findAllNumLettersOfAllPossibleCombinations(P, Q, minUniqueLettersSet);

	//std::set keeps elements sorted in ascending order
    return *minUniqueLettersSet.begin();
}

int main() {
    std::string P = "dcba";
    std::string Q = "cbad";

    std::cout<<minCount(P,Q)<<"\n";
    return 0;
}
