#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

/* Given a vector of ints write an efficient nearest function (v, x, n)
that will receive a vector of ints, a value x, and return the n elements closest to the value x in the array.
nearest ([ 10, 7, 19, 3, 1, 12], 14, 3) → [ 10, 12, 19]*/

std::vector<int> closestElements(const std::vector<int>& a_vec, int x, int n)
{
    if(n > a_vec.size()) {
		n = a_vec.size();
	}

	std::vector<std::pair<int, int>> diffPairs;
	auto it = a_vec.begin();
	for (it; it != a_vec.end(); ++it) {
	    int num = *it;
        int diff = std::abs(num - x);
        diffPairs.push_back(std::make_pair(diff, num));
    }

    std::sort(diffPairs.begin(), diffPairs.end());

    std::vector<int> result;
    for (int i = 0; i < n; ++i) {
        result.push_back(diffPairs[i].second);
    }

    return result;
}

void printVector(const std::vector<int>& a_vector)
{
	auto it = a_vector.begin();
	for(it; it != a_vector.end(); ++it) {
		int num = *it;
        std::cout << num << " ";
	}
	// another way to write this
	// for (int num : a_vector){
	// 	std::cout << num << " ";
    // }
	std::cout << "\n";
}

int main()
{
    std::vector<int> v = {10, 7, 19, 3, 1, 12};
    int x = 14;
    int n = 3;
    std::vector<int> result = closestElements(v, x, n);

	printVector(result);

    return 0;
}

