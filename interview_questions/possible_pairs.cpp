/*Given a set of ints, calculate the number of possible pairs of ints x and y from
the set where x < y */

#include <iostream>
#include <set>

int possiblePairs(const std::set<int>& a_set)
{
    int size = a_set.size();
    if(size < 2) {
        return 0;
    }

    int counter = 0;
    auto it = a_set.begin();
    auto end = a_set.end();

    while(it != end) {
        auto nextIt = std::next(it);
        while(nextIt != end) {
            if(*nextIt > *it) {
                ++counter;
            }
            ++nextIt;
        }
        ++it;
    }

    return counter;
}

void printSet(const std::set<int>& a_set)
{
    auto it = a_set.begin();
    auto end = a_set.end();
    while (it != end) {
        std::cout << *it << " ";
        ++it;
    }
    std::cout << "\n";
}


int main() {
    std::set<int> mySet;

    mySet.insert(1);
    mySet.insert(2);
    mySet.insert(3);
    mySet.insert(4);
    mySet.insert(5);

    printSet(mySet);

    int pairCount = possiblePairs(mySet);
    std::cout << "Number of pairs where x < y: " << pairCount << std::endl;

    return 0;
}
