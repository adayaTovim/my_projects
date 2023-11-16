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

// i
#include <vector>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <queue>

int numBusesToDestination(std::vector<std::vector<int>>& routes, int source, int target)
{
    //fill in a graphic map with each station and all the buses that pass through the station
    //key- station
    //value - vector of all the buses that pass through this station
    std::unordered_map<int,std::vector<int>> mapGraph;
    for(size_t i = 0; i < routes.size(); ++i) {
        for(int station : routes[i]) {
            mapGraph[station].push_back(i);
        }
    }

    std::unordered_set<int> visitedStations = {source};

    //create queue to make bfs search
    //q present pair - the station and num of buses pass there
    std::queue<std::pair<int,int>> bfsQueue;
    bfsQueue.push(std::make_pair(source,0));

    while(!bfsQueue.empty()) {
        int currStation = bfsQueue.front().first;
        int numOfBuses = bfsQueue.front().second;
        bfsQueue.pop();

        if(currStation == target) {
            return numOfBuses;
        }

        std::vector<int> stationBuses = mapGraph[currStation]; // all the buses that trhough in curr station
        for(int bus : stationBuses) {
            // we check if there is bus that through in the target
            for(int nextStation : routes[bus]) {
                if(visitedStations.find(nextStation) == visitedStations.end()) {
                    visitedStations.insert(nextStation);
                    bfsQueue.push(std::make_pair(nextStation,numOfBuses + 1));
                }
            }
            routes[bus].clear();
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

// Explain
// This solution uses a breadth-first search (BFS) algorithm to find the minimum number of buses needed to travel from a source station to a target station.
// Here's how it works:

// 1. Building the Graph:
// It starts by creating a graph representation where each station is connected to the buses that pass through it. This is done using an unordered map mapGraph.
// The key in mapGraph is the station number, and the value is a vector containing the indices of buses that pass through that station.

// 2. It initializes a visitedStations set to keep track of visited stations, starting with the source station.

// 3. Use queue (bfsQueue) to perform the BFS traversal. Each entry in the queue is a pair containing the station and the number of buses taken to reach that station.

// 4.BFS Traversal:
	// a. While the queue is not empty:
	// Dequeues a station and the number of buses taken to reach that station.
	// b. If the dequeued station is the target, it returns the number of buses taken to reach it.
	// Otherwise, it retrieves the buses that pass through the current station (stationBuses).
	// c. For each bus passing through that station:
	// Checks each station on the bus route (nextStation) and if the station has not been visited yet - Marks the station as visited.
	// d. Enqueues the next station along with the incremented number of buses taken to reach it.
	// e. Clears the routes for buses that have been visited (routes[bus].clear()) to avoid revisiting them.

// 5.Returns -1 if there is no valid route found.
