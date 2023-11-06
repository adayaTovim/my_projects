#include <iostream>
#include <vector>

// Create a binary tree
// Find and print all the paths from the root to the leaf nodes of the tree.
// Calculate the sum of numbers formed by concatenating the values along each path.
// for example for bt - 1 3 2 5- the path will be :
// Path: 1 3 2
// Path: 1 3 5
// the sum will be 132 + 135 = 267

class Node {
public:
    Node(int val) : value(val), left(nullptr), right(nullptr) {}

    int value;
    Node* left;
    Node* right;

};

class BinaryTree {
public:
    BinaryTree(int rootValue) : root(new Node(rootValue)) {}

    void insert(int value) {
        insertRecursive(root, value);
    }

    void insertRecursive(Node* currentNode, int value) {
        if (value <= currentNode->value) {
            if (currentNode->left == nullptr) {
                currentNode->left = new Node(value);
            } else {
                insertRecursive(currentNode->left, value);
            }
        } else {
            if (currentNode->right == nullptr) {
                currentNode->right = new Node(value);
            } else {
                insertRecursive(currentNode->right, value);
            }
        }
    }

    std::vector<std::vector<int>> findPathsToLeaves() {
        std::vector<std::vector<int>> paths;
        std::vector<int> currentPath;
        findPathsRecursive(root, currentPath, paths);
        return paths;
    }

    void findPathsRecursive(Node* currentNode, std::vector<int>& currentPath, std::vector<std::vector<int>>& paths) {
        if (currentNode == nullptr) {
            return;
        }

        currentPath.push_back(currentNode->value);

        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            paths.push_back(currentPath);
        } else {
            findPathsRecursive(currentNode->left, currentPath, paths);
            findPathsRecursive(currentNode->right, currentPath, paths);
        }

        currentPath.pop_back();
    }

private:
    Node* root;
};

void printResult(const std::vector<std::vector<int>>& pathsToLeaves) {
    for (const std::vector<int>& path : pathsToLeaves) {
            std::cout << "Path: ";
            for (int value : path) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
    }
}

int sumPaths(const std::vector<std::vector<int>>& paths) {
    int totalSum = 0;
    for (const std::vector<int>& path : paths) {
        int pathSum = 0;
        for (int value : path) {
            pathSum = pathSum * 10 + value;
        }
        totalSum += pathSum;
    }
    return totalSum;
}

int main() {
    BinaryTree tree(1);
    tree.insert(3);
    tree.insert(2);
    tree.insert(5);

    std::vector<std::vector<int>> pathsToLeaves = tree.findPathsToLeaves();
    printResult(pathsToLeaves);

    std::cout << sumPaths(pathsToLeaves)<<"\n";

    return 0;
}
