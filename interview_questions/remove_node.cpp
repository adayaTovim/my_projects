
#include <iostream>

/*Describe a cyclic single linked list in C
Given a pointer to a node in such a list remove it. In o(1)*/

struct Node {
    size_t m_data;
    Node* m_next;
};

void removeNode(Node& a_nodeToRemove)
{
    if (a_nodeToRemove.m_next == nullptr) {
        std::cerr << "empty node \n";
        return;
    }

    Node* nextNode = a_nodeToRemove.m_next;
    a_nodeToRemove.m_data = nextNode->m_data;
    a_nodeToRemove.m_next = nextNode->m_next;
    
    delete nextNode;
    std::cout<<"Node Removed\n";

    return;
}


int main() {
    Node* head = new Node{1, nullptr};
    Node* node2 = new Node{2, nullptr};
    Node* node3 = new Node{3, nullptr};
    
    head->m_next = node2;
    node2->m_next = node3;
    node3->m_next = head;

    std::cout << "Before removing node: ";
    Node* it = head;
    do {
        std::cout << it->m_data << " ";
        it = it->m_next;
    } while (it != head);
    std::cout << std::endl;

    removeNode(*node2);

    std::cout << "After removing node: ";
    it = head;
    do {
        std::cout << it->m_data << " ";
        it = it->m_next;
    } while (it != head);
    std::cout << std::endl;

    // //remove the last element
    // Node* head = new Node{1, nullptr};
    // Node* node2 = new Node{2, nullptr};
    // Node* node3 = new Node{3, nullptr};
    
    // head->m_next = node2;
    // node2->m_next = node3;
    // node3->m_next = head;

    // std::cout << "Before removing node: ";
    // Node* it = head;
    // do {
    //     std::cout << it->m_data << " ";
    //     it = it->m_next;
    // } while (it != head);
    // std::cout << std::endl;

    // removeNode(*node3);

    // std::cout << "After removing node: ";
    // it = node2;
    // do {
    //     std::cout << it->m_data << " ";
    //     it = it->m_next;
    // } while (it != node2);
    // std::cout << std::endl;

    return 0;
}

// // with loop
// void removeNode(Node*& a_head, Node* a_nodeToRemove)
// {
//     if (a_head == nullptr) {
//         std::cerr << "empty list \n";
//         return;
//     }

//     if (a_head == a_nodeToRemove) {
//         if (a_head->m_next == a_head) {
//             // Only one node in the list
//             delete a_head;
//             a_head = nullptr;
//         } 
        
//         else {
//             Node* lastNode = a_head;
//             while (lastNode->m_next != a_head) {
//                 lastNode = lastNode->m_next;
//             }
//             lastNode->m_next = a_head->m_next;
//             Node* newHead = a_head->m_next;
//             delete a_head;
//             a_head = newHead;
//         }

//         std::cout << "node removed\n";
//         return;
//     }

//     Node* it = a_head;
//     while (it->m_next != a_head) {
//         if (it->m_next == a_nodeToRemove) {
//             it->m_next = a_nodeToRemove->m_next;
//             delete a_nodeToRemove;
//             std::cout << "node removed\n";
//             return;
//         }
//         it = it->m_next;
//     }

//     std::cerr << "node not found\n";
// }


// int main() {
//     Node* head = new Node{1, nullptr};
//     Node* node2 = new Node{2, nullptr};
//     Node* node3 = new Node{3, nullptr};
    
//     head->m_next = node2;
//     node2->m_next = node3;
//     node3->m_next = head;

//     // Test case 1: Remove the second node (2)
//     std::cout << "Before removing node: ";
//     Node* it = head;
//     do {
//         std::cout << it->m_data << " ";
//         it = it->m_next;
//     } while (it != head);
//     std::cout << std::endl;

//     removeNode(head, node2);

//     std::cout << "After removing node: ";
//     it = head;
//     do {
//         std::cout << it->m_data << " ";
//         it = it->m_next;
//     } while (it != head);
//     std::cout << std::endl;

//     return 0;
// }
