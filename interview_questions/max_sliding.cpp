#include <iostream>
#include <vector>
#include <algorithm>

/*You are given an array of integers nums,
there is a sliding window of size k which is moving from the very left of the array to the very right.
You can only see the k numbers in the window. Each time the sliding window moves right by one position.
Return the max sliding window.
Example 1:
Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Example 2:
Input: nums = [1], k = 1
Output: [1]
*/

std::vector<int> maxSlidingWindow(std::vector<int> a_vector, int a_num)
{
	std::vector<int> result;
	int size = a_vector.size();
	if(a_num < 1 || a_num > size || size < 1) {
		std::cout << "Invalid window size or empty input\n";
		return result;
	}
	auto windowStart = a_vector.begin();
    auto windowEnd = a_vector.begin() + a_num;
	int currentMax = 0;

	while (windowEnd <= a_vector.end()) {
		currentMax = *std::max_element(windowStart, windowEnd);
		result.push_back(currentMax);
		++windowStart;
		++windowEnd;
	}

	return result;
}

int main() {
    std::vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
    int k = 3;

    std::vector<int> result = maxSlidingWindow(nums, k);

    std::cout << "Maximum sliding window: ";
    for (int num : result) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}

