#include <vector>
#include <iostream>

//The seat function is designed to solve a seating arrangement problem
//in which we want to find the maximum number of 4-passenger clusters within a specified number of rows and a list of occupied seats.

int seat(int n, std::vector<std::vector<int>>& occupiedSeats)
{
    std::vector<std::vector<int>> allSeats(n, std::vector<int>(10, 0));
    //fill all seats;
    for(auto seat : occupiedSeats) {
        int row = seat[0] - 1;
        int col = seat[1];
        if(row >= 0 && row < n && col >= 0 && col < 10) {
            allSeats[row][col] = 1;
        }
    }

    int maxOptions = 0;
    for (int row = 0; row < n; ++row) {
        int currentClusterSize = 0;
        int firstEmptySeat = 0;

        // check each seat in the row
        for (int col = 0; col < 10; ++col) {
            if (allSeats[row][col] == 0) {
                if(currentClusterSize == 0) {
                    firstEmptySeat = col;
                }
                ++currentClusterSize;

                if (currentClusterSize == 4) {
                    col = firstEmptySeat;
                    ++maxOptions;
                    currentClusterSize = 0;
                }
            }
            else {
                currentClusterSize = 0;
            }
        }
    }

    return maxOptions;
}

int main()
{
    int n = 3;

    std::vector<std::vector<int>> occupiedSeats = {
        {1, 0},
        {1, 1},
        {1, 3},
        {2, 2},
        {2, 3},
        {2, 4}
    };

    int result = seat(n, occupiedSeats);
    std::cout << "maximum number of 4 passenger clusters: " << result << std::endl;

    return 0;
}

