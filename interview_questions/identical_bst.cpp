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

private:
	Node* m_root;
};

bool identicalBst(BST a_bst1, BST a_bst2)
{

}

int main() {
	BST bst;
	bst.insert(1);
	bst.insert(3);
	bst.insert(6);
	bst.insert(4);
	bst.insert(7);
	bst.insert(8);
	bst.insert(10);
	bst.insert(14);
	bst.insert(13);

	bst.printInOrder();
	std::cout << "\n";
	return 0;
}
