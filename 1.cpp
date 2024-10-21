#include <iostream>
#include "data_structures/tree.hpp"


int main() {
    Tree tree;
    tree.insert(tree.head, 5);
    tree.insert(tree.head, 10);
    tree.insert(tree.head, 15);
    tree.insert(tree.head, 3);

    cout << tree << endl;
    if (tree.find(11)) {
        cout << "true" << endl;
    } else {
        cout << "false" << endl;
    }
    //cout << tree.find(10) << endl;
    //cout << tree.find(11) << endl;

    return 0;
}