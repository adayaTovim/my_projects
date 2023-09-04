#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

// checks whether there are two elements in a given vector that sum up to a specified target number

//1. naive implementation - time complexity o(n^2) , space complexity o(1)
// bool findPairWithSum(std::vector<int> a_vec, int a_num) {
//     int size = a_vec.size();

//     for (int i = 0; i < size - 1; ++i) {
//         for (int j = i + 1; j < size; ++j) {
//             if (a_vec[i] + a_vec[j] == a_num) {
//                 return true;
//             }
//         }
//     }

//     return false;
// }


//2. with using unordered set - time complexity o(n) , space complexity o(n)
// bool findPairWithSum(std::vector<int> a_vec, int a_num) {
//     std::unordered_set<int> numsSet;

//     for(int num : a_vec) {
//         int diff = a_num - num;

//         if(numsSet.find(diff) != numsSet.end()){
//             return true;
//         }

//         numsSet.insert(num);
//     }

//     return false;
// }

//3. with sort vec - time complexity o(nlog(n)) , space complexity o(1)
// bool findPairWithSum(std::vector<int> a_vec, int a_num) {
//     int left = 0;
//     int right = a_vec.size() - 1;

//     // Sort the vector (O(n*log(n)) time complexity)
//     std::sort(a_vec.begin(), a_vec.end());

//     while (left < right) {
//         int sum = a_vec[left] + a_vec[right];

//         if (sum == a_num) {
//             return true; // Found a pair of elements that sum up to a_num
//         } else if (sum < a_num) {
//             left++;
//         } else {
//             right--;
//         }
//     }

//     return false; // No such pair found
// }

//4. with sort vec & binary search- time complexity o(nlog(n)) , space complexity o(1)
bool binarySearch(std::vector<int> const& v, int start, int end, int val)
{
    if (start > end) {
        return false;
    }
    int mid = start + (end - start )/2;

    if (v[mid] == val) {
        return true;
    }

    if (v[mid] > val ) {
        return binarySearch(v, start, mid - 1, val);
    }
    else {
        return binarySearch(v, mid + 1, end, val);
    }
}

bool findPairWithSum(std::vector<int>& v, int x)
{
    std::sort(v.begin(), v.end());

    for (int i = 0; i < v.size(); ++i) {
        int toCheck = x - v[i];
        if (v[i] == toCheck) {
            if(v[i+1] != toCheck) {
                continue;
            }
            else {
                return true;
            }
        }
        if (binarySearch(v, 0, v.size() - 1, toCheck)) {
            return true;
        }
    }

    return false;
}

int main() {
    std::vector<int> nums = {1, 2, 3, 4, 5};
    int num = 9;

	for (auto& i : nums) {
        std::cout << i << " ";
    }
	std::cout << std::endl;

    if (findPairWithSum(nums, num)) {
        std::cout << "Two elements in the vector sum up to " << num << std::endl;
    } else {
        std::cout << "No two elements in the vector sum up to " << num << std::endl;
    }

    return 0;
}
