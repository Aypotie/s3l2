#include <iostream>
#include "data_structures/vector.hpp"

int main() {
    Vector<int> vec;
    vec.pushBack(4);
    vec.pushBack(-7);
    vec.pushBack(1);
    vec.pushBack(5);
    vec.pushBack(-4);
    vec.pushBack(0);
    vec.pushBack(-3);
    vec.pushBack(2);
    vec.pushBack(4);
    vec.pushBack(1);

    int a = 5;
    
    for (int i = 0; i < vec.size(); i++) {
        int sum = 0; 
        for (int j = i; j < vec.size(); j++) {
            sum += vec.get(j); 
            if (sum == a) {
                for (int k = i; k <= j; k++) {
                    cout << vec.get(k);
                    if (k < j) {
                        cout << ", ";
                    }
                }
                cout << endl;
            }
        }
    }

    return 0;
}
