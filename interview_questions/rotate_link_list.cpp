#include <iostream>
#include <list>
#include <vector>

void rotateLinkedList(std::list<int>& list, int k)
{
    std::vector<int> rest;

    auto first = list.begin();
    auto second = list.begin();

    //bring second to position for the first element after rotation
    for(int i = 0; i < k; ++i) {
        //save the k first element
        rest.push_back(*second);
        ++second;
    }

    while(second != list.end()) {
        std::swap(*first, *second);
        ++first;
        ++second;
    }

    // //handle the rest
    for(auto i : rest) {
        *first = i;
        ++first;
    }
}

void printList(const std::list<int>& list)
{
    for(auto i : list) {
        std::cout<<i<<" ";
    }
    std::cout<<std::endl;
}

int main()
{
    std::list<int> l = {1,2,3,4,5,6,7,8,9};
    printList(l);

    rotateLinkedList(l,2);
    printList(l);

    return 0;
}
