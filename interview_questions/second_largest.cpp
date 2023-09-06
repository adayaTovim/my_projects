#include <iostream>
#include <vector>
#include <climits>

//Build a function that accepts a matrix and finds the second largest element

int findSecondLargest(const std::vector<std::vector<int>>& a_matrix)
{
    if (a_matrix.empty() || a_matrix[0].empty()) {
        std::cerr << "Matrix is empty." << std::endl;
        return -1;
    }

    int first = a_matrix[0][0];
    int second = INT_MIN;
    for(auto row : a_matrix) {
        for(auto col : row) {
            if(col > first) {
                second = first;
                first = col;
            } else if(col > second && col != first) {
                second = col;
            }
        }
    }
    if (second == INT_MIN) {
        std::cerr << "No second largest element found." << std::endl;
        return -1;
    }

    return second;
}

int main()
{
    std::vector<std::vector<int>> matrix = {
        {2, 4, 15},
        {6, 8, 20},
        {12, 1, -2}
    };

    int result = findSecondLargest(matrix);
    if (result != -1) {
        std::cout << "The second largest element is: " << result << std::endl;
    }

    std::vector<std::vector<int>> matrix2 = {
        {2, 2},
        {2, 2}
    };

    int result2 = findSecondLargest(matrix2);
    if (result2 != -1) {
        std::cout << "The second largest element is: " << result2 << std::endl;
    }

    std::vector<std::vector<int>> matrix3 = {};

    int result3 = findSecondLargest(matrix3);
    if (result3 != -1) {
        std::cout << "The second largest element is: " << result3 << std::endl;
    }


    return 0;
}
