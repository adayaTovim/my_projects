//Given an array with 3 colors sort it

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

// //solutiion 1 - bubble sort
// std::map<std::string,int> order = {{"blue",1},{"red",2},{"green",3}};
// void sortColors(std::vector<std::string>& a_colors)
// {
//     int size = static_cast<int>(a_colors.size());
//     bool swapped = false;
//     for(int i = 0; i < size; ++i) {
//         swapped = false;
//         for(int j = 0; j < size-1; ++j) {
//             if(order[a_colors[j]] > order[a_colors[j+1]]) {
//                 std::swap(a_colors[j], a_colors[j+1]);
//                 swapped = true;
//             }
//         }
//         if(!swapped) {
//             return;
//         }
//     }
// }

// // solution 2 - quick sort o(nlog(n)) using std::sort
// std::map<std::string,int> orderColor = {{"red",1},{"blue",2},{"yellow",3}};
// void sortColors(std::vector<std::string>& a_vector)
// {
//     //std::sort(a_vector.begin(), a_vector.end());

//     //if we want to sort by specific order:
//     std::sort(a_vector.begin(), a_vector.end(), [](const std::string& a, const std::string& b){
//         return (orderColor[a] > orderColor[b]);
//     });
// }

// // solution 3 - quick sort o(nlog(n))
std::map<std::string, int> order = {{"blue", 1}, {"red", 2}, {"green", 3}};

// helper function for Quick Sort partitioning
int partition(std::vector<std::string>& colors, int low, int high) {
    std::string pivotColor = colors[high];
    int i = low - 1; // i marks the boundary between elements with color orders less than or equal to the pivot and those greater than the pivot
    for (int j = low; j < high; ++j) {
        if (order[colors[j]] <= order[pivotColor]) {
            ++i;
            std::swap(colors[i], colors[j]);
        }
    }
    std::swap(colors[i + 1], colors[high]);
    return i + 1;
}

// Quick Sort implementation
void quickSortColors(std::vector<std::string>& colors, int low, int high) {
    if (low < high) {
        int pivot = partition(colors, low, high);
        quickSortColors(colors, low, pivot - 1);
        quickSortColors(colors, pivot + 1, high);
    }
}

// Function to sort colors using Quick Sort
void sortColors(std::vector<std::string>& colors) {
    int size = static_cast<int>(colors.size());
    quickSortColors(colors, 0, size - 1);
}


void printVector(const std::vector<std::string>& a_vector)
{
    for(auto i : a_vector) {
        std::cout << i << ", ";
    }
    std::cout<<std::endl;
}

int main()
{
    std::vector<std::string> colors = {"red", "red", "blue", "yellow", "red", "red", "blue", "yellow"};
    printVector(colors);

    sortColors(colors);
    printVector(colors);

    return 0;
}
