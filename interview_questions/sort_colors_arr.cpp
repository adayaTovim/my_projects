//Given an array with 3 colors sort it

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

// solution 1 - bubble sort o(n^2)
// void sortColors(std::vector<std::string>& a_vector)
// {
//     size_t size = a_vector.size();
//     std::string next;
//     std::string current;
//     for(size_t j = 0; j < size; ++j) {
//         for(size_t i = 0; i < size -1; ++i) {
//             current = a_vector[i];
//             next = a_vector[i + 1];
//             if(current > next) {
//                 std::swap(a_vector[i], a_vector[i+1]);
//             }
//         }
//     }
// }

// solution 2 - quick sort o(nlog(n))
std::map<std::string,int> orderColor = {{"red",1},{"blue",2},{"yellow",3}};
void sortColors(std::vector<std::string>& a_vector)
{
    //std::sort(a_vector.begin(), a_vector.end());

    //if we want to sort by specific order:
    std::sort(a_vector.begin(), a_vector.end(), [](const std::string& a, const std::string& b){
        return (orderColor[a] > orderColor[b]);
    });
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
