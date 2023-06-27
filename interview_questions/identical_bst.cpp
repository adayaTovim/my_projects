#include <iostream>
#include <stack>

/*Write a function that given two binary search trees returns true if the trees are identical.*/
class Node {
public:
	explicit Node(int a_data, Node* a_right = nullptr, Node* a_left = nullptr) : m_data(a_data), m_right(a_right), m_left(a_left) {};
	Node(const Node& a_other) = delete;
	Node& operator = (const Node& a_other) =  delete;
	~Node() = default;

	int getData() const { return m_data; };
	Node* getLeft() const { return m_left; };
	Node* getRight() const { return m_right; };

	void setData(int a_data) { m_data = a_data; };
	void setLeft(Node* a_left) { m_left = a_left; };
	void setRight(Node* a_right) { m_right = a_right; };

private:
	int m_data;
	Node* m_left;
	Node* m_right;
};

class BST {
public:
	BST() : m_root (nullptr) {};

	void insert(int a_data)
	{
		if(m_root == nullptr) {
			m_root = new Node(a_data);
		}

		Node* current = m_root;
		while(true) {
			if(a_data < current->getData()) {
				if(current->getLeft() == nullptr) {
					current->setLeft(new Node(a_data));
					return;
				}
				current = current->getLeft();
			} else if(a_data > current->getData()){
				if(current->getRight() == nullptr) {
					current->setRight(new Node(a_data));
					return;
				}
				current = current->getRight();
			} else {
				return;
			}
		}
	};

	void printInOrder()
	{
		if(m_root == nullptr) {
			return;
		}

		std::stack<Node*> stack;
		Node* current = m_root;

		while(current != nullptr || !stack.empty()) {
			while(current != nullptr) {
				stack.push(current);
				current = current->getLeft();
			}

			current = stack.top();
			stack.pop();

			std::cout << current->getData() << " ";

			current = current->getRight();
		}
	}

	Node* getRoot() {return m_root;};

private:
	Node* m_root;
};

bool identicalBst(Node* a_root1, Node* a_root2)
{
    if (a_root1 == nullptr && a_root2 == nullptr) {
        return true;
    }

    if (a_root1 == nullptr || a_root2 == nullptr) {
        return false;
    }

    if (a_root1->getData() != a_root2->getData()) {
        return false;
    }

    bool isLeftSubtreeIdentical = identicalBst(a_root1->getLeft(), a_root2->getLeft());

    bool isRightSubtreeIdentical = identicalBst(a_root1->getRight(), a_root2->getRight());

    return isLeftSubtreeIdentical && isRightSubtreeIdentical;
}

int main() {
	BST bst1;
	bst1.insert(1);
	bst1.insert(3);
	bst1.insert(6);
	bst1.insert(4);
	bst1.insert(7);
	bst1.insert(8);
	bst1.insert(10);
	bst1.insert(14);
	bst1.insert(13);

	std::cout << "bst1: " << std::endl;
	bst1.printInOrder();
	std::cout << "\n";

	BST bst2;
	bst2.insert(1);
	bst2.insert(3);
	bst2.insert(6);
	bst2.insert(4);
	bst2.insert(7);
	bst2.insert(8);
	bst2.insert(10);
	bst2.insert(14);
	bst2.insert(13);

	std::cout << "bst2: " << std::endl;
	bst2.printInOrder();
	std::cout << "\n";

	if( identicalBst(bst1.getRoot(), bst2.getRoot()) == true) {
		std::cout << "The trees are identical" << std::endl;
	} else {
		std::cout << "The trees are Unidentical" << std::endl;
	}
	return 0;
}
