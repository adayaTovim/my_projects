#include <iostream>
#include <vector>
#include <limits.h>

/*Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.
The overall run time complexity should be O(log (m+n)).

Example 1:
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2*/


//naive algorithm
// double findMedian(const std::vector<int>& nums1, const std::vector<int>& nums2) {
//     int size1 = nums1.size();
//     int size2 = nums2.size();
//     std::vector<int> merged;
//     int i = 0, j = 0;
//     while(i < size1 && j < size2) {
//             if (nums1[i] < nums2[j]) {
//                 merged.push_back(nums1[i]);
//                 ++i;
//             } else {
//                 merged.push_back(nums2[j]);
//                 ++j;
//             }
//     }

//     while (i < size1) {
//         merged.push_back(nums1[i]);
//         ++i;
//     }

//     while (j < size2) {
//         merged.push_back(nums2[j]);
//         ++j;
//     }

//     int mergedSize = size1 + size2;
//     int midIndex = mergedSize / 2;

//     if(mergedSize % 2 == 0) {
//         return (merged[midIndex - 1] + merged[midIndex]) / 2.0;
//     } else {
//         // odd
//         return merged[midIndex];
//     }
// }

double findMedian(const std::vector<int>& nums1, const std::vector<int>& nums2) {
    int size1 = nums1.size();
    int size2 = nums2.size();

    // Ensure nums1 is the smaller array
    if (size1 > size2) {
        return findMedian(nums2, nums1);
    }

    int low = 0;
    int high = size1;

    while (low <= high) {
		// partition point in nums1
        int mid1 = (low + high) / 2;
		// partition point in nums2
        int mid2 = (size1 + size2 + 1) / 2 - mid1;

        // calculate the maximum values of the left side
        int maxLeft1 = (mid1 == 0) ? INT_MIN : nums1[mid1 - 1];
		// int maxLeft1;
		// if (mid1 == 0) {
		// 	maxLeft1 = INT_MIN;
		// } else {
		// 	maxLeft1 = nums1[mid1 - 1];
		// }

        int maxLeft2 = (mid2 == 0) ? INT_MIN : nums2[mid2 - 1];

        // calculate the minimum values of the right side
        int minRight1 = (mid1 == size1) ? INT_MAX : nums1[mid1];
        int minRight2 = (mid2 == size2) ? INT_MAX : nums2[mid2];

        // check the partition
        if (maxLeft1 <= minRight2 && maxLeft2 <= minRight1) {
            // median found
            if ((size1 + size2) % 2 == 0) {
                return (std::max(maxLeft1, maxLeft2) + std::min(minRight1, minRight2)) / 2.0;
            } else {
                return std::max(maxLeft1, maxLeft2);
            }
        } else if (maxLeft1 > minRight2) {
            // adjust partition range to the left
            high = mid1 - 1;
        } else {
            // adjust partition range to the right
            low = mid1 + 1;
        }
    }

    // invalid input or no median found
    return -1;
}

int main()
{
    std::vector<int> nums1 = {1,2,3,4,5,6,7,8};
    std::vector<int> nums2 = {1,2,3,4,5};
    std::cout << "Median: "<< findMedian(nums1,nums2)<<std::endl;

    std::vector<int> nums3 = {1,2,3,4,5,6,7,8};
    std::vector<int> nums4 = {1,2,3,4};
    std::cout << "Median: "<< findMedian(nums3,nums4)<<std::endl;

    return 0;
}
