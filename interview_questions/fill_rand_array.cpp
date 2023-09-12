//write program to fill an array of size 100 with random values between 1 and 100, ensuring that each value is unique within the array


#include <array>
#include <iostream>
#include <cstdlib>
#include <list>

std::list<int> createList()
{
    std::list<int> l;
    int num = 1;
    while(num <= 100) {
        l.push_back(num);
        ++num;
    }

    return l;
}

int rand(int x)
{
    int min = 1;
    int max = x;

    return min + (rand() % (max - min + 1));
}

void fillRandArray(std::array<int,100>& a_array) {
    std::list<int> list = createList();

    for(int i = 100; i > 0; --i) {
        int index = rand(i);
        std::list<int>::iterator it = list.begin();
        //move the iterator to the correct position in the list
        std::advance(it, index - 1);
        int num = *it;
        list.erase(it);

        a_array[num-1] = num;
    }
}

int main()
{
    std::array<int, 100> myArray;
    fillRandArray(myArray);

    // print the filled array to verify the result
    for (int num : myArray) {
        std::cout << num << " ";
    }

    return 0;
}

