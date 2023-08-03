/*
You are given n balloons, indexed from 0 to n - 1.
Each balloon is painted with a number on it represented by an array nums.
You are asked to burst all the balloons.
If you burst the ith balloon, you will get nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array,
then treat it as if there is a balloon with a 1 painted on it.
Return the maximum coins you can collect by bursting the balloons wisely.

Example 1:
Input: nums = [3,1,5,8]
Output: 167
Explanation:
nums = [3,1,5,8] --> [3,5,8] --> [3,8] --> [8] --> []
coins =  3*1*5    +   3*5*8   +  1*3*8  + 1*8*1 = 167

Example 2:
Input: nums = [1,5]
Output: 10
*/

#include <vector>
#include <iostream>
#include <algorithm>

int maxCoins(std::vector<int> a_nums)
{
	std::vector<int> tempVector;

	int size = a_nums.size();
	if(size < 1) {
		return 0;
	}

	while(a_nums.size() > 2) {
		auto it = a_nums.begin() + 1;
		auto end = a_nums.end() - 1;
		auto minNumIt = it;
		for(it; it != end; ++it) {
			if (*it < *minNumIt) {
                minNumIt = it;
            }
		}
		int currentCoins = *(minNumIt-1) * *minNumIt * *(minNumIt+1);
		tempVector.push_back(currentCoins);
		a_nums.erase(minNumIt);
	}

	// now i have 2 num in nums
	int minNum = std::min(a_nums[0], a_nums[1]);
	int lastNum = std::max(a_nums[0], a_nums[1]);
	int currentCoins = a_nums[0] * a_nums[1];
	tempVector.push_back(currentCoins);


	tempVector.push_back(lastNum);

	//sum all
	int sum = 0;
 	for (int coin : tempVector) {
        sum += coin;
    }

    return sum;
}

int main()
{
	std::vector<int> nums1 = {3, 1, 5, 8};
	std::cout<<maxCoins(nums1)<<std::endl;  // Output: 167

	std::vector<int> nums2 = {1, 5};
	std::cout<<maxCoins(nums2)<<std::endl;  // Output: 10

	return 0;
}
