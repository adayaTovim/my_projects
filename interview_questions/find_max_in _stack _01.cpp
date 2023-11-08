#include <iostream>
#include <stack>

//Find maximum in a stack in O(1) time and O(1) extra space

class Stack
{
public:
    void push(int num)
    {
        if(m_max.empty() || m_max.top() <= num) {
            m_max.push(num);
        }
        m_stack.push(num);
    }

    void pop()
    {
        int num = m_stack.top();
        if(m_max.top() == num) {
            m_max.pop();
        }
        m_stack.pop();
    }

    int findMax()
    {
        return m_max.top();
    }

    std::stack<int> m_stack;
    std::stack<int> m_max;
};

int main() {
    Stack myStack;

    myStack.push(3);
    myStack.push(1);
    myStack.push(5);
    myStack.push(2);
    myStack.push(10);

    std::cout << "Maximum element: " << myStack.findMax() << std::endl;

    myStack.pop();
    std::cout << "Maximum element after pop: " << myStack.findMax() << std::endl;

    return 0;
}
