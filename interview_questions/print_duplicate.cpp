// array of size N and the range of numbers is between 1 and n.
// print the numbers that appeared at least twice.

#include <vector>
#include <iostream>
#include <unordered_map>

void printRepeatingNums(const std::vector<int>& a_vec)
{
    if(a_vec.size() < 2) {
        return;
    }

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

//naive way
// void printRepeatingNums(const std::vector<int>& a_vec)
// {
//     int size = a_vec.size();
//     for(int i = 0; i < size; ++i) {
//         bool isRepeated = false;
//         for (int j = i + 1; j < size; ++j) {
//             if(a_vec[i] == a_vec[j]) {
//                 isRepeated = true;
//             }
//         }
//         if(isRepeated) {
//             std::cout<<a_vec[i]<<" ";
//         }
//     }
// }

//function that print unique num , itis work only if there is only one unique
void findUniqueNum(const std::vector<int>& a_vec)
{
    int result = 0;
    for (auto num : a_vec) {
        result ^= num;
    }
    std::cout<<result<<std::endl;
}

int main()
{
    std::vector<int> v = {1,2,3,1,1,4,5,6,7,3,8,10};
    printRepeatingNums(v);

	std::vector<int> v2 = {1,2,3,1,2};
    //findUniqueNum(v2);
    return 0;
}

