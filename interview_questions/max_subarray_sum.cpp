/*Given a vector of integers write an efficient function to find the sum of
contiguous subarray within a one-dimensional array of numbers which has the
largest sum.*/

#include <iostream>
#include <vector>

int maxSubarraySum(const std::vector<int>& a_vector)
{
    int size = a_vector.size();
    if(0 == size) {
        return 0;
    }

    int currentSum = a_vector[0];
    int maxSum = a_vector[0];
    for(int i = 1; i < size; ++i) {
        currentSum = std::max(a_vector[i], a_vector[i] + currentSum);
		maxSum = std::max(currentSum, maxSum);
    }

    return maxSum;
}

void printVector(const std::vector<int>& a_vector)
{
    auto it = a_vector.begin();
    auto end = a_vector.end();
    while (it != end) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << "\n";
}


int main() {
    std::vector<int> vec {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    printVector(vec);

    std::cout<<"The largest subarray sum: "<<maxSubarraySum(vec)<<std::endl;

    return 0;
}

