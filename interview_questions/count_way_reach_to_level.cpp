#include <iostream>
#include <vector>

//The number of ways you can reach level 100 on the ladder- you can go up one or two steps

// calculate sum of Fibonacci sequence
// Time complexity: O(n) since it calculates each Fibonacci number only once.
// Space complexity: O(1) as it uses a constant amount of space.
long countWayToLevel(int n)
{
    long long prev = 1;
    long curr = 1;
    long next = 0;
    for (int i = 2; i <= n; ++i) {
        next = prev + curr;
        prev = curr;
        curr = next;
    }

    return next;
}

//with pure recursive
//Time complexity: O(2^n), which is exponential.
//Space complexity: O(n) due to the recursive call stack.
long long countWayToLevelRec1(long long n) {
    // there is one way to be at step 0 or 1 (not moving or taking 1 step).
    if ( n == 0|| n == 1) {
        return 1;
    }

    return n = countWayToLevel(n - 1) + countWayToLevel(n - 2);
}

//with recursive and vec to store the results
// Time complexity: O(n), as each Fibonacci number is calculated only once.
// Space complexity: O(n) due to the memoization vector.
std::vector<long long> v(101,-1);
long long countWayToLevelRec2(int n) {
    //// if the result is already calculated, return it
    if (v[n] != -1) {
        return v[n];
    }

    if (n == 0|| n == 1) {
        v[n] = 1;
    } else {
        v[n] = countWayToLevel(n - 1) + countWayToLevel(n - 2);
    }

    return v[n];
}

//dynamic programming
// Time complexity: O(n) as each step is calculated only once.
// Space complexity: O(n) due to the dynamic programming vector.
long long countWayToLevelDp(int n)
{
    std::vector<long long> v(101);
    v[0] = 1;
    v[1] = 1;
    for(int i = 2; i <= n; ++i) {
        v[i] = v[i - 1] + v[i - 2];
    }
    return v[n];
}

int main()
{
    long long result1 = countWayToLevel(100);
    std::cout << result1 << std::endl;

    long long result2 = countWayToLevelRec1(100);
    std::cout << result2 << std::endl;

    long long result3 = countWayToLevelRec2(100);
    std::cout << result3 << std::endl;

    long long result4 = countWayToLevelDp(100);
    std::cout << result4 << std::endl;
    return 0;
}
