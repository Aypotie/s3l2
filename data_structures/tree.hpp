#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <functional>
#include "stack.hpp"

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

    TreeNode* insert(TreeNode* node, int value) {
        if (head == nullptr) {
            head = new TreeNode(value);
            return head;
        }

        if(node == nullptr) {
            return new TreeNode(value);
        }

        if(value < node->value) {
            node->left = insert(node->left, value);
            
        } else if(value > node->value) {
            node->right = insert(node->right, value);
        }

        return node;
    }

    void insertNum(int value) {
        insert(head, value);
    }

    TreeNode* find2(Stack<TreeNode*> stack, int value) {
        while (stack.size() != 0) {
            TreeNode* node = stack.pop();
            if (node->value == value) {
                return node;
            }

            if (node->right != nullptr) {
                stack.push(node->right);
            }
            if (node->left != nullptr) {
                stack.push(node->left);
            }
        }

        return nullptr;
    }

    TreeNode* find(int value) {
        Stack<TreeNode*> stack;
        if(head == nullptr) {
            return nullptr;
        } else {
            stack.push(head);
        }

        return find2(stack, value);
    } 
};

// Функция для печати дерева
void printTree(string& result, TreeNode* tree, int depth = 0, string prefix = "") {
    if (tree == nullptr) {
        return;
    }

    // Выводим правое поддерево (расположено выше в консоли)
    if (tree->right != nullptr) {
        printTree(result, tree->right, depth + 1, prefix + "\t");
    }

    // Выводим текущий узел с отступом
    result += prefix;
    if (depth > 0) {
        result += "└──";
    }
    result += "[" + to_string(tree->value) + "]\n";

    // Выводим левое поддерево (расположено ниже в консоли)
    if (tree->left != nullptr) {
        printTree(result, tree->left, depth + 1, prefix + "\t");
    }
}

ostream& operator<<(ostream& os, const Tree& tree) {
    string stringTree = "";
    printTree(stringTree, tree.head);
    os << stringTree;
    return os;
}

#endif
