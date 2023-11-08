#include <iostream>
#include <list>
#include <vector>

// rotate a linked list by k positions

class Node {
public:
    Node() : m_next(nullptr) {};
    Node(Node* a_next, int a_data) : m_next(a_next), m_data(a_data){};

    Node* m_next;
    int m_data;
};


Node* rotateList(Node* a_head, int k)
{
    Node* originalTail = a_head;
    Node* newTail = a_head;
    Node* newHead = a_head;

    for(int i = 0; i < k; ++i) {
        newTail = newHead;
        newHead = newHead->m_next;
    }

    newTail->m_next = nullptr;
    originalTail = newHead;

    while(originalTail->m_next != nullptr) {
        originalTail = originalTail->m_next;
    }

    originalTail->m_next = a_head;

    return newHead;
}

void printList(Node* a_head)
{
    while (a_head != nullptr) {
        std::cout << a_head->m_data << " ";
        a_head = a_head->m_next;
    }
    std::cout << "\n";
}

//with std::list
// void rotateLinkedList(std::list<int>& list, int k)
// {
//     std::vector<int> rest;

//     auto first = list.begin();
//     auto second = list.begin();

//     //bring second to position for the first element after rotation
//     for(int i = 0; i < k; ++i) {
//         //save the k first element
//         rest.push_back(*second);
//         ++second;
//     }

//     while(second != list.end()) {
//         std::swap(*first, *second);
//         ++first;
//         ++second;
//     }

//     // //handle the rest
//     for(auto i : rest) {
//         *first = i;
//         ++first;
//     }
// }

// void printList(const std::list<int>& list)
// {
//     for(auto i : list) {
//         std::cout<<i<<" ";
//     }
//     std::cout<<std::endl;
// }

// // another way with std::list
// void rotateList(std::list<int>& a_list, int k)
// {
//     for(int i = 0; i < k; ++i) {
//         a_list.push_back(*a_list.begin());
//         a_list.pop_front();
//     }
// }

int main()
{
	Node* a = nullptr;
    Node* b = new Node(a, 1);
    Node* c = new Node(b, 2);
    Node* d = new Node(c, 3);
    Node* e = new Node(d, 4);
    Node* f = new Node(e, 5);
    Node* g = new Node(f, 6);

    Node* a_head = g;

    printList(a_head);

    Node* result = rotateList(a_head, 3);

    printList(result);

    // std::list<int> l = {1,2,3,4,5,6,7,8,9};
    // printList(l);

    // rotateLinkedList(l,2);
    // printList(l);

    return 0;
}
