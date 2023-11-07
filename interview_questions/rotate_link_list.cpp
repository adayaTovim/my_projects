#include <iostream>
#include <list>

void rotateLinkedList(std::list<int>& list, int k)
{
    auto first = list.begin();
    auto second = list.begin();

    //bring second to position for the first element after rotation
    for(int i = 0; i < k; ++i) {
        ++second;
    }

    while(second != list.end()) {
        std::swap(*first, *second);
        ++first;
        ++second;
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
    std::list<int> l = {1,2,3,4,5,6};
    printList(l);

    rotateLinkedList(l,2);
    printList(l);

    return 0;
}
