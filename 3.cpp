#include <iostream>
#include "data_structures/vector.hpp"
#include "data_structures/set.hpp"

int main() {
    Set set;
    set.put(14);
    set.put(5);
    set.put(7);
    set.put(8);
    set.put(1);

    auto values = set.values();
    values.sort();

    Set subset1, subset2;
    int sum1 = 0;
    int sum2 = 0;

    for(int i = 0; i < values.size(); i++) {
        int element = values.get(i);
        if(sum1 < sum2) {
            subset1.put(element);
            sum1 += element;
        } else {
            subset2.put(element);
            sum2 += element;
        }
    }
    
    cout << "Subset1: " << subset1 << "Sum: " << sum1 << endl;
    cout << "Subset2: " << subset2 << "Sum: " << sum2 << endl;
}