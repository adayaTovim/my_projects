#include <vector>
#include <iostream>
#include <algorithm>

void sortVecByZero(std::vector<int>& a_vec)
{
    size_t size = a_vec.size();
    size_t start = 0;
    size_t end = size - 1;

    while(end > start) {
        if(a_vec[end] == 0 && a_vec[start] != 0) {
            std::swap(a_vec[start], a_vec[end]);
            --end;
            ++start;
            continue;
        }
        if(a_vec[end] != 0) {
            --end;
        }
        if(a_vec[start] == 0) {
            ++start;
        }
    }
}

// //with use stable_partition
// void sortVecByZero(std::vector<int>& a_vec) {
//     std::stable_partition(a_vec.begin(), a_vec.end(), [](int elem) {
//         return elem == 0;
//     });
// }

int main()
{
    std::vector<int> v {0,1,2,5,4,0,3,0,8,0};

    std::cout << "Original vector: ";
    for (int elem : v) {
        std::cout << elem << ' ';
    }
    std::cout << "\n";

    sortVecByZero(v);

    std::cout << "sorted vector: ";
    for (int elem : v) {
        std::cout << elem << ' ';
    }
    return 0;
}
