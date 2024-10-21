#include <iostream>
#include "data_structures/tree.hpp"
#include "data_structures/vector.hpp"

void find(TreeNode* node, Vector<int>& result) {
    if (node == nullptr) {
        return;
    }
    if (node->left != nullptr && node->right != nullptr) {
        result.pushBack(node->value);
        
    }
    find(node->left, result);
    find(node->right, result);
}

int main() {
    Tree tree;
    int value;
    while (true) {
        cin >> value;
        if (value == 0) {
            break;
        }

        tree.insertNum(value);
    }
    cout << tree << endl;

    Vector<int> res;
    find(tree.head, res);
    res.sort();
    res.reverse();
    cout << res << endl;
    return 0;
}