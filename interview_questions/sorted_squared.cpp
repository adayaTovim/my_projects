//Given a sorted array with positive and negative numbers.
//return a sorted array which all members of the original array are squared

#include <iostream>
#include <vector>
#include <algorithm>

std::vector<int> sortedSquaredVector(const std::vector<int>& a_vec)
{
    int size = a_vec.size();
    std::vector<int> result(size);
    if(size < 1) {
        std::cerr<<"empty vector\n";
        return result;
    }

    int left = 0;
    int right = size -1;
    int resultIndex = right;

    while(left <= right) {
        int leftNum = a_vec[left] * a_vec[left];
        int rightNum = a_vec[right] * a_vec[right];

        if(leftNum > rightNum) {
            result[resultIndex] = leftNum;
            ++left;
        } else {
            result[resultIndex] = rightNum;
            --right;
        }

        --resultIndex;
    }

    return result;
}

int main()
{
    std::vector<int> v = {-1, 1, 3, -2, 4};
    std::vector<int> result = sortedSquaredVector(v);

    for(auto i : result) {
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;

    std::vector<int> v2 = {};
    std::vector<int> result2 = sortedSquaredVector(v2);

    for(auto i : result2) {
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;
    return 0;
}

