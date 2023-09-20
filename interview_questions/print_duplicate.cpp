// array of size N and the range of numbers is between 1 and n.
// print the numbers that appeared at least twice.

#include <vector>
#include <iostream>
#include <unordered_map>

void printRepeatingNums(const std::vector<int>& a_vec)
{
    std::unordered_map<int,int> map;
    for (auto num : a_vec) {
        map[num]++;
    }

    for (const auto& pair : map) {
        if (pair.second > 1) {
            std::cout << pair.first << std::endl;
        }
    }
}

int main()
{
    std::vector<int> v = {1,2,3,1,1,4,5,6,7,3,8,10};
    printRepeatingNums(v);
    return 0;
}

