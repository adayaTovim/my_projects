/* Given a linked list, swap every two adjacent nodes and return its head.
You must solve the problem without modifying the values in the list's nodes
(i.e., only nodes themselves may be changed.)
Example 1:
Input: head = [1,2,3,4]
Output: [2,1,4,3]

Example 2:
Input: head = []
Output: []

Example 3:
Input: head = [1]
Output: [1]*/

#include <iostream>


 // Definition for singly-linked list
 struct ListNode {
	ListNode() : m_value(0), m_next(nullptr) {}
	ListNode(int a_x) : m_value(a_x), m_next(nullptr) {}
	ListNode(int a_x, ListNode *next) : m_value(a_x), m_next(next) {}

	int m_value;
	ListNode *m_next;
 };

class Solution {
public:
    ListNode* swapPairs(ListNode* a_head) {

		if(a_head == nullptr || a_head->m_next == nullptr) {
			return a_head;
		}

		ListNode* newHead = a_head->m_next;
		ListNode* prevNode = nullptr;
		ListNode* currentNode = a_head;
		ListNode* nextNode;

		while (currentNode != nullptr && currentNode->m_next != nullptr) {
			nextNode = currentNode->m_next;
			currentNode->m_next = nextNode->m_next;
			nextNode->m_next = currentNode;

			if(prevNode != nullptr) {
				prevNode->m_next = nextNode;
			}

			prevNode = currentNode;
			currentNode = currentNode->m_next;
		}

		return newHead;
    }
};

void printLinkList(ListNode* a_head)
{
	std::cout<<"[ ";
	auto it = a_head;
	while(it != nullptr) {
		std::cout << it->m_value << " ";
		it = it->m_next;
	}
	std::cout<<"]\n";
}

int main() {

	std::cout <<"Example 1:\n";
	ListNode node1(3);
	ListNode node2(4, &node1);
	ListNode node3(1, &node2);
	ListNode node4(2, &node3);

	printLinkList(&node4);
	Solution s;
	ListNode *result1 = s.swapPairs(&node4);
	printLinkList(result1);

	std::cout <<"Example 2:\n";
	ListNode* node5 = nullptr;
	printLinkList(node5);
	ListNode *result2 = s.swapPairs(node5);
	printLinkList(result2);

	std::cout <<"Example 3:\n";
	ListNode node6(1);
	printLinkList(&node6);
	ListNode *result3 = s.swapPairs(&node6);
	printLinkList(result3);

	return 0;
}
