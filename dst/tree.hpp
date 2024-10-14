#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <iomanip>
#include <functional>

using namespace std;

struct TreeNode {
    int value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const int val) : value(val), left(nullptr), right(nullptr) {}
};

struct Tree {
    TreeNode* head;
    Tree() : head(nullptr) {}

    void insertNum(int value) {
        function<TreeNode*(TreeNode*, int)> insert = [&insert](TreeNode* node, int value) -> TreeNode* {
            if (node == nullptr) {
                return new TreeNode(value);
            }

            if (value < node->value) {
                node->left = insert(node->left, value);
            } else {
                node->right = insert(node->right, value);
            }

            return node;
        };
        head = insert(head, value);
    }

    int depth(int value) {
        bool found = false;

        function<int(TreeNode*, int)> getDepth = [&getDepth, &found](TreeNode* node, int value) -> int {
            if (node == nullptr) {
                return 0;
            }

            if (value < node->value) {
                return getDepth(node->left, value) + 1;
            } else if (value > node->value) {
                return getDepth(node->right, value) + 1;
            } else {
                found = true;
                return 1;
            }
        };
        
        int depth = getDepth(head, value);
        if (!found) {
            return -1;
        }
        return depth;
    }
};

void printTree(ostream& os, TreeNode* tree, int depth = 0, string prefix = "") {
    if (tree == nullptr) {
        return;
    }

    // Выводим правое поддерево (расположено выше в консоли)
    if (tree->right != nullptr) {
        printTree(os, tree->right, depth + 1, prefix + "\t");
    }

    // Выводим текущий узел с отступом
    os << prefix;
    if (depth > 0) {
        os << "└──";
    }
    os << "[" << tree->value << "]" << endl;

    // Выводим левое поддерево (расположено ниже в консоли)
    if (tree->left != nullptr) {
        printTree(os, tree->left, depth + 1, prefix + "\t");
    }
}

ostream& operator<<(ostream& os, const Tree& tree) {
    printTree(os, tree.head);
    return os;
}

#endif