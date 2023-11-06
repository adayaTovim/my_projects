// Find the largest number of developers required
// Task 1 takes from week 3 to week 5 and requires 6 developers
// Task 2 takes from week 21 to week 30 and requires 2 developers
// Task 3 takes from week 4 to week 7 and requires 4 developers

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>

// // solution 1
// // with a vector - every index present week and the value is the number of workers
// std::vector<int> weeks(50,0);

// void addTask(int a_start, int a_end, int a_numOfWorkers)
// {
//     if(a_start < 1 || a_end > 50 || a_start > a_end) {
//         return;
//     }

//     for(int i = a_start; i <= a_end; ++i) {
//         weeks[i-1] += a_numOfWorkers;
//     }
// }

// int findMaxWorkers(std::vector<int>& a_weeks)
// {
//     int max = 0;
//     for(auto i : a_weeks) {
//         max = std::max(max, i);
//     }
//     return max;
// }



// // solution 2
// // with a map - it doesn't waste space for weeks that don't have workers
// std::unordered_map<int,int> weeks;

// void addTask(int a_start, int a_end, int a_numOfWorkers)
// {
//     if(a_start < 1 || a_end > 50 || a_start > a_end) {
//         return;
//     }

//     for(int i = a_start; i <= a_end; ++i) {
//         weeks[i] += a_numOfWorkers;
//     }
// }

// int findMaxWorkers(std::unordered_map<int,int>& a_weeks)
// {
//     int max = 0;
//     for(auto i : a_weeks) {
//         max = std::max(max, i.second);
//     }
//     return max;
// }



//solution 2
// with map to track changes in the number of workers
std::map<int,int> changesWeeks;

void addTask(int a_start, int a_end, int a_numOfWorkers)
{
    if(a_start < 1 || a_end > 50 || a_start > a_end) {
        return;
    }

    changesWeeks[a_start] += a_numOfWorkers;
    changesWeeks[a_end + 1] -= a_numOfWorkers;
}

int findMaxWorkers(std::map<int,int>& a_weeks)
{
    int currentWorkersNums = 0;
    int max = 0;
    for(auto i : a_weeks) {
        currentWorkersNums += i.second;
        max = std::max(max, currentWorkersNums);
    }
    return max;
}

int main()
{
    addTask(3, 5, 6);
    addTask(21, 30, 2);
    addTask(4, 8, 4);

    std::cout << findMaxWorkers(changesWeeks)<<"\n";

    return 0;
}
