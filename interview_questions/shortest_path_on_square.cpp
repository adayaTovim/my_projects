// Shortest path on a Square
// Given side of a square n and two points (x1, y1) and (x2, y2)
// on the boundaries of the given square.
// The task is to find the shortest path through the square sides between these two points
// where the corner coordinates of the square are (0, 0), (n, 0), (0, n), and (n, n).
// Examples:
// Input: n = 2, x1 = 0, y1 = 0, x2 = 1, y2 = 0
// Output: 1
// Input: n = 26, x1 = 21, y1 = 0, x2 = 26, y2 = 14
// Output: 19

#include <iostream>

// int shortestPathOnSquare(int n, int x1, int y1, int x2, int y2)
// {
//     // if the point in parallel lines
//     if(!(std::abs(x1-x2) == n || std::abs(y1-y2) == n )) {
//         return std::abs(x2-x1) + std::abs(y2-y1);
//     }

//     int path = 0;
//     if(std::abs(x1-x2) == n) {
//         path += std::min(std::abs(n-y1) + std::abs(n-y2), std::abs(y1-0) +  std::abs(y2-0));
//     } else if(std::abs(y1-y2) == n) {
//         path += std::min(std::abs(n-x1) + std::abs(n-x2), std::abs(x1-0) +  std::abs(x2-0));
//     }
//     path += std::abs(n);

//     return path;

//     //instead i can return
//     //return std::min(x1+x2+y1+y2 , 4*n - (x1+x2+y1+y2))
// }

int shortestPathOnSquare(int n, int x1, int y1, int x2, int y2)
{
    // if the point in parallel lines
    if(!(std::abs(x1-x2) == n || std::abs(y1-y2) == n )) {
        return std::abs(x2-x1) + std::abs(y2-y1);
    }

    return std::min(x1+x2+y1+y2 , 4*n - (x1+x2+y1+y2));;
}

int main()
{
    std::cout<<shortestPathOnSquare(2,0,0,1,0)<<"\n"; //1
    std::cout<<shortestPathOnSquare(26,21,0,26,14)<<"\n"; // 19
    std::cout<<shortestPathOnSquare(4,2,0,3,4)<<"\n"; // 7
    std::cout<<shortestPathOnSquare(4,0,2,4,3)<<"\n"; // 7
    std::cout<<shortestPathOnSquare(5,4,0,1,5)<<"\n"; // 10
    std::cout<<shortestPathOnSquare(5,3,0,1,5)<<"\n"; // 9

}
