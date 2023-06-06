#include <iostream>
#include <vector>
#include <algorithm>

/*Write a function that takes an array of integers and another integer and will return true if the integer is present in the array. 
Should be O(1) space with minimum compare operations.*/

// // naive way
// bool isIntegerPresent(const std::vector<int>& a_arr, int a_target) {
//     for (int i = 0; i < a_arr.size(); ++i) {
//         if (a_target == a_arr[i]) {
//             return true;
//         }
//     }
//     return false;
// }

// // with find function
// bool isIntegerPresent(const std::vector<int>& a_vector, const int a_num)
// {
//     if(std::find(begin(a_vector), end(a_vector), a_num) == end(a_vector)) {
//         return false;
//     }

//     return true;
// }


//with xor 
bool isIntegerPresent(const std::vector<int>& arr, int target) {
    for (int i = 0; i < arr.size(); ++i) {
        if ((target ^ arr[i]) == 0) {
            return true;
        }
    }
    return false;
}

int main() {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    int target = 7;

    bool result = isIntegerPresent(arr, target);
    std::cout << result << std::endl;

    return 0;
}


// // with arr in c
// bool isIntegerPresent(const int* a_arr, int a_size, int a_target) {
//     for (int i = 0; i < a_size; ++i) {
//         if(!(a_target ^ a_arr[i])){
//             return true;
//         }
//     }

//     return false;
// }

// int main() {
//     int arr[] = {1, 2, 3, 4, 5};
//     int size = sizeof(arr) / sizeof(arr[0]);
//     int target = 4;

//     bool result = isIntegerPresent(arr, size, target);
//     std::cout << result << std::endl;

//     return 0;
// }