#include <iostream>
#include "data_structures/tree.hpp"

int main() {
    Tree tree;
    tree.insertNum(5);
    tree.insertNum(10);
    tree.insertNum(15);
    tree.insertNum(3);

    cout << tree << endl;
    int a = 3;
    cout << "Element " << a;
    if (tree.find(a)) {
        cout << " is found" << endl;
    } else {
        cout << " is not found" << endl;
    }
    //cout << tree.find(10) << endl;
    //cout << tree.find(11) << endl;

    return 0;
}