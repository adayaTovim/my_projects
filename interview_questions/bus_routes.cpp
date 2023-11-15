// Bus Routes
// You are given an array routes representing bus routes where routes[i] is a bus route that the ith bus repeats forever.

// For example, if routes[0] = [1, 5, 7], this means that the 0th bus travels in the sequence 1 -> 5 -> 7 -> 1 -> 5 -> 7 -> 1 -> ... forever.
// You will start at the bus stop source (You are not on any bus initially), and you want to go to the bus stop target. You can travel between bus stops by buses only.

// Return the least number of buses you must take to travel from source to target. Return -1 if it is not possible.

// Example 1:
// Input: routes = [[1,2,7],[3,6,7]], source = 1, target = 6
// Output: 2
// Explanation: The best strategy is take the first bus to the bus stop 7, then take the second bus to the bus stop 6.

// Example 2:
// Input: routes = [[7,12],[4,5,15],[6],[15,19],[9,12,13]], source = 15, target = 12
// Output: -1

#include <vector>
#include <iostream>
#include <unordered_map>
#include <queue>
#include <unordered_set>

int numBusesToDestination(std::vector<std::vector<int>>& routes, int source, int target) {

    if (routes.empty() || source == target) {
        return 0;
    }

    // create a graph where each bus stop is connected to the buses that pass through it
    // map that the key is the bus stop and the value is a vector of all the buses that pass there
    std::unordered_map<int, std::vector<int>> graph;
    for (size_t i = 0; i < routes.size(); ++i) {
        for (int stop : routes[i]) {
            graph[stop].push_back(i);
        }
    }

    std::queue<std::pair<int, int>> bfsQueue;
    bfsQueue.push({source, 0}); //the stop and num of buses up to here (this is the first bus you take)
    std::unordered_set<int> visitedStop = {source};

    while (!bfsQueue.empty()) {
        int currStop = bfsQueue.front().first;
        int bus = bfsQueue.front().second;
        bfsQueue.pop();
        if (currStop == target) {
            return bus;
        }
        //check which root contain the stop we looking for
        for (int rootNum : graph[currStop]) { //for ex stop 1-> in root 0 only so graph[stop] size is 1 and contain 0 only

            //look for the next stop in the way
            //check if we checked this next stop
            //now you go over the root 0[] ak [1,2,7]
            for (int nextStop : routes[rootNum]) {
                if (visitedStop.find(nextStop) == visitedStop.end()) {
                    visitedStop.insert(nextStop);
                    //doesnt push to the bfsQueue 1, 1 (stop 1 bus 1) 1 is in visitedStop
                    //push 2, 1
                    //push 7, 1
                    bfsQueue.push({nextStop, bus + 1});
                }
            }
            //delete this root
            routes[rootNum].clear();
        }
    }
    return -1;
}

int main() {
    // Example 1
    std::vector<std::vector<int>> routes1 = {{1, 2, 7}, {3, 6, 7}};
    int source1 = 1, target1 = 6;
    int result1 = numBusesToDestination(routes1, source1, target1);
    std::cout << "Example 1: " << result1 << std::endl;

    // Example 2
    std::vector<std::vector<int>> routes2 = {{7, 12}, {4, 5, 15}, {6}, {15, 19}, {9, 12, 13}};
    int source2 = 15, target2 = 12;
    int result2 = numBusesToDestination(routes2, source2, target2);
    std::cout << "Example 2: " << result2 << std::endl;

    return 0;
}
